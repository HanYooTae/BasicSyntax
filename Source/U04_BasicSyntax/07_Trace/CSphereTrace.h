#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSphereTrace.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACSphereTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSphereTrace();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void Explosion(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
};
