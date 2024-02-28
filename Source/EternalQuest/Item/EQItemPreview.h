// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQItemPreview.generated.h"

UCLASS()
class ETERNALQUEST_API AEQItemPreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEQItemPreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(EditDefaultsOnly, Blueprintreadwrite)
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureCam;

	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> MyRenderTarget;
};
