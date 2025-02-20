// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTutoPawn.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyTutoPawn::AMyTutoPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // 동적 할당?
	RootComponent = _mesh;

	// 생성자에서
	// sm에 해당 경로의 UStaticMesh, object를 갖고오는 방법
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		sm(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));

	if (sm.Succeeded())
	{
		_mesh->SetStaticMesh(sm.Object);
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor!"));
}

// Called when the game starts or when spawned
void AMyTutoPawn::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Begin!"));
	
}

// Called every frame
void AMyTutoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Error, TEXT("Deltatime : %f"), DeltaTime);

	// DeltaTime : Update에 걸리는 시간

	if (GetAttachParentActor() == nullptr)
	{
		FVector curLocation = GetActorLocation();
		FVector destLocation = curLocation + FVector(_moveSpeed, 0, 0) * DeltaTime;
		SetActorLocation(destLocation);

		// Pitch(Y축), Yaw(Z축), Roll(X축)
		FRotator rot = FRotator(0, 1, 0);
		AddActorLocalRotation(rot * _rotSpeed * DeltaTime);
	}
	else
	{
		FVector parentV = GetAttachParentActor()->GetActorLocation();
		FVector myV = GetActorLocation(); // WorldLocation

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(myV, parentV);
		SetActorRotation(rot);
	}
}

// Called to bind functionality to input
void AMyTutoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 언리얼 이벤트 함수 실행 순서
//
//1️. Actor 생성
// 생성자(Constructor)
// PreInitializeComponents()
// PostInitializeComponents()
// 
//2️. 게임 시작
// BeginPlay()
//
//3️. 매 프레임마다
// Tick()
//
//4. Actor 제거
// EndPlay()
// Destroyed()


// C 언어의 printf() : 다양한 데이터 타입을 문자열로 변환해서 출력
// - 데이터 타입마다 변환 방식이 다름
// -> 형식 지정자(%d, %f, %s 등)를 사용
// 
// TEXT() : 언리얼 엔진에서 문자열을 안전하게 사용하기 위한 장치
// - C++에서는 기본적으로 문자열이 ANSI(1바이트)로 저장
// - 언리얼은 유니코드(2바이트)로 저장
// -> TEXT()를 이용해 문자열을 유니코드로 처리