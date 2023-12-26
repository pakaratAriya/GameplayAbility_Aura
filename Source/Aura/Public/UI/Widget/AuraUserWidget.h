// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetAuraWidgetController(UObject* InWidgetController);
	UPROPERTY(BlueprintReadOnly)
		TObjectPtr<UObject> AuraWidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void AuraWidgetControllerSet();

	
};
