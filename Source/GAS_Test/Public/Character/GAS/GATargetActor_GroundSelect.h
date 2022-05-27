// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActor_GroundSelect.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TEST_API AGATargetActor_GroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATargetActor_GroundSelect();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
	bool GetPlayerLookingPoint(FVector& OutViewPoint);

	virtual void Tick(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroundSelect", meta=(AllowPrivateAccess = true, ExposeOnSpawn = true))
	float Radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GroundBlast", meta = (AllowPrivateAccess = true))
	UDecalComponent* DecalComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GroundBlast", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneComponent;

};
