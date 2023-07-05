#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CBluePrintEvent.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACBluePrintEvent : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)	//BI Event
		void ChangePlayerColor();

	UFUNCTION(BlueprintNativeEvent)		// BN Event
		void ResetPlayerColor();

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
