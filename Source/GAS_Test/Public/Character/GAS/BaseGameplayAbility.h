// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TEST_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGameplayAbility")
	UMaterialInstance* UIMaterial;

	UFUNCTION(BlueprintCallable, Category = "BaseGameplayAbility")
		FGameplayAbilityInfo GetGameplayAbilityInfo();

	void GetAbilityCostTypeByName(FString& InName, EAbilityCostType& OutCostType);
};
