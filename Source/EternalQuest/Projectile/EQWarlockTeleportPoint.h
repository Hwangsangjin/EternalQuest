// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQWarlockTeleportPoint.generated.h"

UCLASS()
class ETERNALQUEST_API AEQWarlockTeleportPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQWarlockTeleportPoint();

protected:
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	FVector GetTeleportPoint(int32 Idx);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(MakeEditWidget = "true"))
	TArray<FVector> TPPoints;
};
