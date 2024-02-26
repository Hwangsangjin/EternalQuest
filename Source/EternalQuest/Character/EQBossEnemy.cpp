


#include "Character/EQBossEnemy.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widget/EQBossMonsterHPUI.h"

AEQBossEnemy::AEQBossEnemy()
{
	HPComp = CreateDefaultSubobject<UWidgetComponent>("HPComp");
	HPComp -> SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UUserWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_MonsterHPBar.WBP_MonsterHPBar_C'"));
	if(TempWidget.Succeeded())
	{
		HPComp->SetWidgetClass(TempWidget.Class);
		HPComp->SetDrawSize(FVector2D(150,20));
		HPComp->SetRelativeLocation(FVector(0,0,500.f));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HPComp->SetVisibility(false);
		HPComp->SetCastShadow(false);
	}
	
	//Ability = CreateDefaultSubobject<UEQMonsterAbility>(TEXT("Ability"));
	bReplicates = true;
	SetReplicateMovement(true);
}



void AEQBossEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto Player = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	float Dist = FVector::Dist(Player->GetActorLocation(),this->GetActorLocation());
	FVector Start = HPComp->GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	HPComp->SetWorldRotation(NewRotation);
	if(Dist < DetectRange || bCanShowHP == true ) HPComp->SetVisibility(true);
	else  HPComp->SetVisibility(false);
	
	if(Dist < DetectRange || bCanShowHP == true )
	{
		ShowBossHPBar();
	}
	else
	{
		RemoveBossHPBar();
	}
}

bool AEQBossEnemy::GetIsMonsterHit()
{
	return Ability->bIsHit;
}

void AEQBossEnemy::ShowBossHPBar()
{
	auto UI = CreateWidget<UEQBossMonsterHPUI>(GetWorld(),HPUIFactory);
	UI->AddToViewport();
	UI->SetVisibility(ESlateVisibility::Visible);
	BossHp = Cast<UEQBossMonsterHPUI>(UI);
	UI->UpdateHP(Ability->CurrentHealth,Ability->MaxHealth);
}

void AEQBossEnemy::RemoveBossHPBar()
{
	if(BossHp)
	{
		auto UI = CreateWidget<UEQBossMonsterHPUI>(GetWorld(),HPUIFactory);
		UI->SetVisibility(ESlateVisibility::Hidden);
		BossHp = Cast<UEQBossMonsterHPUI>(UI);
	}
}
