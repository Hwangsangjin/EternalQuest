// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQSpider.h"

#include "Components/CapsuleComponent.h"

AEQSpider::AEQSpider()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Spider/SK_Spider.SK_Spider'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeScale3D(FVector(0.3f));
		GetMesh()->SetRelativeLocation(FVector(10,0,-60));
		GetCapsuleComponent()->SetCapsuleHalfHeight(74.f);
		GetCapsuleComponent()->SetCapsuleRadius(70);
	}
}
