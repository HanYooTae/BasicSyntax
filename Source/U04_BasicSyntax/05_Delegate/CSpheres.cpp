#include "CSpheres.h"
#include "Global.h"
#include "CMulticast.h"
#include "Materials/MaterialInstanceDynamic.h"

ACSpheres::ACSpheres()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	UStaticMesh* meshAsset = nullptr;
	CHelpers::GetAsset(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Sphere.SM_Sphere'");

	for (int32 i = 0; i < 3; i++)
	{
		FString name;
		name.Append("Sphere");
		name.Append(FString::FromInt(i + 1));

		CHelpers::CreateSceneComponent(this, &Spheres[i], FName(name), Root);

		Spheres[i]->SetRelativeLocation(FVector(i * 150, 0, 0));
		Spheres[i]->SetStaticMesh(meshAsset);
	}
}

void ACSpheres::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstance* materialAsset;
	CHelpers::GetAssetDynamic(&materialAsset, "MaterialInstanceConstant'/Game/StaticMeshes/MAT_StaticMesh_Inst.MAT_StaticMesh_Inst'");

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform = Spheres[i]->GetComponentToWorld();
		OriginLocation[i] = transform.GetLocation();

		DynamicMaterials[i] = UMaterialInstanceDynamic::Create(materialAsset, nullptr);
		Spheres[i]->SetMaterial(0, DynamicMaterials[i]);
	}

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMultiCast::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACMultiCast* multicast = Cast<ACMultiCast>(actors[0]);
	CheckNull(multicast);

	multicast->OnMulticast.AddUFunction(this, "Fall");
	multicast->OnMulticast.AddLambda([=](int32 InIndex, FLinearColor InColor)
		{
			CLog::Print(InColor.ToString());
			CLog::Print(Number);
		}
	);
}

void ACSpheres::Fall(int32 InIndex, FLinearColor InColor)
{
	CLog::Print("Random Index : " + FString::FromInt(InIndex));

	for (int32 i = 0; i < 3; i++)
	{
		Spheres[i]->SetSimulatePhysics(false);
		Spheres[i]->SetWorldLocation(OriginLocation[i]);
		
		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FLinearColor(1, 1, 1));
	}

	Spheres[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}