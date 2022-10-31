// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Mesh(TEXT("StaticMesh'/Game/P38/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Mesh.Succeeded())
	{
		Body->SetStaticMesh(SM_Mesh.Object);
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentHit.AddDynamic(this, &AMyActor::ProcessHit);
	Box->OnComponentHit.RemoveDynamic(this, &AMyActor::ProcessHit);

}

void AMyActor::ProcessHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogClass, Warning, TEXT("Hit"));

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

