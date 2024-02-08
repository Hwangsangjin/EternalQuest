

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EQMonsterAbility.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQMonsterAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEQMonsterAbility();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
