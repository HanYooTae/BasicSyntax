#include "CPointLights.h"
#include "Global.h"
#include "Components/PointLightComponent.h"
#include "CDelegate.h"

ACPointLights::ACPointLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &PointLight1, "PointLight1", Root);
	CHelpers::CreateSceneComponent(this, &PointLight2, "PointLight2", Root);

	PointLight1->SetIntensity(1e+4f);
	PointLight1->SetAttenuationRadius(200.f);
	PointLight1->LightColor = FColor(255, 128, 50);

	PointLight2->SetIntensity(1e+4f);
	PointLight2->SetAttenuationRadius(200.f);
	PointLight2->LightColor = FColor(255, 128, 50);
	PointLight2->SetRelativeLocation(FVector(200, 0, 0));
}

void ACPointLights::BeginPlay()
{
	Super::BeginPlay();

	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACDelegate::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACDelegate* trigger = Cast<ACDelegate>(actors[0]);
	CheckNull(trigger);
	trigger->OnBeginOverlap.BindUFunction(this, "On");
	trigger->OnEndOverlap.BindUFunction(this, "Off");

	trigger->OnRandomColor.BindUFunction(this, "RandomLightColor");
}

void ACPointLights::On()
{
	PointLight1->SetVisibility(true);
}

void ACPointLights::Off()
{
	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);
}

FString ACPointLights::RandomLightColor(FLinearColor InColor)
{
	PointLight2->SetLightColor(InColor);
	PointLight2->SetVisibility(true);

	return InColor.ToString();
}

