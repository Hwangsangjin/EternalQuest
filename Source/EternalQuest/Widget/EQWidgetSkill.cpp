// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetSkill.h"

UEQWidgetSkill::UEQWidgetSkill(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> SkillPointClickSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Assets/RPG_Interface_SFX/WAV/Interaction_With_Magic_Gem.Interaction_With_Magic_Gem'"));
	if (SkillPointClickSoundRef.Succeeded())
	{
		SkillPointClickSound = SkillPointClickSoundRef.Object;
	}
}

void UEQWidgetSkill::NativeConstruct()
{
	Super::NativeConstruct();
}
