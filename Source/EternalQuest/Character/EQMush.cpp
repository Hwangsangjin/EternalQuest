// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQMush.h"

#include "AI/EQMeleeFSM.h"

AEQMush::AEQMush()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Mushroom/SK_Mushroom.SK_Mushroom'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0,0,-30));
	}
	
}


