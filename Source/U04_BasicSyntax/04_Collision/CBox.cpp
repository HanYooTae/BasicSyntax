#include "CBox.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBox::ACBox()
{
	//Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	//RootComponent = "Scene";
	//SetRootComponent(Scene);
	CHelpers::CreateSceneComponent(this, &Scene, "Scene");

	//Box = CreateDefaultSubobject<UBoxComponent>("Box");
	//Box->SetupAttachment(Scene);
	CHelpers::CreateSceneComponent(this, &Box, "Box", Scene);
	CHelpers::CreateSceneComponent(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3.f));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetTextRenderColor(FColor::Red);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetText(FText::FromString(GetName()));	//GetDisplayName()
}