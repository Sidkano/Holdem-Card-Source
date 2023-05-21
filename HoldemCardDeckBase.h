// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/NHDataBase.h"
#include "HoldemCardDeckBase.generated.h"


UCLASS()
class NFTHOLDEMGAME_API AHoldemCardDeckBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoldemCardDeckBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* Root; // ī�� ��Ʈ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* CardSpawnLoc; // ī�� ������ ��ġ�� ���� ����


//�Լ�
	UFUNCTION(BlueprintCallable)
		/*ī�� ���� �� �����̱�*/
		AHoldemCardBase* SpawnCardAndMove(FTransform CardTrans, const FCard CardInfo, bool CanSee, bool CanClick);

		/* �� �ʱ�ȭ �� ���� */
	UFUNCTION(BlueprintCallable)
	void InitializeDeck();

		/* �� ���� */
	UFUNCTION(BlueprintCallable)
	void ShuffleDeck();

	UFUNCTION(BlueprintCallable)
	FCard GetDeckTopCard(); // �ֻ��� ī�� ���ϴ� �Լ�

	/*��� ī�� ������*/
	void RotateAllSpawnCard();

	/*��� ī�� ����*/
	void DestroyAllSpawnCard();

//���۷���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ref")
		/*Ȧ�� ī�� Ŭ���� ���۷���*/
		TSubclassOf<class AHoldemCardBase> HoldemCardClass;

//����
	TArray<FCard> deck;

	/*������ ī�� �迭*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AHoldemCardBase*> SpawnedCardArray;
};
