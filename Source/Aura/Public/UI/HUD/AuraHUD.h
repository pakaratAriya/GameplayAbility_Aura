// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

/**
 * 
 */

class UAuraUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FAuraWidgetControllerParams;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FAuraWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
