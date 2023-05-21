// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldemCardBase.h"

// Sets default values
AHoldemCardBase::AHoldemCardBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoldemCardBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoldemCardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHoldemCardBase::SetCanClickAndSeeCard(bool canClicked, bool canSee) //카드 옵션 세팅 함수
{
	CanClickCard = canClicked;
	CanSeeCard = canSee;
}


