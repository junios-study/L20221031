// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Mesh.Succeeded())
	{
		Body->SetStaticMesh(SM_Mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Right->SetStaticMesh(SM_Propeller.Object);
		Left->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	//#include "BP_Rocket"
	static ConstructorHelpers::FClassFinder<AActor> BP_Rocket(TEXT("Blueprint'/Game/Blueprints/BP_Rocket.BP_Rocket_C'"));
	if (BP_Rocket.Succeeded())
	{
		RocketTemplate = BP_Rocket.Class;
	}


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AMyPawn::ProcessOverlap2);
	OnActorBeginOverlap.AddDynamic(this, &AMyPawn::ProcessOverlap);
	OnActorBeginOverlap.RemoveAll(this);

	Box->OnComponentHit.AddDynamic(this, &AMyPawn::ProcessHit);
	Box->OnComponentHit.RemoveDynamic(this, &AMyPawn::ProcessHit);
}

void AMyPawn::ProcessHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogClass, Warning, TEXT("Hit"));

}

void AMyPawn::ProcessOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogClass, Warning, TEXT("Overlap"));
}

void AMyPawn::ProcessOverlap2(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogClass, Warning, TEXT("Overlap2"));
}


// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Left->AddLocalRotation(FRotator(0,
		0,
		3600 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()))
	);
	Right->AddLocalRotation(FRotator(0,
		0,
		3600 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()))
	);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
}



void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(
		Value * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		0,
		0
	));
}


void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(
		0,
		0,
		Value * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()))
	);
}

void AMyPawn::Fire()
{
	//여기는 블프프린트로 구현한 함수 호출
	//GetWorld()->SpawnActor<AActor>(RocketTemplate);
	//MakeBlueprint();
	MakeOverrideBlueprint();
}

void AMyPawn::MakeOverrideBlueprint_Implementation()
{
	GetWorld()->SpawnActor<AActor>(RocketTemplate);
}

void AMyPawn::CallBlueprint()
{
	UE_LOG(LogClass, Warning, TEXT("Call Blueprint"));
}
