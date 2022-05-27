// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/GATargetActor_Around.h"

#include "Abilities/GameplayAbility.h"

////////////////////////////////////////////////////////////

AGATargetActor_Around::AGATargetActor_Around():
	Radius(200.f)
{
}

void AGATargetActor_Around::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

////////////////////////////////////////////////////////////

void AGATargetActor_Around::ConfirmTargetingAndContinue()
{
	APawn* OwningPawn = MasterPC->GetPawn();
	if (!OwningPawn) return;

	FVector ViewLocation{ OwningPawn->GetActorLocation() };

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


	if (OverlapActorArray.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapActorArray);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}

////////////////////////////////////////////////////////////
