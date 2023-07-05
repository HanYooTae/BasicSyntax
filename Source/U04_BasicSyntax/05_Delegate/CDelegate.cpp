#include "CDelegate.h"
#include "Global.h"

void ACDelegate::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACDelegate::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDelegate::EndOverlap);
}

void ACDelegate::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OnBeginOverlap.IsBound())
		OnBeginOverlap.Execute();

	if (OnRandomColor.IsBound())
	{
		FLinearColor color = FLinearColor::MakeRandomColor();
		color.A = 1.f;

		FString str = OnRandomColor.Execute(color);
		str.Append("Random Color is");

		CLog::Log(str);
	}
}

void ACDelegate::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnEndOverlap.IsBound())
		OnEndOverlap.Execute();
}
