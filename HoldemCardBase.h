// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/NHDataBase.h"
#include "HoldemCardBase.generated.h"

UCLASS()
class NFTHOLDEMGAME_API AHoldemCardBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoldemCardBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//�Լ�
	UFUNCTION(BlueprintImplementableEvent)
		/*���ö��� EndPoint ��� - ������*/
		void SetSplineEndPoint_CPP(FVector EndLoc);

	UFUNCTION(BlueprintImplementableEvent)
		/*ī�� �����̱� ������*/
		void MoveCard_CPP(bool ReverseMove, float CardSpeed, int32 CardIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		/*�ؽ�ó �ٲٱ� ������*/
		void SetCardTexture(FCard Card);

	/*Ŭ��, see ���� ����*/
	void SetCanClickAndSeeCard(bool canClicked, bool canSee);

	UFUNCTION(BlueprintImplementableEvent)
	/*ī�� ȸ�� ��Ű��*/
	void CardRotate();

	UFUNCTION(BlueprintImplementableEvent)

	/* ī�� ũ�� ���� */
	void SetCardScale(FTransform transform);

	UFUNCTION(BlueprintImplementableEvent)
		/*ī�� ������*/
		void CardRotate_180();

	UFUNCTION(BlueprintImplementableEvent)
		/*ī�� �ø���*/
		void CardLocationOffset(FVector AddOffset);

	UFUNCTION(BlueprintImplementableEvent)
		/*ī�� ����Ʈ ����*/
		void CardEffectActive();

//����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*������ �� üũ*/
		bool CanClickCard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*ī�带 �� �� �ִ��� üũ*/
		bool CanSeeCard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*ī�带 ȸ����ų �� �ִ��� üũ*/
		bool IsRotate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*ī���� ������ üũ�ϴ� ����ü*/
		FCard MyData;
};
