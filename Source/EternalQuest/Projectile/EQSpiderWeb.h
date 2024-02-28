

#pragma once

#include "CoreMinimal.h"
#include "EQEnemyProjectile.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "EQSpiderWeb.generated.h"

class UEQMonsterAbility;
class AEQCharacterNonPlayer;
class AEQSpider;
class AEQCharacterPlayer;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ETERNALQUEST_API AEQSpiderWeb : public AEQEnemyProjectile
{
	GENERATED_BODY()
	
public:	
	
	AEQSpiderWeb();

protected:
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
