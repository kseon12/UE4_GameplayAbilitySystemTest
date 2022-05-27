// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActor_Around.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TEST_API AGATargetActor_Around : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATargetActor_Around();
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GATargetActor_Around", meta=(AllowPrivateAccess=true, ExposeOnSpawn=true))
	float Radius;
};
