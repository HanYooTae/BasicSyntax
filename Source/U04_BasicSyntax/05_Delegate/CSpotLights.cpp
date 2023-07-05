#include "CSpotLights.h"
#include "Global.h"
#include "CMulticast.h"
#include "Components/SpotLightComponent.h"

ACSpotLights::ACSpotLights()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	for (int32 i = 0; i < 3; i++)
	{
		FString name;
		name.Append("SpotLight");
		name.Append(FString::FromInt(i + 1));

		CHelpers::CreateSceneComponent(this, &SpotLights[i], FName(name), Root);

		SpotLights[i]->SetRelativeLocation(FVector(i * 150, 0, 0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->SetIntensity(1e+5f);		// 100000
		SpotLights[i]->OuterConeAngle = 25.f;
	}
}

void ACSpotLights::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMultiCast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACMultiCast* multicast = Cast<ACMultiCast>(actors[0]);
	CheckNull(multicast);

	multicast->OnMulticast.AddUFunction(this, "ChangeLightColor");
}

void ACSpotLights::ChangeLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));
	}

	SpotLights[InIndex]->SetLightColor(InColor);
}