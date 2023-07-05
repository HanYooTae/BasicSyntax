#include "CParticles.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"
#include "CEvent.h"

ACParticles::ACParticles()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);

	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetTextRenderColor(FColor::Red);
	Text->SetText(FText::FromString(GetActorLabel()));

	CHelpers::GetAsset(&Particles[0], "ParticleSystem'/Game/Particles/P_Destruction1.P_Destruction1'");
	CHelpers::GetAsset(&Particles[1], "ParticleSystem'/Game/Particles/P_ky_healAura.P_ky_healAura'");
	CHelpers::GetAsset(&Particles[2], "ParticleSystem'/Game/Particles/P_ky_lightning3.P_ky_lightning3'");
}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACEvent::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACEvent* eventObject = Cast<ACEvent>(actors[0]);
	CheckNull(eventObject);

	eventObject->OnEvent.AddUFunction(this, "PlayParticles");
}

void ACParticles::PlayParticles(int32 InIndex)
{

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorTransform());
}

