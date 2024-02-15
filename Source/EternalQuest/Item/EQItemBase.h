// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQItemBase.generated.h"


UCLASS()
class ETERNALQUEST_API AEQItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEQItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	UStaticMeshComponent* MeshComp;

	
	// ----- 변수 -----
};