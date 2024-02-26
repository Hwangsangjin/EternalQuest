// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Character/EQBerserkerOrc.h"




AEQAIController::AEQAIController(FObjectInitializer const& ObjectInitializer)
{
	bReplicates = true;
}

void AEQAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(AEQBerserkerOrc* Orc = Cast<AEQBerserkerOrc>(InPawn))
	{
		if(UBehaviorTree* const Tree = Orc->GetBehaviorTree())
		{
			UBlackboardComponent* BlackBoardComp;
			UseBlackboard(Tree->BlackboardAsset,BlackBoardComp);
			Blackboard = BlackBoardComp;
			RunBehaviorTree(Tree); 
		}
	}
	
}
