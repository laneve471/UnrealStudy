// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

#include "MyInvenUI.h"

void UMyButton::SetCurIndex()
{
	if (widget == nullptr)
		return;

	widget->_curIndex = _buttonIndex;
}
