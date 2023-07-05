#include "CGameMode.h"
#include "Chracters/CPlayer.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;

}