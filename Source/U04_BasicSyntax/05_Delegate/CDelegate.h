#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CDelegate.generated.h"

DECLARE_DELEGATE(FBeginOverlapSignature);	//void __()
DECLARE_DELEGATE(FEndOverlapSignature);		//void __()
DECLARE_DELEGATE_RetVal_OneParam(FString, FRandomColorSignature, FLinearColor);	//FString __(FLinearColor)

UCLASS()
class U04_BASICSYNTAX_API ACDelegate : public ACBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBeginOverlapSignature OnBeginOverlap;
	FEndOverlapSignature OnEndOverlap;
	FRandomColorSignature OnRandomColor;
};
