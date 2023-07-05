#include "CStaticMesh_Cube.h"

ACStaticMesh_Cube::ACStaticMesh_Cube()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'"));

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
}

