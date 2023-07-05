#include "CLineTrace.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "CVertex.h"
#include "Chracters/CPlayer.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);
}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACVertex::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	bCheckVertex = actors.Num() >= 2 ? true : false;

	if (bCheckVertex == false)
	{
		FString message = "Not Enough Vertex";
		UE_LOG(LogTemp, Error, L"%s", *message);

		return;
	}

	Vertices[0] = Cast <ACVertex>(actors[0]);
	Vertices[1] = Cast <ACVertex>(actors[1]);

	OnLineTraceResult.AddDynamic(this, &ACLineTrace::Ragdoll);
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bCheckVertex);

	FVector start = Vertices[0]->GetActorLocation();
	FVector end = Vertices[1]->GetActorLocation();

	//start.Z = -20;
	//end.Z = -20;

	TArray<AActor*> ignores;
	ignores.Add(Vertices[0]);
	ignores.Add(Vertices[1]);

	FHitResult hitResult;

	if (UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(),
		start,
		end,
		"Pawn",
		false,
		ignores,
		EDrawDebugTrace::ForOneFrame,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	))
	{
		if (OnLineTraceResult.IsBound())
		{
			OnLineTraceResult.Broadcast(hitResult.GetActor(), FLinearColor::MakeRandomColor());
		}
	}

	DrawDebugLine(GetWorld(), start, end, FColor::Red);
}

void ACLineTrace::Ragdoll(AActor* InActor, FLinearColor InColor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor);
	CheckNull(player);

	player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	player->GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	player->GetMesh()->SetSimulatePhysics(true);

	FVector force = player->GetActorForwardVector() * -100000.f;
	player->GetMesh()->AddImpulse(FVector(force));
}

