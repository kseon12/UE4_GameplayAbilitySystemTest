// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/GATargetActor_GroundSelect.h"

#include "Abilities/GameplayAbility.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"

////////////////////////////////////////////////////////////

AGATargetActor_GroundSelect::AGATargetActor_GroundSelect():
	Radius(200.f)
{
	PrimaryActorTick.bCanEverTick = true;
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	DecalComponent->SetupAttachment(DecalComponent);
}

////////////////////////////////////////////////////////////

void AGATargetActor_GroundSelect::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	DecalComponent->DecalSize = FVector{ Radius };
}

////////////////////////////////////////////////////////////

void AGATargetActor_GroundSelect::ConfirmTargetingAndContinue()
{
	FVector ViewLocation;
	GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> OverlapResultArray;
	TArray<TWeakObjectPtr<AActor>> OverlapActorArray;
	//bool TraceComplex = false;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = false;
	CollisionQueryParams.bReturnPhysicalMaterial = false;

	const APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		CollisionQueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	//constexpr float Radius{ 100.f };
	bool bOverlapSuccess = GetWorld()->OverlapMultiByObjectType(
		OverlapResultArray,
		ViewLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		CollisionQueryParams);

	if (bOverlapSuccess)
	{
		for (int32 i = 0; i < OverlapResultArray.Num(); ++i)
		{
			APawn* OverlappedPawn = Cast<APawn>(OverlapResultArray[i].GetActor());
			if (OverlappedPawn && !OverlapActorArray.Contains(OverlappedPawn))
			{
				OverlapActorArray.Add(OverlappedPawn);
			}
		}
	}

	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	if(DecalComponent)
	{
		CenterLocation->TargetLocation.LiteralTransform = DecalComponent->GetComponentTransform();
		CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	}

	if (OverlapActorArray.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapActorArray);
		TargetData.Add(CenterLocation);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(CenterLocation));
	}
}

////////////////////////////////////////////////////////////

bool AGATargetActor_GroundSelect::GetPlayerLookingPoint(FVector& OutViewPoint)
{
	FVector Viewpoint;
	FRotator ViewRotation;
	MasterPC->GetPlayerViewPoint(Viewpoint, ViewRotation);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;

	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	bool bTraceSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Viewpoint, Viewpoint + ViewRotation.Vector() * 5'000.f, ECollisionChannel::ECC_Visibility, QueryParams);
	if (bTraceSuccess)
	{
		OutViewPoint = HitResult.ImpactPoint;
	}
	else
	{
		OutViewPoint = FVector();
	}

	return bTraceSuccess;
}

////////////////////////////////////////////////////////////

void AGATargetActor_GroundSelect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Viewpoint{};
	GetPlayerLookingPoint(Viewpoint);
	DecalComponent->SetWorldLocation(Viewpoint);
}

////////////////////////////////////////////////////////////
