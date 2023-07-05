#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;

	NumX = 100.f;
	NumY = 200.f;
	NumZ = 300.f;

	//AActor* actor = nullptr;
	//GLog->Log(actor->GetName());
}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();
	
	FString str;
	str.Append("NumA : ");
	str.Append(FString::FromInt(NumA));
	str.Append(", NumX : ");
	str.Append(FString::SanitizeFloat(NumX));

	GLog->Log(str);
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

