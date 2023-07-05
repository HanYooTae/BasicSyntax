#include "CActorOverlap.h"
#include "Global.h"

void ACActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACActorOverlap::BeginOverlap);	
}

void ACActorOverlap::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print(OtherActor->GetActorLabel() + " is come in");
}