#include "CExplosionTrigger.h"
#include "CSphereTrace.h"
#include "Global.h"

void ACExplosionTrigger::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACSphereTrace::StaticClass(), actors);

	CheckFalse(actors.Num() > 0);

	ACSphereTrace* explosion = Cast<ACSphereTrace>(actors[0]);
	CheckNull(explosion);

	OnActorBeginOverlap.AddDynamic(explosion, &ACSphereTrace::Explosion);
}