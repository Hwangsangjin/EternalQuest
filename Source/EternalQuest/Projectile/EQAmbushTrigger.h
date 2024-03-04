

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQAmbushTrigger.generated.h"

class AEQCharacterPlayer;
class AEQAmbushOrc;
class UBoxComponent;

UCLASS()
class ETERNALQUEST_API AEQAmbushTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQAmbushTrigger();

protected:
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	AEQCharacterPlayer* Player;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	USceneComponent* SpawnLoc1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	USceneComponent* SpawnLoc2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	USceneComponent* SpawnLoc3;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AEQAmbushOrc> OrcFactory;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Orc")
	AEQAmbushOrc* AmbushOrc;

	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(Server,Reliable)
	void ServerRPC_OverLapBegin(AActor* OtherActor);

private:
	UPROPERTY(Replicated)
	bool IsOverlapped = false;
};
