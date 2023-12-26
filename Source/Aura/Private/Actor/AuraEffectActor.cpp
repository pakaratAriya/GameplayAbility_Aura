

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "Character/AuraCharacter.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject < USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap) {
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap) {
		for (const TSubclassOf<UGameplayEffect> DurationGameplayEffectClass : DurationGameplayEffectClasses) {
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap) {
		for (const TSubclassOf<UGameplayEffect> DurationGameplayEffectClass : DurationGameplayEffectClasses) {
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap) {
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap) {
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles) {
			if (HandlePair.Value == TargetASC) {
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove) {
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASCTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASCTarget == nullptr) return;
	check(GameplayEffectClass );
	FGameplayEffectContextHandle EffectContextHandle = ASCTarget->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec = ASCTarget->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = ASCTarget->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	if (EffectSpec.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite) {
		ActiveEffectHandles.Add(ActiveEffectHandle, ASCTarget);
	}
}


