#include "CRifle.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Chracters/IRifle.h"
#include "Engine/StaticMeshActor.h"
#include "Chracters/CPlayer.h"
#include "CBullet.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	USkeletalMesh* meshAsset;

	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");

	Mesh->SetSkeletalMesh(meshAsset);

	CHelpers::GetAsset(&GrabMontage, "AnimMontage'/Game/Character/Animations/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	CHelpers::GetAsset(&UngrabMontage, "AnimMontage'/Game/Character/Animations/Rifle/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	CHelpers::GetClass(&FireShakeClass, "Blueprint'/Game/Player/BP_FireShake.BP_FireShake_C'");

	CHelpers::GetClass(&BulletClass, "Blueprint'/Game/Player/BP_CBullet.BP_CBullet_C'");

	CHelpers::GetAsset(&MuzzleParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Muzzleflash.VFX_Muzzleflash'");
	CHelpers::GetAsset(&EjectParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Eject_bullet.VFX_Eject_bullet'");
	CHelpers::GetAsset(&ImpactParticle, "ParticleSystem'/Game/Particles_Rifle/Particles/VFX_Impact_Default.VFX_Impact_Default'");

	CHelpers::GetAsset(&FireSound, "SoundCue'/Game/Sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
	CHelpers::GetAsset(&Decal, "Material'/Game/Materials/M_Decal.M_Decal'");
}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters param;
	param.Owner = InOwner;

	return InWorld->SpawnActor<ACRifle>(param);
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bAiming);

	// Get Aim Info
	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifleCharacter);

	FVector start, end, direction;
	rifleCharacter->GetAimInfo(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1.0f, 0, 3.f);

	// LineTrace (AimWidget)
	FHitResult hitResult;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	param.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_PhysicsBody,
		param
	))
	{
		AStaticMeshActor* smActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!smActor)
		{
			UStaticMeshComponent* smComp = Cast<UStaticMeshComponent>(smActor->GetRootComponent());
			if (!!smComp)
			{
				if (smComp->BodyInstance.bSimulatePhysics == true)
				{
					OtherComp = smComp;
					rifleCharacter->OnTarget();
					return;
				}
			}
		}

		OtherComp = nullptr;
		rifleCharacter->OffTarget();
	}

}

void ACRifle::Begin_Aiming()
{ 
	bAiming = true; 
}

void ACRifle::End_Aiming()
{
	bAiming = false; 
}

void ACRifle::Equip()
{
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACRifle::End_Equip()
{
	bEquipping = false;

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACRifle::Unequip()
{
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void ACRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::End_Unequip()
{
	bEquipping = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACRifle::Begin_Fire()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);
	//CheckFalse(bAiming);
	CheckTrue(bFiring);

	bFiring = true;

	CurrentPitch = 0.f;

	// 연사모드
	if (bRapid == true)
	{
		GetWorld()->GetTimerManager().SetTimer(RapidTimer, this, &ACRifle::Firing, 0.1f, true);
		return;
	}

	// 단발모드
	Firing();
}

void ACRifle::End_Fire()
{
	bFiring = false;

	if (bRapid == true && RapidTimer.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(RapidTimer);
}

void ACRifle::Firing()
{
	FVector start, end, direction;
	
	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifleCharacter);
	rifleCharacter->GetAimInfo(start, end, direction);

	// Add Impulse
	if (!!OtherComp)
	{
		FVector ownerLocation = OwnerCharacter->GetActorLocation();
		FVector targetLocation = OtherComp->GetComponentToWorld().GetLocation();
		FVector targetDirection;

		targetDirection = targetLocation - ownerLocation;
		targetDirection.Normalize();

		OtherComp->AddImpulseAtLocation(targetDirection * 3000.f, ownerLocation);
	}

	// Play CameraShake
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	if (!!player)
	{
		APlayerController* controller = player->GetController<APlayerController>();
		CheckNull(controller);
		controller->PlayerCameraManager->PlayCameraShake(FireShakeClass);
	}

	// Spawn Bullet
	FVector muzzleLocation = Mesh->GetSocketLocation("muzzleFlash");
	if (!!BulletClass)
		GetWorld()->SpawnActor<ACBullet>(BulletClass, muzzleLocation, direction.Rotation());
	
	// Play Effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticle, Mesh, "MuzzleFlash");
	UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "EjectBullet");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, muzzleLocation);


	// Decal & impact particle
	FHitResult hitResult;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	param.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_Visibility,
		param
	))
	{
		FRotator impactRotator = hitResult.ImpactNormal.Rotation();

		UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5, 5, 5), hitResult.Location, impactRotator, 10.f);
		decal->SetFadeScreenSize(0);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, hitResult.Location, impactRotator, true);
	}

	// Additive Pitch
	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();

	if (CurrentPitch > -PitchSpeed)
	{
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
		CLog::Print(CurrentPitch, 1);
	}
}


