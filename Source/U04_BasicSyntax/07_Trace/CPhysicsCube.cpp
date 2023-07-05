#include "CPhysicsCube.h"
#include "Global.h"

ACPhysicsCube::ACPhysicsCube()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/StaticMeshes/SM_Cube");
	Mesh->SetStaticMesh(meshAsset);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	UMaterial* materialAsset;
	CHelpers::GetAsset(&materialAsset, "Material'/Game/StaticMeshes/Textures/Mat_Box.Mat_Box'");
	Mesh->SetMaterial(0, materialAsset);

	Mesh->SetMassOverrideInKg(NAME_None, 50.f);
}

void ACPhysicsCube::BeginPlay()
{
	Super::BeginPlay();
	
}


