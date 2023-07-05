#include "CPrintLog.h"
#include "Global.h"

ACPrintLog::ACPrintLog()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPrintLog::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2);
	CLog::Print(4, 2);
	CLog::Print(5);
	CLog::Print("Hell World", -1, 5.f, FColor::Red);

	FVector someLocation = FVector(100, 200, 300);
	CLog::Print(someLocation);

	FRotator someRotator = FRotator(0, 0, 90);
	CLog::Print(someRotator);

	//CLog::Print(SomeActor->GetName());
	
	CLog::Log(20);
	CLog::Log(PI);
	CLog::Log("Hello World ^^");
	CLog::Log(someLocation);
	CLog::Log(someRotator);
	CLog::Log(SomeActor);
	CLog::Log(this);
	CLog::Log(__FILE__);
	PrintLine();

}

void ACPrintLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	CLog::Print(RunningTime, 7);
}

