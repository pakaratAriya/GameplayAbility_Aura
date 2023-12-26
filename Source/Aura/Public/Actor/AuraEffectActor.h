// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;
class UAbilitySystemComponent;


UENUM(BlueprintType)
enum class EEffectApplicationPolicy :uint8 {
	EAP_ApplyOnOverlap,
	EAP_ApplyOnEndOverlap,
	EAP_DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy :uint8 {
	ERP_RemoveOnEndOverlap,
	ERP_DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::ERP_RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effect")
		float ActorLevel = 1.0f;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
