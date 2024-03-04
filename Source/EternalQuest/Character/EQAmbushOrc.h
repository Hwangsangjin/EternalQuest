// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQAmbushOrc.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQAmbushOrc : public AEQNormalEnemy
{
	GENERATED_BODY()

public:
	AEQAmbushOrc();
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* HelmetComp;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PauldronsComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp_L;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp_R;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Montage")
	UAnimMontage* Montage;
	
	virtual void BeginPlay() override;
	virtual FString SetName() override;

	UFUNCTION(NetMulticast,Unreliable)
	void MultiPRC_Ambushing();
	
};
