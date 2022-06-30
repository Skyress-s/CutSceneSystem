// Fill out your copyright notice in the Description page of Project Settings.


#include "SomethingSomethingCutscene.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASomethingSomethingCutscene::ASomethingSomethingCutscene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));

	
}

// Called when the game starts or when spawned
void ASomethingSomethingCutscene::BeginPlay()
{
	Super::BeginPlay();

	

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ASomethingSomethingCutscene::OnOverLap);
}

// Called every frame
void ASomethingSomethingCutscene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASomethingSomethingCutscene::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul) {

	FMovieSceneSequencePlaybackSettings settings = FMovieSceneSequencePlaybackSettings();
    ALevelSequenceActor* actor;
    ULevelSequencePlayer* player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequenceOne, settings , actor);
    player->Play();
    player->SetDisableCameraCuts(true);
    UE_LOG(LogTemp, Warning, TEXT("Wahooo"))
    UActorComponent* CameraComponent = nullptr;
    
    CameraComponent = player->GetActiveCameraComponent(); 
    if (CameraComponent != nullptr) {
    	UE_LOG(LogTemp, Warning, TEXT("YEEE BABY!"));
    }

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->SetInputMode(FInputModeUIOnly());
	controller->FlushPressedKeys();
	

    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 0.f);
    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(CameraComponent->GetOwner(), 2.f);

	//gets the time
	FFrameRate TickResolution = LevelSequenceOne->MovieScene->GetTickResolution();
	float EndSeconds = LevelSequenceOne->MovieScene->GetPlaybackRange().GetUpperBoundValue() / TickResolution;
	float StartSeconds = LevelSequenceOne->MovieScene->GetPlaybackRange().GetLowerBoundValue() / TickResolution;
	UE_LOG(LogTemp, Warning, TEXT("End time : %f  . Start time : %f"), EndSeconds, StartSeconds);

	float blendTime = 1.1f;
	FTimerHandle handle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]()
                             	{
                             		ViewTargetToPlayer(blendTime);
                             	});
	GetWorld()->GetTimerManager().SetTimer(handle, TimerDelegate, EndSeconds - blendTime, false);
}

void ASomethingSomethingCutscene::ViewTargetToPlayer(float blendTime) {
	
    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 2.f);
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
    	controller->SetInputMode(FInputModeGameOnly());
}
