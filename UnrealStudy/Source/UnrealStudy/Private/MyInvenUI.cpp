// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Image.h"

void UMyInvenUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto array = Grid->GetAllChildren();

	for (auto widget : array)
	{
		auto image = Cast<UImage>(widget);
		if (image)
		{
			_slotImages.Add(image);
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Image Size : %d"), _slotImages.Num());

	auto item = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_seeds_06_b.Tex_seeds_06_b'"));
	_slotImages[0]->SetBrushFromTexture(item);
}
