#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Aim.generated.h"

UCLASS()
class U04_BASICSYNTAX_API UCUserWidget_Aim : public UUserWidget
{
	GENERATED_BODY()

public:
	// Target Image to Red
	UFUNCTION(BlueprintImplementableEvent)
		void OnTarget();

	// Target Image to White
	UFUNCTION(BlueprintImplementableEvent)
		void OffTarget();
};