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

//함수

	/* 카드 구조체 5장 짜리 배열을 넣으면 족보와 키커를 설정해줌 */
	FPlayerData RankHand(const TArray<FCard> CardArray);

	/* 어떤 숫자의 카드가 몇 장 들어있는지 CardsCount에 저장하는 함수 */
	void MakeCardsCount(const TArray<FCard> cardArray);

	/* RankString에 장수가 많은 종류 카드 부터 내림차순으로 그 종류의 카드 장수를 저장 예 : 32000 */
	void CardCounting();

	/* 핸드가 스트레이트인지 확인 */
	bool IsStraight();

	/* 핸드가 플러쉬인지 확인 */
	bool IsFlush(TArray<FCard> CardArray);

	/* 족보가 비길 때를 대비해 키커 설정*/
	void SetTieBreaker();

	/* 2장, 5장, 6장, 7장 일 때 가장 최고의 패를 찾아서 입력받은 BestHand에 설정해줌 
	   성공시 true, 실패시 false 반환 */
	bool MakeBestHand(const TArray<FCard> IncludeCommunityCardHands, TArray<FCard> &BestHands);

	/* 임시 변수들 초기화 */
	void InitializeTempCards();

	/* BestHand 변수들을 초기화 하는 함수 */
	void InitializeBestHand();

	/* TempHand 변수들을 BestHand 변수에 넣어주는 함수 */
	void SetBestHand();

	/* TempHand와 BestHand를 비교하는 함수*/
	void VsBestHand();

	/* TieBreaker가 같을 때 다른 카드들도 비교하는 함수*/
	void TieBreakerSame();

	/* 나머지 카드들이 비기는 지 확인하는 함수 */
	void IsChop();

	/* 투페어, 풀하우스 일 때 ExtraPair를 추가비교 하는 함수*/
	void IsChopWithTwoPair();

	/* Player Index Getter */
	int32 GetPlayerIndex();

	/* Player Index Setter */
	void SetPlayerIndex(int32 Index);

	/*rankTextOutput 게터*/
	FText GetrankTextOutputText();


//변수
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
