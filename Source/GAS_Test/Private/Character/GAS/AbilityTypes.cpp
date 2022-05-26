// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/AbilityTypes.h"

////////////////////////////////////////////////////////////

FGameplayAbilityInfo::FGameplayAbilityInfo():
	CooldownDuration(0.f),
	Cost(0.f),
	AbilityCostType(EAbilityCostType::MAX),
	UIMaterial(nullptr),
	BaseGameplayAbilityClass(nullptr)
{
}

////////////////////////////////////////////////////////////

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCooldownDuration, float InCost, EAbilityCostType InAbilityCostType, UMaterialInstance* InUIMaterial,
                                           TSubclassOf<UBaseGameplayAbility> InBaseGameplayAbilityClass):
	CooldownDuration(InCooldownDuration),
	Cost(InCost),
	AbilityCostType(InAbilityCostType),
	UIMaterial(InUIMaterial),
	BaseGameplayAbilityClass(InBaseGameplayAbilityClass)
{
}

////////////////////////////////////////////////////////////
