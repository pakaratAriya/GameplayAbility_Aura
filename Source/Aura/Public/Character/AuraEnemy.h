// Copy right Pakarat Ariyaprayoon

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
private:
};
