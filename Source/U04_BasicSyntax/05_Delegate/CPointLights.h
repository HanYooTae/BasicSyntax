#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPointLights.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACPointLights : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPointLights();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void On();
	
	UFUNCTION()
		void Off();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight1;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight2;

	UFUNCTION()
		FString RandomLightColor(FLinearColor InColor);
};
