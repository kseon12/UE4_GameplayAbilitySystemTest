// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.generated.h"

class UBaseGameplayAbility;
class UGameplayAbility;
class UAbilitySystemComponent;
class UCharacterAttributeSet;

UCLASS()
class GAS_TEST_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void AutoDeterminTeamIDByControllerType();
	void Dead();

	void DisableInputControll();
	void EnableInputControll();

	void AddAbilityToUI(TSubclassOf<UBaseGameplayAbility> AbilityToAdd);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS", meta=(AllowPrivateAccess="true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UCharacterAttributeSet* CharacterAttributeSet;

	bool bIsDead;

	/** -1 stands for no team = attacked by anyone */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayData", meta=(AllowPrivateAccess="true", ClampMin = "-1"))
	int32 TeamID;

	FTimerHandle StunHandle;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void AddAbility(TSubclassOf<UGameplayAbility> AbilityToAdd);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void AddAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAdd);


	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void OnManaChanged(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintCallable)
	void OnStrengthChanged(float Strength, float MaxStrength);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStrengthChanged"))
	void BP_OnStrengthChanged(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Die"))
	void BP_Die();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	bool IsTargetHostile(ABaseCharacter* Target);

	FORCEINLINE int32 GetTeamID() const { return TeamID; }

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void AddGameplayTag(FGameplayTag& TagToAdd);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void RemoveGameplayTag(FGameplayTag& TagToRemove);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	FGameplayTag FullHealthTag;

	UFUNCTION(BlueprintCallable)
		void HitStun(float Duration);
};
