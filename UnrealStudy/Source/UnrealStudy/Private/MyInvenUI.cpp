// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "MyButton.h"
#include "MyInvenComponent.h"

bool UMyInvenUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UMyButton>(widget);

		if (button)
		{
			button->OnClicked.AddDynamic(button, &UMyButton::SetCurIndex);
			button->OnClicked.AddDynamic(this, &UMyInvenUI::SetTextBox);
			button->widget = this;
			button->_buttonIndex = index;
			index++;
		}

		auto image = Cast<UImage>(button->GetChildAt(0));
		if (image)
		{
			_slotImages.Add(image);
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Image Size : %d"), _slotImages.Num());

	_potionTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_seeds_06.Tex_seeds_06'"));
	_defaultTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_empty.Tex_empty'"));

	return true;
}

void UMyInvenUI::SetItem_Index(int32 index, FMyItemInfo info)
{
	if (info.itemId == -1 && info.type == MyItemType::NONE)
		_slotImages[index]->SetBrushFromTexture(_defaultTexture);

	if (info.itemId == 1 && info.type == MyItemType::POTION)
		_slotImages[index]->SetBrushFromTexture(_potionTexture);
}

void UMyInvenUI::SetTextBox()
{
	if (_invenComponent == nullptr)
		return;

	auto info = _invenComponent->GetItemInfo_Index(_curIndex);

	if (info.itemId == -1 && info.type == MyItemType::NONE)
	{
		ItemInfo->SetText(FText::FromString(TEXT("ItemType : NONE \n ItemID : -1")));
	}
	if (info.itemId == 1 && info.type == MyItemType::POTION)
	{
		ItemInfo->SetText(FText::FromString(TEXT("ItemType : POTION \n ItemID : 1")));
	}
}
