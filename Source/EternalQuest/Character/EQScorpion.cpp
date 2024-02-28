


#include "Character/EQScorpion.h"
#include "Projectile/EQScorpionSkill.h"
#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "AI/EQScorpionFSM.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

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

void AEQScorpion::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	AEQScorpionSkill* Skill = Cast<AEQScorpionSkill>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		Player -> TakeDamage(Ability->SpiderWebDamage,DamageEvent,nullptr,Skill);
	}
}

FString AEQScorpion::SetName()
{
	Super::SetName();
	MonsterName = TEXT("스콜피");
	return MonsterName;
}
