// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAS/AbilityTypes.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TEST_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "BasePlayerController")
	void AbilityToUI(FGameplayAbilityInfo AbilityInfo);
};
