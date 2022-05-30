// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeSignature, float, Health, float, MaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangeSignature, float, Mana, float, MaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStrengthChangeSignature, float, Strength, float, MaxStrength);

UCLASS()
class GAS_TEST_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCharacterAttributeSet();

	//protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeBase", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Armour;

public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Mana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxMana);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Strength);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Strength);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, MaxStrength);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxStrength);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxStrength);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxStrength);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Power);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Power);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Power);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Power);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Armour);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Armour);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Armour);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Armour);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	FOnHealthChangeSignature OnHealthChange;
	FOnManaChangeSignature OnManaChange;
	FOnStrengthChangeSignature OnStrengthChange;
};
