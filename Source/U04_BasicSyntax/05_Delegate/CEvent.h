#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CEvent.generated.h"


UCLASS()
class U04_BASICSYNTAX_API ACEvent : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	DECLARE_EVENT_OneParam(ACEvent, FEventSignature, int32);

	FEventSignature OnEvent;
};
