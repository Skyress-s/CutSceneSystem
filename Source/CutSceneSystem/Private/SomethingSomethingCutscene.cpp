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


	if (bHoldSkip) {
		UE_LOG(LogTemp, Warning, TEXT("Holding input!"))
	}
}

void ASomethingSomethingCutscene::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul) {
	
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	// //binds input so we can skip
    FInputActionBinding pressed("SkipCutscene", IE_Pressed);
    pressed.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
    {
    	bHoldSkip = true;
    });
    controller->GetPawn()->InputComponent->AddActionBinding(pressed);
    
    FInputActionBinding release("SkipCutscene", IE_Released);
    release.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
    {
    	bHoldSkip = false;
    });
    controller->GetPawn()->InputComponent->AddActionBinding(release);

	//other stuff
	FMovieSceneSequencePlaybackSettings settings = FMovieSceneSequencePlaybackSettings();
    ALevelSequenceActor* actor;
    ULevelSequencePlayer* player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequenceOne, settings , actor);
    player->Play();
    player->SetDisableCameraCuts(true);
    UE_LOG(LogTemp, Warning, TEXT("Wahooo"))
    UActorComponent* CameraComponent = nullptr;
    
    CameraComponent = player->GetActiveCameraComponent(); 
	controller->SetInputMode(FInputModeUIOnly());
	controller->SetInputMode(FInputModeUIOnly().SetWidgetToFocus())
	controller->FlushPressedKeys();
	

    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 0.f);
    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(CameraComponent->GetOwner(), 2.f);

	//gets the time
	FFrameRate TickResolution = LevelSequenceOne->MovieScene->GetTickResolution();
	float EndSeconds = LevelSequenceOne->MovieScene->GetPlaybackRange().GetUpperBoundValue() / TickResolution;
	float StartSeconds = LevelSequenceOne->MovieScene->GetPlaybackRange().GetLowerBoundValue() / TickResolution;
	UE_LOG(LogTemp, Warning, TEXT("End time : %f  . Start time : %f"), EndSeconds, StartSeconds);

	FTimerHandle handle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]()
                             	{
                             		ViewTargetToPlayer();
                             	});
	GetWorld()->GetTimerManager().SetTimer(handle, TimerDelegate, EndSeconds - blendTime, false);


	
}

void ASomethingSomethingCutscene::ViewTargetToPlayer() {

	UE_LOG(LogTemp, Warning, TEXT("blend time%f"), blendTime)
    GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), blendTime);
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
    	controller->SetInputMode(FInputModeGameOnly());
}
