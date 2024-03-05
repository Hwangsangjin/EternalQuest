// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EQBerserkerDummy.generated.h"

UCLASS()
class ETERNALQUEST_API AEQBerserkerDummy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEQBerserkerDummy();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Amor")
    USkeletalMeshComponent* HelmetMesh;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Amor")
    USkeletalMeshComponent* ShoulderMesh;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    UStaticMeshComponent* WeaponComp_L;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    UStaticMeshComponent* WeaponComp_R;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    USceneComponent* StartPos_L;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    USceneComponent* EndPos_L;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    USceneComponent* StartPos_R;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
    USceneComponent* EndPos_R;

};
