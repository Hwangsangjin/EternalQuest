


#include "Character/EQNormalEnemy.h"

#include "AI/EQBaseFSM.h"
#include "AI/EQMonsterAbility.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AEQNormalEnemy::AEQNormalEnemy()
{
	BaseFsm = CreateDefaultSubobject<UEQBaseFSM>("BasFSM");
	Ability = CreateDefaultSubobject<UEQMonsterAbility>("Ability");
	HPComp = CreateDefaultSubobject<UWidgetComponent>("HPComp");
	HPComp -> SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UUserWidget>WidgetTemp(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_MonsterHPBar.WBP_MonsterHPBar_C'"));
	if(WidgetTemp.Succeeded())
	{
		HPComp->SetWidgetClass(WidgetTemp.Class);
		HPComp->SetDrawSize(FVector2D(150,20));
		HPComp->SetRelativeLocation(FVector(0,0,120));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEQNormalEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Start = HPComp->GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	HPComp->SetWorldRotation(NewRotation);

	
}

