// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, FGameplayTagContainer& /*All Asset Tags*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;
protected:
	void OnEffectApplied(UAbilitySystemComponent* AbilitySystem, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
	
};
