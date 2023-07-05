#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CComponentOverlap.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACComponentOverlap : public ACBox
{
	GENERATED_BODY()

public:
	ACComponentOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;

private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
