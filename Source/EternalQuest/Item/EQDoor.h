

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQDoor.generated.h"

class AEQWarlockOrc;
class AEQNormalEnemy;
class UEQBaseFSM;

UCLASS()
class ETERNALQUEST_API AEQDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQDoor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door1;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door2;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door3;
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	
	bool IsOpen = false;
	
};
