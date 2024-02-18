

#pragma once

#include "CoreMinimal.h"
#include "AI/EQBaseFSM.h"
#include "EQRangerFSM.generated.h"


class AEQSpiderWeb;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQRangerFSM : public UEQBaseFSM
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	
	virtual void ShootWeb() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEQSpiderWeb> WebFactory;


	UFUNCTION(Server,Reliable)
	void ServerRPC_SpiderMove();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_SpiderMove();
	UFUNCTION(Server,Reliable)
	void ServerRPC_SpiderAttack();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_SpiderAttack();
};
