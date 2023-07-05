#include "CVertex.h"
#include "Global.h"

ACVertex::ACVertex()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh", Root);

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Cylinder.SM_Cylinder'");
	Mesh->SetStaticMesh(meshAsset);
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 2.5f));
}

void ACVertex::BeginPlay()
{
	Super::BeginPlay();


}
