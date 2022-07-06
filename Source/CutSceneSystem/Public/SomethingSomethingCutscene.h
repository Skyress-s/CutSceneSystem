// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomethingSomethingCutscene.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCutSceneEnd);

UCLASS()
class CUTSCENESYSTEM_API ASomethingSomethingCutscene : public AActor
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
	UPROPERTY(EditAnywhere)
	class ULevelSequence* LevelSequenceOne = nullptr;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	UFUNCTION()
	void OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul);

	UPROPERTY(BlueprintAssignable)
	FCutSceneEnd CutSceneEnd;

	UFUNCTION()
	void ViewTargetToPlayer();

private:
	UPROPERTY()
	bool bHoldSkip = false;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere);
		float blendTime = 1.2f;
};



