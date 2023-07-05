#include "CSphereTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &Particle, "Particle");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Particle);

	UParticleSystem* particleAsset;
	CHelpers::GetAsset(&particleAsset, "ParticleSystem'/Game/Particles/P_Destruction1.P_Destruction1'");
	Particle->SetTemplate(particleAsset);

	Particle->bAutoActivate = false;

	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetTextRenderColor(FColor::Red);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetText(FText::FromString("Boom Here!!!"));
	Text->SetWorldSize(60);
}

void ACSphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSphereTrace::Explosion(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector start = GetActorLocation();
	FVector end = start + 1;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResults;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		start,
		end,
		1000,
		objectTypes,
		false,
		ignores,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true
	))
	{
		Particle->ResetParticles();
		Particle->SetActive(true);

		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());

			if (!!meshComp)
				meshComp->AddRadialImpulse
				(
					GetActorLocation(),
					1000.f,
					15e6f / meshComp->GetMass(),
					ERadialImpulseFalloff::RIF_Linear
				);
		}
	}
}
