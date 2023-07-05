#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACProperty : public AActor
{
	GENERATED_BODY()

public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere) 
		int NumA = 10;

	UPROPERTY(EditDefaultsOnly)
		int NumB = 20;

	UPROPERTY(EditInstanceOnly)
		int NumC = 30;

	UPROPERTY(VisibleAnywhere)
		float NumX;

	UPROPERTY(VisibleDefaultsOnly)
		float NumY;

	UPROPERTY(VisibleInstanceOnly)
		float NumZ;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		bool bCheckTest;
};
