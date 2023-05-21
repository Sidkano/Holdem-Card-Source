// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/NHDataBase.h"
#include "HandRankManagerBase.generated.h"

UCLASS()
class NFTHOLDEMGAME_API AHandRankManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandRankManagerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//�Լ�

	/* ī�� ����ü 5�� ¥�� �迭�� ������ ������ ŰĿ�� �������� */
	FPlayerData RankHand(const TArray<FCard> CardArray);

	/* � ������ ī�尡 �� �� ����ִ��� CardsCount�� �����ϴ� �Լ� */
	void MakeCardsCount(const TArray<FCard> cardArray);

	/* RankString�� ����� ���� ���� ī�� ���� ������������ �� ������ ī�� ����� ���� �� : 32000 */
	void CardCounting();

	/* �ڵ尡 ��Ʈ����Ʈ���� Ȯ�� */
	bool IsStraight();

	/* �ڵ尡 �÷������� Ȯ�� */
	bool IsFlush(TArray<FCard> CardArray);

	/* ������ ��� ���� ����� ŰĿ ����*/
	void SetTieBreaker();

	/* 2��, 5��, 6��, 7�� �� �� ���� �ְ��� �и� ã�Ƽ� �Է¹��� BestHand�� �������� 
	   ������ true, ���н� false ��ȯ */
	bool MakeBestHand(const TArray<FCard> IncludeCommunityCardHands, TArray<FCard> &BestHands);

	/* �ӽ� ������ �ʱ�ȭ */
	void InitializeTempCards();

	/* BestHand �������� �ʱ�ȭ �ϴ� �Լ� */
	void InitializeBestHand();

	/* TempHand �������� BestHand ������ �־��ִ� �Լ� */
	void SetBestHand();

	/* TempHand�� BestHand�� ���ϴ� �Լ�*/
	void VsBestHand();

	/* TieBreaker�� ���� �� �ٸ� ī��鵵 ���ϴ� �Լ�*/
	void TieBreakerSame();

	/* ������ ī����� ���� �� Ȯ���ϴ� �Լ� */
	void IsChop();

	/* �����, Ǯ�Ͽ콺 �� �� ExtraPair�� �߰��� �ϴ� �Լ�*/
	void IsChopWithTwoPair();

	/* Player Index Getter */
	int32 GetPlayerIndex();

	/* Player Index Setter */
	void SetPlayerIndex(int32 Index);

	/*rankTextOutput ����*/
	FText GetrankTextOutputText();


//����
	TArray<int32> TempCardsCount;
	FString RankString;
	FText RankTextOutput;
	EHandRank HandRank;
	int32 SequenceCounter;
	int32 TempHandRankInt;
	int32 TempTieBreaker;

	TArray<FString> StateTurnAllHandCase;
	TArray<FString> SelectHandAllCase;

	TArray<FCard> Hand;
	TArray<FCard> TempHand;
	TArray<FCard> TempBestHand;
	int32 TempBestTieBreaker;
	int32 TempBestHandRankInt;
	TArray<int32> TempHandExtraTieBreakers;
	TArray<int32> TempBestHandExtraTieBreakers;
	TArray<int32> TempBestHandCardsCount;

	int32 TempHandExtraTwoPairPower;
	int32 TempBestHandExtraTwoPairPower;

	int32 PlayerIndex;
};
