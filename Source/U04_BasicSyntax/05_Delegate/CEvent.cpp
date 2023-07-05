#include "CEvent.h"
#include "Global.h"

void ACEvent::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACEvent::BeginOverlap);
}

void ACEvent::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnEvent.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		OnEvent.Broadcast(index);
	}
}