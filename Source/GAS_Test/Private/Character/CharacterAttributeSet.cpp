// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAttributeSet.h"
#include "Character/BaseCharacter.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
////////////////////////////////////////////////////////////

UCharacterAttributeSet::UCharacterAttributeSet() :
	Health(100.0f),
	MaxHealth(100.0f),
	Mana(100.f),
	MaxMana(100.f),
	Strength(100.f),
	MaxStrength(100.f),
	Power(50.f),
	Armour(50.f)
{
}

////////////////////////////////////////////////////////////

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	/**
	 * A bit unnesesary stuff. Can be changed to Data.EvaluatedData.Attribute == GetHealthAttribute(); etc
	 */
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetBaseValue()));

		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningActor());

		if (BaseCharacter)
		{
			if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
			{
				BaseCharacter->AddGameplayTag(BaseCharacter->FullHealthTag);
			}
			else
			{
				BaseCharacter->RemoveGameplayTag(BaseCharacter->FullHealthTag);
			}
		}
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetBaseValue()));

		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.f, MaxStrength.GetBaseValue()));

		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}

////////////////////////////////////////////////////////////
