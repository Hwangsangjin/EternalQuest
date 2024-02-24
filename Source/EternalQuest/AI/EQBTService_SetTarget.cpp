// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTService_SetTarget.h"

#include "AIController.h"
#include "EQAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"


UEQBTService_SetTarget::UEQBTService_SetTarget()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Set Target");
}

void UEQBTService_SetTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto* const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner());
	auto const * const Self = Controller->GetPawn();
	auto Target =  Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//FVector TargetLocation = Target->GetActorLocation();
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEQCharacterPlayer::StaticClass(),AllPlayers);
	float Dist = 10000;
	for(int32 i = 0; i< AllPlayers.Num(); i++)
	{
		float TempDist = FVector::Dist(AllPlayers[i]->GetActorLocation(),Self->GetActorLocation());
		if(Dist > TempDist)
		{
			Dist = TempDist;
			Target = Cast<AEQCharacterPlayer>(AllPlayers[i]);
			//TargetLocation = Target->GetActorLocation();
			
		}
	}
	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"),TargetLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"),Target);
	//OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("CurrentTime"),0);
}
