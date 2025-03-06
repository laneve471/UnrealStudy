// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyPlayerController.h"
#include "MyAnimInstance.h"
#include "MyStatComponent.h"

#include "Blueprint/Userwidget.h"
#include "Components/Button.h"
#include "MyInvenComponent.h"
#include "MyInvenUI.h"
#include "MyItem.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	// Inventory
	static ConstructorHelpers::FClassFinder<UMyInvenUI> invenClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyInvenUI.BP_MyInvenUI_C'"));
	if (invenClass.Succeeded())
	{
		_invenWidget = CreateWidget<UUserWidget>(GetWorld(), invenClass.Class);
	}

	_invenComponent = CreateDefaultSubobject<UMyInvenComponent>(TEXT("InvenComponent"));
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto invenUI = Cast<UMyInvenUI>(_invenWidget);
	if (invenUI)
	{
		_invenComponent->itemAddEvent.AddUObject(invenUI, &UMyInvenUI::SetItem_Index);
		invenUI->Drop->OnClicked.AddDynamic(this, &AMyPlayer::DropItem);
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		enhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		enhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &AMyPlayer::JumpA);
		enhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Triggered, this, &AMyPlayer::Attack);
		enhancedInputComponent->BindAction(_invenAction, ETriggerEvent::Started, this, &AMyPlayer::InvenOnOff);
	}
}

void AMyPlayer::Move(const FInputActionValue& value)
{
	if (_isAttack) return;

	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			FVector forward = GetActorForwardVector();
			FVector right = GetActorRightVector();

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forward, moveVector.Y * _statComponent->GetSpeed());
			AddMovementInput(right, moveVector.X * _statComponent->GetSpeed());
		}
	}
}

void AMyPlayer::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(-lookAxisVector.Y);
	}
}

void AMyPlayer::JumpA(const FInputActionValue& value)
{
	if (_isAttack) return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		ACharacter::Jump();
	}
}

void AMyPlayer::Attack(const FInputActionValue& value)
{
	if (_isAttack) return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		_isAttack = true;

		_curAttackSection = (_curAttackSection + 1) % 3;
		_animInstance->PlayAnimMontage();
		_animInstance->JumpToSection(_curAttackSection + 1);
	}
}

void AMyPlayer::InvenOnOff(const FInputActionValue& value)
{
	bool isPress = value.Get<bool>();

	if (isPress)
	{
		auto controller = Cast<AMyPlayerController>(GetController());

		if (_isInvenOpen)
		{
			if (controller)
				controller->HideUI();
			_invenWidget->RemoveFromViewport();
		}
		else
		{
			if (controller)
				controller->ShowUI();
			_invenWidget->AddToViewport();
		}

		_isInvenOpen = !_isInvenOpen;
	}
}

void AMyPlayer::AddItem(AMyItem* item)
{
	// TODO
	if (item && _invenComponent)
	{
		auto info = item->GetInfo();
		_invenComponent->AddItem(info.itemId, info.type);
	}
}

void AMyPlayer::DropItem()
{
	UE_LOG(LogTemp, Error, TEXT("Drop"));
}
