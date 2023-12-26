// Copy right Pakarat Ariyaprayoon


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetAuraWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitiealized, please fill out BP_AuraHUD"));
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	const FAuraWidgetControllerParams WCParams(PC, PS, ASC, AS);
	OverlayWidgetController = GetOverlayWidgetController(WCParams);
	OverlayWidget->SetAuraWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}

