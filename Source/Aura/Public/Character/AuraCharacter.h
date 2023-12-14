// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
class AAuraPlayerState;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	UPROPERTY()
		TObjectPtr<AAuraPlayerState> PlayerState;
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;
};