

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "EQSpiderWeb.generated.h"

class AEQSpider;
class AEQCharacterPlayer;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ETERNALQUEST_API AEQSpiderWeb : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQSpiderWeb();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Niagara")
	UNiagaraComponent* NiagaraComp;

	UPROPERTY()
	AEQCharacterPlayer* Target;

	UPROPERTY()
	AEQSpider* Self;

	float Speed = 600;
	
	UFUNCTION()
	void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
