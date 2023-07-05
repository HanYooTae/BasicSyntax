#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Chracters/IRifle.h"
#include "Weapons/CRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	CheckNull(OwnerCharacter);
	
	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	if (!!rifleCharacter)
	{
		bEquipped = rifleCharacter->GetRifle()->IsEquipped();
		bAiming = rifleCharacter->GetRifle()->IsAiming();
	}
	
	//UKismetMathLibrary::VSizeXY()
}