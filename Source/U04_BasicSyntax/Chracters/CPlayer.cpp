#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "CAnimInstance.h"
#include "Weapons/CRifle.h"
#include "Widgets/CUserWidget_Aim.h"
#include "Widgets/CUserWidget_Rapid.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Component Settings
	//<Mesh>
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(L"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	if(meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> animClass(L"AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	if(animClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(animClass.Class);

	//<SpringArm(CameraBoom)>
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));

	//<Camera>
	Camera->SetupAttachment(SpringArm);

	//Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// Get Widget Class
	CHelpers::GetClass(&AimWidgetClass, "WidgetBlueprint'/Game/Widgets/WB_Aim.WB_Aim_C'");
	CHelpers::GetClass(&RapidWidgetClass, "WidgetBlueprint'/Game/Widgets/WB_Rapid.WB_Rapid_C'");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* bodyMaterialAsset;
	UMaterialInstanceConstant* logoMaterialAsset;

	CHelpers::GetAssetDynamic(&bodyMaterialAsset, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic(&logoMaterialAsset, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_ChestLogo.M_UE4Man_ChestLogo'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterialAsset, nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterialAsset, nullptr);

	// Set Dynamic Material to Mesh Comp
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// Spawn Rifle
	Rifle = ACRifle::Spawn(GetWorld(), this);

	// Create Widget
	AimWidget = CreateWidget<UCUserWidget_Aim, APlayerController>(GetController<APlayerController>(), AimWidgetClass);
	AimWidget->AddToViewport();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);

	RapidWidget = CreateWidget<UCUserWidget_Rapid, APlayerController>(GetController<APlayerController>(), RapidWidgetClass);
	RapidWidget->AddToViewport();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	// Action Event
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
	
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("Rapid", EInputEvent::IE_Released, this, &ACPlayer::OnRapid);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();
	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();
	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnRifle()
{
	if (Rifle->IsEquipped() == true)
	{
		OffAim();
		Rifle->Unequip();
		return;
	}
		Rifle->Equip();
}

void ACPlayer::OnAim()
{
	CheckFalse(Rifle->IsEquipped());
	CheckTrue(Rifle->IsEquipping());

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	//bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	ZoomIn();

	Rifle->Begin_Aiming();
	AimWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	CheckFalse(Rifle->IsEquipped());
	CheckTrue(Rifle->IsEquipping());

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector(0, 0, 0);

	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;

	ZoomOut();

	Rifle->End_Aiming();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnFire()
{
	Rifle->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Rifle->End_Fire();
}

void ACPlayer::OnRapid()
{
	CheckTrue(Rifle->IsFiring());

	Rifle->ToggleRapid();

	Rifle->IsRapid() ? RapidWidget->OnRapid() : RapidWidget->OffRapid();
}

void ACPlayer::SetColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::SetColor_Reset()
{
	FLinearColor origin = FLinearColor(0.450980f, 0.403922f, 0.360784f);
	SetColor(origin, origin);
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutDirection)
{
	OutDirection = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector cameraLocation = transform.GetLocation();
	OutAimStart = cameraLocation + OutDirection * 180.f;

	FVector conDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutDirection, 0.2f);
	conDirection *= 3000.f;
	OutAimEnd = cameraLocation + conDirection;
}

void ACPlayer::OnTarget()
{
	AimWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	AimWidget->OffTarget();
}
