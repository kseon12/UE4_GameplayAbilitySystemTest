// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/BaseGameplayAbility.h"

////////////////////////////////////////////////////////////

FGameplayAbilityInfo UBaseGameplayAbility::GetGameplayAbilityInfo()
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	float CooldownDuration{ 0.f };
	float Cost{ 0.f };
	EAbilityCostType CostType{EAbilityCostType::MAX};

	if (CooldownEffect && CostEffect)
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);

			GetAbilityCostTypeByName(EffectInfo.Attribute.AttributeName, CostType);
		}
	}

	return FGameplayAbilityInfo{ CooldownDuration,Cost,CostType, UIMaterial, GetClass() };
}

	

////////////////////////////////////////////////////////////

void UBaseGameplayAbility::GetAbilityCostTypeByName(FString& InName, EAbilityCostType& OutCostType)
{
	if(InName == "Health")
	{
		OutCostType= EAbilityCostType::Health;
		return;
	}
	if (InName == "Mana")
	{
		OutCostType= EAbilityCostType::Mana;
		return;
	}
	if (InName == "Strength")
	{
		OutCostType= EAbilityCostType::Strength;
		return;
	}

	OutCostType = EAbilityCostType::MAX;
}

////////////////////////////////////////////////////////////
