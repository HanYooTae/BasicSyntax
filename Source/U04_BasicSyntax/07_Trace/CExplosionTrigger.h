#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBox.h"
#include "CExplosionTrigger.generated.h"

UCLASS()
class U04_BASICSYNTAX_API ACExplosionTrigger : public ACBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
