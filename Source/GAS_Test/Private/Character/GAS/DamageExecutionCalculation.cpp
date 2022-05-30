// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/DamageExecutionCalculation.h"
#include "Character/CharacterAttributeSet.h"

////////////////////////////////////////////////////////////

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Power)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armour)

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Power, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Armour, Target, false)
	}
};

////////////////////////////////////////////////////////////

static DamageStatics& GetDamageStatics()
{
	static DamageStatics DamageStaticsSingletone;
	return DamageStaticsSingletone;
}

////////////////////////////////////////////////////////////

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	/*
	HealthProperty = FindFieldChecked<FProperty>(UCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCharacterAttributeSet, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, false);
	*/
	DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Health, Target, false)

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().PowerDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmourDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float AttackDamageMagnitude{ 0.f };
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().PowerDef, FAggregatorEvaluateParameters(), AttackDamageMagnitude);

	float ArmourMagnitude{ 0.f };
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmourDef, FAggregatorEvaluateParameters(), ArmourMagnitude);

	float FinalDamage = (AttackDamageMagnitude / ArmourMagnitude) * (-10);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, FinalDamage));
}

////////////////////////////////////////////////////////////
