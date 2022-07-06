// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CutsceneSkipWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUTSCENESYSTEM_API UCutsceneSkipWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
};
