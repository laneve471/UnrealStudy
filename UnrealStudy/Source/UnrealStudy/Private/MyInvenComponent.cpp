// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenComponent.h"

// Sets default values for this component's properties
UMyInvenComponent::UMyInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_items.SetNum(9);
}


// Called when the game starts
void UMyInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FMyItemInfo UMyInvenComponent::GetItemInfo_Index(int32 index)
{
	if (index < 0 || index >= _items.Num())
		return FMyItemInfo();

	if (_items[index] == nullptr)
		return FMyItemInfo();

	return _items[index]->GetInfo();
}

void UMyInvenComponent::AddItem(AMyItem* item)
{
	auto target = _items.IndexOfByPredicate([](AMyItem* item)->bool
		{
			if (item == nullptr)
				return true;
			return false;
		});
	
	if (target == INDEX_NONE)
		return;

	_items[target] = item;

	if (itemAddEvent.IsBound())
		itemAddEvent.Broadcast(target, item->GetInfo());
	// Info를 주는 이유 -> UI 세팅
}

AMyItem* UMyInvenComponent::DropItem()
{
	return nullptr;
}

AMyItem* UMyInvenComponent::DropItem(int32 index)
{

	FMyItemInfo noneInfo;

	if (index >= _items.Num() || index < 0)
		return nullptr;

	if (_items[index] == nullptr)
		return nullptr;

	AMyItem* dropItem = _items[index];
	_items[index] = nullptr;
	//GetOwner() -> Player
	// => Cast<MyPlayer>
	// => Drop함수 호출
	// player->DropItem(dropItem)

	// ItemDropEvent
	// => MyPlayer의 Drop함수를 바인딩해서 간접호출

	return dropItem;
}

