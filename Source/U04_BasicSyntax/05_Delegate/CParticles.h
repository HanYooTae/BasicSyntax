#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void PlayParticles(int32 InIndex);

private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Particles[3];

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
};
