// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EQItemPreview.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
AEQItemPreview::AEQItemPreview()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SceneCaptureCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture"));
	SetRootComponent(SceneCaptureCam);
	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetRelativeLocation(FVector(50,0,0));
	MeshComp->SetVisibleInSceneCaptureOnly(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Tree_And_Box/Mesh/SM_Box.SM_Box"));
	if (MeshRef.Succeeded()) MeshComp->SetStaticMesh(MeshRef.Object);

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTargetRef(TEXT("/Game/Blueprints/RenderTarget/RT_Item.RT_Item"));
	if (RenderTargetRef.Succeeded()) MyRenderTarget = RenderTargetRef.Object;

	MeshComp->SetCastShadow(false);
}

// Called when the game starts or when spawned
void AEQItemPreview::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEQItemPreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

