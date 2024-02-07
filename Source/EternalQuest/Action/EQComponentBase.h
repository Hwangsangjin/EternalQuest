
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EQComponentBase.generated.h"

class AEQCharacterPlayer;
class AEQPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEQComponentBase();
	// ----- Override 함수 -----
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent);
	// ----- Override 함수 -----

	// ----- 함수 -----
	// ----- 함수 -----
	
	// ----- 변수 -----
	UPROPERTY()
	TObjectPtr<AEQCharacterPlayer> Player;

	UPROPERTY()
	TObjectPtr<AEQPlayerController> PlayerController;
	// ----- 변수 -----
};
