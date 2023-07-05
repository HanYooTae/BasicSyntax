#include "CBluePrintEvent.h"
#include "Global.h"
#include "Chracters/CPlayer.h"

void ACBluePrintEvent::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBluePrintEvent::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBluePrintEvent::EndOverlap);
}

void ACBluePrintEvent::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	ChangePlayerColor();
}

void ACBluePrintEvent::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	ResetPlayerColor();
}

void ACBluePrintEvent::ResetPlayerColor_Implementation()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(player);

	player->SetColor_Reset();
}