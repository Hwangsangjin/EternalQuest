

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQSpiderWeb.generated.h"

UCLASS()
class ETERNALQUEST_API AEQSpiderWeb : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQSpiderWeb();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
};
