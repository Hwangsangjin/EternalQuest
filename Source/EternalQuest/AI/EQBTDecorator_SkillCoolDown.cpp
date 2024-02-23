// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTDecorator_SkillCoolDown.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UEQBTDecorator_SkillCoolDown::UEQBTDecorator_SkillCoolDown()
{
	NodeName = TEXT("Skill Cool Down");
}

bool UEQBTDecorator_SkillCoolDown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	float CurrentTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	CurrentTime += GetWorld()->GetDeltaSeconds();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("CurrentTime")), CurrentTime);
	UE_LOG(LogTemp, Warning, TEXT("currTime1 : %f"), CurrentTime);
	
	
	float CoolDown = FMath::FRandRange(7.f,10.f);

	if(CurrentTime > CoolDown)
	{
		return true;
	}
	return false;
}



