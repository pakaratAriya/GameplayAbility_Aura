// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category=Weapon)
		TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
		TObjectPtr<UAttributeSet> AbilitySet;

	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
