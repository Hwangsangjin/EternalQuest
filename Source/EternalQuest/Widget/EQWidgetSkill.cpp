// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetSkill.h"

#include "Component/EQComponentInventory.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Game/EQGameInstance.h"
#include "GameFramework/Character.h"

UEQWidgetSkill::UEQWidgetSkill(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> SkillPointClickSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Assets/RPG_Interface_SFX/WAV/Interaction_With_Magic_Gem.Interaction_With_Magic_Gem'"));
	if (SkillPointClickSoundRef.Succeeded())
	{
		SkillPointClickSound = SkillPointClickSoundRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_Keyboard1Ref(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_147.icon_controller_147'"));
	if (Img_Keyboard1Ref.Succeeded()) Img_Keyboard1 = Img_Keyboard1Ref.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_Keyboard2Ref(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_148.icon_controller_148'"));
	if (Img_Keyboard2Ref.Succeeded()) Img_Keyboard2 = Img_Keyboard2Ref.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_Keyboard3Ref(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_149.icon_controller_149'"));
    	if (Img_Keyboard3Ref.Succeeded()) Img_Keyboard3 = Img_Keyboard3Ref.Object;
    	
	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_Keyboard4Ref(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_150.icon_controller_150'"));
	if (Img_Keyboard4Ref.Succeeded()) Img_Keyboard4 = Img_Keyboard4Ref.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_Keyboard5Ref(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_151.icon_controller_151'"));
	if (Img_Keyboard5Ref.Succeeded()) Img_Keyboard5 = Img_Keyboard5Ref.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_MouseLeftClickRef(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_194.icon_controller_194'"));
	if (Img_MouseLeftClickRef.Succeeded()) Img_MouseLeftClick = Img_MouseLeftClickRef.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> Img_MouseRightClickRef(TEXT("/Script/Engine.Texture2D'/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_controller/icon_controller_196.icon_controller_196'"));
	if (Img_MouseRightClickRef.Succeeded()) Img_MouseRightClick = Img_MouseRightClickRef.Object;
}

void UEQWidgetSkill::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSkillPnt();

	// 내가 선택한 클래스 타입에 따라, 스킬창이 뜨게 표시
	auto EQClassType = Cast<UEQGameInstance>(GetGameInstance())->GetClassType();
	if (EQClassType == EClassType::ECT_Warrior)
	{
		Txt_JobName->SetText(FText::FromString(TEXT("Warrior")));
		WS_SwitchSkillWindow->SetActiveWidgetIndex(0);
	}
	else if (EQClassType == EClassType::ECT_Mage)
	{
		Txt_JobName->SetText(FText::FromString(TEXT("Mage")));
		WS_SwitchSkillWindow->SetActiveWidgetIndex(1);
	}

	// 워리어 스킬 버튼 바인딩 모음
	Btn_WarriorSkill1->OnHovered.AddDynamic(this, &ThisClass::OnHoveredWarriorSkill1);
	Btn_WarriorSkill2->OnHovered.AddDynamic(this, &ThisClass::OnHoveredWarriorSkill2);
	Btn_WarriorSkill3->OnHovered.AddDynamic(this, &ThisClass::OnHoveredWarriorSkill3);
	Btn_WarriorSkill4->OnHovered.AddDynamic(this, &ThisClass::OnHoveredWarriorSkill4);
	Btn_WarriorSkill5->OnHovered.AddDynamic(this, &ThisClass::OnHoveredWarriorSkill5);

	Btn_WarriorSkill1->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_WarriorSkill2->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_WarriorSkill3->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_WarriorSkill4->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_WarriorSkill5->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);

	Btn_WarriorSkill1->OnClicked.AddDynamic(this, &ThisClass::OnClickedWarriorSkill1);
	Btn_WarriorSkill2->OnClicked.AddDynamic(this, &ThisClass::OnClickedWarriorSkill2);
	Btn_WarriorSkill3->OnClicked.AddDynamic(this, &ThisClass::OnClickedWarriorSkill3);
	Btn_WarriorSkill4->OnClicked.AddDynamic(this, &ThisClass::OnClickedWarriorSkill4);
	Btn_WarriorSkill5->OnClicked.AddDynamic(this, &ThisClass::OnClickedWarriorSkill5);
	// 워리어 스킬 버튼 바인딩 모음

	// 메이지 스킬 버튼 바인딩 모음
	Btn_MageSkill1->OnHovered.AddDynamic(this, &ThisClass::OnHoveredMageSkill1);
	Btn_MageSkill2->OnHovered.AddDynamic(this, &ThisClass::OnHoveredMageSkill2);
	Btn_MageSkill3->OnHovered.AddDynamic(this, &ThisClass::OnHoveredMageSkill3);
	Btn_MageSkill4->OnHovered.AddDynamic(this, &ThisClass::OnHoveredMageSkill4);
	Btn_MageSkill5->OnHovered.AddDynamic(this, &ThisClass::OnHoveredMageSkill5);
	
	Btn_MageSkill1->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_MageSkill2->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_MageSkill3->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_MageSkill4->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);
	Btn_MageSkill5->OnHovered.AddDynamic(this, &ThisClass::ClearSkillText);

	Btn_MageSkill1->OnClicked.AddDynamic(this, &ThisClass::OnClickedMageSkill1);
	Btn_MageSkill2->OnClicked.AddDynamic(this, &ThisClass::OnClickedMageSkill2);
	Btn_MageSkill3->OnClicked.AddDynamic(this, &ThisClass::OnClickedMageSkill3);
	Btn_MageSkill4->OnClicked.AddDynamic(this, &ThisClass::OnClickedMageSkill4);
	Btn_MageSkill5->OnClicked.AddDynamic(this, &ThisClass::OnClickedMageSkill5);
	// 메이지 스킬 버튼 바인딩 모음
}

void UEQWidgetSkill::UpdateSkillPnt()
{
	Txt_SkillPnt->SetText(FText::FromString(FString::Printf(TEXT("Skill Point : %d"), EQSkill.SkillPnt)));
	
	Txt_WarriorSkill1Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_WarriorSkill1)));
	Txt_WarriorSkill2Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_WarriorSkill2)));
	Txt_WarriorSkill3Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_WarriorSkill3)));
	Txt_WarriorSkill4Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_WarriorSkill4)));
	Txt_WarriorSkill5Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_WarriorSkill5)));

	Txt_MageSkill1Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_MageSkill1)));
	Txt_MageSkill2Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_MageSkill2)));
	Txt_MageSkill3Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_MageSkill3)));
	Txt_MageSkill4Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_MageSkill4)));
	Txt_MageSkill5Pnt->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSkill.Pnt_MageSkill5)));
}

