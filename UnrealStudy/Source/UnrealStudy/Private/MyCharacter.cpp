// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

#include "MyGameInstance.h"
#include "MyAnimInstance.h"
#include "MyPlayerController.h"
#include "MyStatComponent.h"
#include "MyItem.h"
#include "MyEffect.h"

#include "Engine/DamageEvents.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// bluePrint에서 SkeletalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_statComponent = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (_animInstance == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AnimInstance did not exist."));

	// Delegate 바인딩 연습
	_animInstance->_attackStart.BindUObject(this, &AMyCharacter::TestDelegate);
	_animInstance->_attackStart2.BindUObject(this, &AMyCharacter::TestDelegate2);
	_animInstance->_attackStart3.AddDynamic(this, &AMyCharacter::TestDelegate);

	_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::AttackEnd);
	_animInstance->_hitEvent.AddDynamic(this, &AMyCharacter::Attack_Hit);
	_animInstance->_deadEvent.AddDynamic(this, &AMyCharacter::DeadEvent);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::TestDelegate()
{
	UE_LOG(LogTemp, Log, TEXT("Attack Start Delegate Test"));
}

int32 AMyCharacter::TestDelegate2(int32 a, int32 b)
{
	UE_LOG(LogTemp, Log, TEXT("Speed : %d, IsFalling : %d"), a, b);

	return -1;
}

void AMyCharacter::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttack = false;
}

void AMyCharacter::Attack_Hit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 100.0f;
	//FQuat quat = FQuat(GetActorRightVector(), FMath::DegreesToRadians(90));

	FVector forward = GetActorForwardVector();
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward);

	FVector center = GetActorLocation() + forward * _attackRange * 0.5f;
	FVector start = GetActorLocation();  // 충돌체의 중심 start
	FVector end = GetActorLocation() + forward * _attackRange; // 충돌체의 중심 end

	bool bResult = GetWorld()->SweepSingleByChannel
	( // Sweep : start부터 end까지 물고 가는 형태의 충돌 판정
		OUT hitResult,
		center,
		center,
		quat,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, _attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		AMyCharacter* victim = Cast<AMyCharacter>(hitResult.GetActor());

		if (victim)
		{
			FDamageEvent damageEvent = FDamageEvent();

			FVector hitPoint = hitResult.ImpactPoint;
			EFFECT_M->PlayEffect("SparrowHit", hitPoint);
			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		}
	}

	DrawDebugCapsule(GetWorld(), center,
		_attackRange * 0.5f, attackRadius, quat, drawColor, false, 1.0f);
}

void AMyCharacter::DeadEvent()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Controller->UnPossess();
}

void AMyCharacter::AddHp(float Amount)
{
	_statComponent->AddCurHp(Amount);
}

void AMyCharacter::SubtractHp(float Amount)
{
	_statComponent->AddCurHp(-Amount);
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	_statComponent->AddCurHp(-Damage);

	auto attackerController = Cast<AMyPlayerController>(EventInstigator);

	if (attackerController)
	{
		if (IsDead())
		{
			UE_LOG(LogTemp, Error, TEXT("Be Dead by Player"));
		}
	}

	return Damage;
}

bool AMyCharacter::IsDead()
{
	return _statComponent->IsDead();
}
