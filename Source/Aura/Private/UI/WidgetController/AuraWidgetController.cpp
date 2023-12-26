// Copy right Pakarat Ariyaprayoon


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetAuraWidgetControllerParams(FAuraWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
