// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTService_SetFarthestTarget.h"

#include "EQAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"

UEQBTService_SetFarthestTarget::UEQBTService_SetFarthestTarget()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Set Farthest Target");
}

void UEQBTService_SetFarthestTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto* const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner());
	auto const * const Self = Controller->GetPawn();
	auto Target =  Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector TargetLoc = Target->GetActorLocation();
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEQCharacterPlayer::StaticClass(),AllPlayers);
	float Dist = Self->GetActorLocation().Length();
	for(int32 i = 0; i< AllPlayers.Num(); i++)
	{
		float TempDist = FVector::Dist(AllPlayers[i]->GetActorLocation(),Self->GetActorLocation());
		if(TempDist > Dist)
		{
			Dist = TempDist;
			Target = Cast<AEQCharacterPlayer>(AllPlayers[i]);
			TargetLoc = Target->GetActorLocation();
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("FarthestTargetLocation"),TargetLoc);
}
