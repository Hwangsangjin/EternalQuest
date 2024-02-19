

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Monster")
	float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Monster")
	float CurrentHealth;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Spider")
	float SpiderWebDamage = 20;

public:
	void UpdateHP(float UpdateHealth);
	
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(Server,Reliable)
	void ServerRPC_UpdateHP(float UpdateHealth);

};
