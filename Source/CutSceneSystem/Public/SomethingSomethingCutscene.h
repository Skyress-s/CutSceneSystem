// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomethingSomethingCutscene.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCutSceneStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCutSceneEnd);
UCLASS()
class CUTSCENESYSTEM_API ASomethingSomethingCutscene : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASomethingSomethingCutscene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//my deseg
	//------------------------------------------------

	//componennts
	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;
	
	//funcs
	UFUNCTION()
	void OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul);
	UFUNCTION()
	void ViewTargetToPlayer(float blendTime);

	//events
	UPROPERTY(BlueprintAssignable)
	FCutSceneEnd CutSceneEnd;

	UPROPERTY(BlueprintAssignable)
	FCutSceneStart CutSceneStart;


	//variables
	UPROPERTY( EditAnywhere, Category = "Cutscene|assets")
	UAnimSequenceBase* cutSceneAnimation = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Cutscene|assets")
	class ULevelSequence* LevelSequenceOne = nullptr;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> widgetToSpawnClass = nullptr;
private:
	//flags
	UPROPERTY()
	bool bActive = false;
	UPROPERTY()
	bool bHoldSkip = false;
	UPROPERTY()

	//private varibles
	float holdSkipTime = 0.f;

	//eidtor visible
	UPROPERTY(meta =(AllowPrivateAccess = "true"), EditAnywhere, Category = "Cutscene|config")
	float holdSkipDuration = 1.5f;
	
	UPROPERTY(meta =(AllowPrivateAccess = "true"), EditAnywhere, Category = "Cutscene|config")
		float blendInTime = 1.2f;
	
	UPROPERTY(meta =(AllowPrivateAccess = "true"), EditAnywhere, Category = "Cutscene|config")
		float blendOutTime = 1.2f;

	UPROPERTY(meta =(AllowPrivateAccess = "true"), EditAnywhere, Category = "Cutscene|config")
	float skipBlendOutTime = 0.4f;
	
	//timer handles
	FTimerHandle CutSceneEndTimerHandle;

	//private objects
	UPROPERTY()
	APawn* originalPawn = nullptr;
	
	UPROPERTY()
	UActorComponent* CutsceneCamera = nullptr;
	
	UPROPERTY(EditAnywhere)
	class UCutsceneSkipWidget* cutsceneSkipWidget = nullptr;
};



