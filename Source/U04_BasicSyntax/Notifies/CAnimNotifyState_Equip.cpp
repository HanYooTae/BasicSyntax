#include "CAnimNotifyState_Equip.h"
#include "Chracters/IRifle.h"
#include "Global.h"
#include "Weapons/CRifle.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	//Attach to Hand Socket
	CheckNull(MeshComp);

	IIRifle* rifleCharacter = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifleCharacter);

	rifleCharacter->GetRifle()->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);

	IIRifle* rifleCharacter = Cast<IIRifle>(MeshComp->GetOwner());
	CheckNull(rifleCharacter);

	rifleCharacter->GetRifle()->End_Equip();
	//bEquipping -> false
}