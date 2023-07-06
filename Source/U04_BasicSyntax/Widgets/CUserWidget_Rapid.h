#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Rapid.generated.h"

UCLASS()
class U04_BASICSYNTAX_API UCUserWidget_Rapid : public UUserWidget
{
	GENERATED_BODY()

public:
	// Multi Shot
	UFUNCTION(BlueprintImplementableEvent)
		void OnRapid();

	// Single Shot
	UFUNCTION(BlueprintImplementableEvent)
		void OffRapid();
};