void UEQWidgetSkill::ClearSkillText()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("")));
	Img_SkillShortCut->SetRenderOpacity(0);
}

void UEQWidgetSkill::OnHoveredWarriorSkill1()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("용기의 함성을 내질러, 두려움을 없애고 공격력을 증가시킨다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 2")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard2);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredWarriorSkill2()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("검을 크게 내려찍어, 3단 충격파를 일으킨다")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 3"))); 
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard3);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredWarriorSkill3()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("용기의 함성을 내질러, 두려움을 없애고 공격력을 증가시킨다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 4")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard4);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredWarriorSkill4()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("높게 점프하여 검으로 적을 내리찍는다")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 1")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard1);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredWarriorSkill5()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("크게 회전하는 소용돌이를 일으킨다. \n 연속으로 사용 가능하다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Mouse : 우클릭")));
	Img_SkillShortCut->SetBrushFromTexture(Img_MouseRightClick);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnClickedWarriorSkill1()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_WarriorSkill1 < 20)
	{
		EQSkill.Pnt_WarriorSkill1++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedWarriorSkill2()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_WarriorSkill2 < 20)
	{
		EQSkill.Pnt_WarriorSkill2++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedWarriorSkill3()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_WarriorSkill3 < 20)
	{
		EQSkill.Pnt_WarriorSkill3++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedWarriorSkill4()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_WarriorSkill4 < 20)
	{
		EQSkill.Pnt_WarriorSkill4++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedWarriorSkill5()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_WarriorSkill5 < 20)
	{
		EQSkill.Pnt_WarriorSkill5++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnHoveredMageSkill1()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("이공간에 잠시 머무르는 주문을 외우며 순간이동 한다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 1")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard1);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredMageSkill2()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("우주의 기운을 모아 운석을 소환하여 내리찍는다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 2")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard2);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredMageSkill3()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("적란운을 생성하여 번개를 내리친다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Keyborad : 3")));
	Img_SkillShortCut->SetBrushFromTexture(Img_Keyboard3);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredMageSkill4()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("파이어볼을 연속으로 발사한다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Mouse : 좌클릭")));
	Img_SkillShortCut->SetBrushFromTexture(Img_MouseLeftClick);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnHoveredMageSkill5()
{
	Txt_SkillDetail->SetText(FText::FromString(TEXT("화염주문을 충전하여 큰 파이어볼을 발사한다.")));
	Txt_SkillShortCut->SetText(FText::FromString(TEXT("Mouse : 좌클릭 충전 후 떼기")));
	Img_SkillShortCut->SetBrushFromTexture(Img_MouseLeftClick);
	Img_SkillShortCut->SetRenderOpacity(1);
}

void UEQWidgetSkill::OnClickedMageSkill1()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_MageSkill1 < 20)
	{
		EQSkill.Pnt_MageSkill1++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();
		
		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedMageSkill2()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_MageSkill2 < 20)
	{
		EQSkill.Pnt_MageSkill2++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedMageSkill3()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_MageSkill3 < 20)
	{
		EQSkill.Pnt_MageSkill3++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedMageSkill4()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_MageSkill4 < 20)
	{
		EQSkill.Pnt_MageSkill4++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}

void UEQWidgetSkill::OnClickedMageSkill5()
{
	if (EQSkill.SkillPnt > 0 && EQSkill.Pnt_MageSkill5 < 20)
	{
		EQSkill.Pnt_MageSkill5++;
		EQSkill.SkillPnt--;
		UpdateSkillPnt();

		auto SaveComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		SaveComp->SaveInventory();
	}
}
