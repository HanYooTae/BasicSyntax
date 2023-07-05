#include "CComponentOverlap.h"
#include "Global.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Chracters/CPlayer.h"

ACComponentOverlap::ACComponentOverlap()
{
	CHelpers::CreateSceneComponent(this, &PointLight, "PointLight", Scene);

	PointLight->SetLightColor(FLinearColor::Green);
}

void ACComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACComponentOverlap::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACComponentOverlap::EndOverlap);
}

void ACComponentOverlap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	PointLight->SetVisibility(true);
}

void ACComponentOverlap::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	PointLight->SetVisibility(false);
}
