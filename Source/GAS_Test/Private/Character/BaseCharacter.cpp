// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Character/CharacterAttributeSet.h"
#include "Character/BasePlayerController.h"
#include "Character/GAS/BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Abilities/GameplayAbility.h"



////////////////////////////////////////////////////////////

ABaseCharacter::ABaseCharacter():
	bIsDead(false),
	TeamID(-1)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

////////////////////////////////////////////////////////////

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributeSet->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChanged);
	CharacterAttributeSet->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChanged);
	CharacterAttributeSet->OnStrengthChange.AddDynamic(this, &ABaseCharacter::OnStrengthChanged);
	AutoDeterminTeamIDByControllerType();
	AddGameplayTag(FullHealthTag);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::AutoDeterminTeamIDByControllerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
	else
	{
		TeamID = 1;
	}
}

////////////////////////////////////////////////////////////

void ABaseCharacter::Dead()
{
	DisableInputControll();
}

////////////////////////////////////////////////////////////

void ABaseCharacter::DisableInputControll()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		//DisableInput(PlayerController);
		PlayerController->DisableInput(PlayerController);
	}
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->GetBrainComponent()->StopLogic(FString("Whatever reason"));
	}
}

////////////////////////////////////////////////////////////

void ABaseCharacter::EnableInputControll()
{
	if (!bIsDead)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			//DisableInput(PlayerController);
			PlayerController->EnableInput(PlayerController);
		}
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->GetBrainComponent()->RestartLogic();
		}
	}
}

////////////////////////////////////////////////////////////

void ABaseCharacter::AddAbilityToUI(TSubclassOf<UBaseGameplayAbility> AbilityToAdd)
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController());
	if(BasePlayerController)
	{
		UBaseGameplayAbility* AbilityInstance = AbilityToAdd.Get()->GetDefaultObject<UBaseGameplayAbility>();
		if(AbilityInstance)
		{
			const FGameplayAbilityInfo AbilityInfo = AbilityInstance->GetGameplayAbilityInfo();
			BasePlayerController->AbilityToUI(AbilityInfo);
		}
	}
}

////////////////////////////////////////////////////////////

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

////////////////////////////////////////////////////////////

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

////////////////////////////////////////////////////////////

void ABaseCharacter::AddAbility(TSubclassOf<UGameplayAbility> AbilityToAdd)
{
	if (!HasAuthority()) return;
	if (!AbilitySystemComponent || !AbilityToAdd) return;

	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec{ AbilityToAdd });
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::AddAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAdd)
{
	for(const auto Ability : AbilitiesToAdd)
	{
		AddAbility(Ability);
		if(Ability->IsChildOf(UBaseGameplayAbility::StaticClass()))
		{
			TSubclassOf<UBaseGameplayAbility> BaseAbilityClass = *Ability;
			if(BaseAbilityClass)
			{
				AddAbilityToUI(BaseAbilityClass);
			}
		}
	}
}

////////////////////////////////////////////////////////////

void ABaseCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.f && !bIsDead)
	{
		bIsDead = true;
		Dead();
		BP_Die();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::OnStrengthChanged(float Strength, float MaxStrength)
{
	BP_OnStrengthChanged(Strength, MaxStrength);
}

////////////////////////////////////////////////////////////

bool ABaseCharacter::IsTargetHostile(ABaseCharacter* Target)
{
	// WTF?? TeamID is private member, yet no compile error
	if (Target->GetTeamID() == TeamID || !(Target->GetTeamID() != -1))
	{
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////

void ABaseCharacter::AddGameplayTag(FGameplayTag& TagToAdd)
{
	AbilitySystemComponent->AddLooseGameplayTag(TagToAdd);

	AbilitySystemComponent->SetTagMapCount(TagToAdd, 1);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::RemoveGameplayTag(FGameplayTag& TagToRemove)
{
	AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
}

////////////////////////////////////////////////////////////

void ABaseCharacter::HitStun(float Duration)
{
	DisableInputControll();

	GetWorldTimerManager().SetTimer(StunHandle, this, &ABaseCharacter::EnableInputControll, Duration);
}

////////////////////////////////////////////////////////////
