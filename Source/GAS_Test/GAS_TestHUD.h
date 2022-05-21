// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GAS_TestHUD.generated.h"

UCLASS()
class AGAS_TestHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGAS_TestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

