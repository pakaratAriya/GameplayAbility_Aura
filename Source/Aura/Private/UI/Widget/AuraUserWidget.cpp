// Copy right Pakarat Ariyaprayoon


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetAuraWidgetController(UObject* InWidgetController)
{
	AuraWidgetController = InWidgetController;	
	AuraWidgetControllerSet();
}
