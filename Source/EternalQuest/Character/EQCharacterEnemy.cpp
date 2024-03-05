// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterEnemy.h"

#include "AI/EQMonsterAbility.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widget/EQDamageAmoutUI.h"

AEQCharacterEnemy::AEQCharacterEnemy()
{
	Ability = CreateDefaultSubobject<UEQMonsterAbility>(TEXT("Ability"));
	DamageComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageComp"));
	DamageComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UEQDamageAmoutUI> TempUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_DamageUI.WBP_DamageUI'"));
	if(TempUI.Succeeded())
	{
		DamageComp->SetWidgetClass(TempUI.Class);
		DamageComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DamageComp->SetCastShadow(false);
	}
}

void AEQCharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	DamageComp->SetVisibility(false);
	Ability->DamageUI = Cast<UEQDamageAmoutUI>(DamageComp->GetWidget());
}

void AEQCharacterEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector Start = DamageComp->GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	DamageComp->SetWorldRotation(NewRotation);
}

float AEQCharacterEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Ability->TakeDamage(this,DamageAmount,Type,EventInstigator,DamageCauser);
	return DamageAmount;
}


int32 AEQCharacterEnemy::GetExperience()
{
	return Experience;
}

void AEQCharacterEnemy::DropItem() {}
