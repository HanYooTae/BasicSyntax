#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, AActor*, InActor, FLinearColor, InColor);

UCLASS()
class U04_BASICSYNTAX_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

private:
	class ACVertex* Vertices[2];
	bool bCheckVertex;

public:
	UPROPERTY(BlueprintAssignable)
		FLineTraceResult OnLineTraceResult;

private:
	UFUNCTION()
		void Ragdoll(AActor* InActor, FLinearColor InColor);
};
