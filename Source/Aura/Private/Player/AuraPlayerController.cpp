// Copy right Pakarat Ariyaprayoon


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Crash immediately if there is no InputMappingContext
	check(AuraContext);
	// Get Subsystem from ULocalPlayer static function
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// Crash immediately if there is no InputLocalPlayerSubsystem
	if (Subsystem) {
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	/**
		Line trace from cursor, There are several scenarios:
		 A. LastActor is null, and ThisActor is null
			- Do nothing
		 B. LastActor is valid, and ThisActor is null
			- UnHighlight LastActor
		 C. LastActor is null, and ThisActor is valid
			- Highlight ThisActor
		 D. LastActor is valid, and ThisActor is valid but LastActor != ThisActor
			- UnHighlight LastActor, and Highlight ThisActor
		 E. LastActor, and ThisActor are the same
			- Do nothing
	*/
	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			// Case C - Highlight ThisActor
			ThisActor->HighlightActor();
		}
		else {
			// Case A - Do nothing
		}
	}
	else {
		if (LastActor != ThisActor) {
			if (ThisActor != nullptr) {
				// Case D - Highlight ThisActor and UnHighlight LastActor
				ThisActor->HighlightActor();
			}
			// Case B - UnHighlight LastActor
			LastActor->UnHighlightActor();
		}
		else {
			// Case E - Do Nothing
		}
	}
}
