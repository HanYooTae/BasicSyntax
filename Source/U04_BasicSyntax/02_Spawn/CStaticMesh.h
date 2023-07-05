#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACStaticMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMesh();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeColor();

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
};
