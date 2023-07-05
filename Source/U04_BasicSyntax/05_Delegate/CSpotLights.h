#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLights.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACSpotLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLights();

private:
	UFUNCTION()
		void ChangeLightColor(int32 InIndex, FLinearColor InColor);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];
};
