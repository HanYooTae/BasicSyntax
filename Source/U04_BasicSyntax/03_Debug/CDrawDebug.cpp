#include "CDrawDebug.h"
#include "Global.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	RelativeLocation[0] = FVector(0, 0, 0);
	RelativeLocation[1] = FVector(0, 500, 0);
	RelativeLocation[2] = FVector(-500, 0, 0);
	RelativeLocation[3] = FVector(-1000, 0, 0);

	Box = FBox(FVector(-50, -100, -50), FVector(+50, +100, +50));
	//-> Center : (0, 0, 0)
	//-> Width : 200
	//-> Height : 100
	//-> Depth : 100
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();
	
	//DrawDebugBox(GetWorld(), GetActorLocation() + Box.GetCenter(), Box.GetExtent(), FColor::Cyan, true);
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < 4; i++)
		WorldLocation[i] = GetActorLocation() + RelativeLocation[i];

	DrawDebugSolidBox(GetWorld(), WorldLocation[0], Box.GetExtent(), FColor::Cyan);
	DrawDebugPoint(GetWorld(), WorldLocation[1], 50, FColor::Red);
	DrawDebugSphere(GetWorld(), WorldLocation[2], 200, 30, FColor::Green);
	DrawDebugCircle(GetWorld(), WorldLocation[3], 200, 30, FColor::Blue);

	FVector start = WorldLocation[0];
	FVector end = WorldLocation[3];
	DrawDebugDirectionalArrow(GetWorld(), start, end, 200, FColor::White, false, -1, 0, 20.f);

	FVector sphereLocation = WorldLocation[2];
	sphereLocation.X += FMath::Sin(GetWorld()->GetTimeSeconds() * 3.f) * 200.f;
	DrawDebugPoint(GetWorld(), sphereLocation, 50, FColor::Red);
}

