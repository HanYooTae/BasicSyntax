#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACSpawner : public AActor
{
	GENERATED_BODY()

public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UClass* ClassRef;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<class ACStaticMesh> MeshClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACStaticMesh> MeshClasses[4];

private:
	class ACStaticMesh* MeshObjects[4];
};
