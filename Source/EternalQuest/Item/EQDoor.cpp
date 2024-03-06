


#include "Item/EQDoor.h"

AEQDoor::AEQDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	Door1 = CreateDefaultSubobject<UStaticMeshComponent>("Door1");
	Door1 -> SetupAttachment(SceneComponent);
	Door1-> SetRelativeLocation(FVector(177.f,14.f,142.f));
	Door2 = CreateDefaultSubobject<UStaticMeshComponent>("Door2");
	Door2 -> SetupAttachment(SceneComponent);
	Door2-> SetRelativeLocation(FVector(622.f,14.f,142.f));
	Door3 = CreateDefaultSubobject<UStaticMeshComponent>("Door3");
	Door3 -> SetupAttachment(SceneComponent);

}

void AEQDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEQDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

