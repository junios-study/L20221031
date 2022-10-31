// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class L20221031_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void ProcessHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void ProcessOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ProcessOverlap2(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Pitch(float Value);

	void Roll(float Value);

	void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TSubclassOf<class AMyActor> RocketTemplate;
	//TSoftClassPtr<class AMyActor> RocketTemplate;
		
	//������ BP, ����� C++
	UFUNCTION(BlueprintImplementableEvent)
	void MakeBlueprint();

	//������ BP, ����� C++, �� �⺻ ���� C++
	UFUNCTION(BlueprintNativeEvent)
	void MakeOverrideBlueprint();
	void MakeOverrideBlueprint_Implementation();

	//C++ ����, ȣ���� BP����
	//UFUNCTION(BlueprintCallable)
	UFUNCTION(BlueprintCallable)
	void CallBlueprint();


};
