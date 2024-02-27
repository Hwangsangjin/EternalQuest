// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EQProjectileBase.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/EQCharacterEnemy.h"
#include "Engine/DamageEvents.h"

AEQProjectileBase::AEQProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetCollisionProfileName(TEXT("EQTrigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	SetRootComponent(Trigger);

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(Trigger);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(Trigger);
}

void AEQProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEQProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEQProjectileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const float AttackDamage = 10.0f;
	FDamageEvent DamageEvent;
	AEQCharacterEnemy* Enemy = Cast<AEQCharacterEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->TakeDamage(AttackDamage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		Destroy();
	}
}
