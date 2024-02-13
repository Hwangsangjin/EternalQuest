


#include "Character/EQScorpion.h"

#include "Components/CapsuleComponent.h"

AEQScorpion::AEQScorpion()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Scorpion/SK_Scorpion.SK_Scorpion'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeScale3D(FVector(2.5f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(120.f);
		GetCapsuleComponent()->SetCapsuleRadius(100.f);
	}
}
