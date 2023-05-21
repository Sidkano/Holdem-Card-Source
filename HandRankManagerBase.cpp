// Fill out your copyright notice in the Description page of Project Settings.


#include "HandRankManagerBase.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHandRankManagerBase::AHandRankManagerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TempCardsCount.Init(0, 15); //0 ~ 14까지 빈 배열생성
	TempHandRankInt = 20;
	TempBestHandRankInt = 20;

	SelectHandAllCase.Add("12345"); SelectHandAllCase.Add("12346"); SelectHandAllCase.Add("12347");
	SelectHandAllCase.Add("12356"); SelectHandAllCase.Add("12357"); SelectHandAllCase.Add("12367");
	SelectHandAllCase.Add("12456"); SelectHandAllCase.Add("12457"); SelectHandAllCase.Add("12467");
	SelectHandAllCase.Add("12567"); SelectHandAllCase.Add("13456"); SelectHandAllCase.Add("13457");
	SelectHandAllCase.Add("13467"); SelectHandAllCase.Add("13567"); SelectHandAllCase.Add("14567");
	SelectHandAllCase.Add("23456"); SelectHandAllCase.Add("23457"); SelectHandAllCase.Add("23467");
	SelectHandAllCase.Add("23567"); SelectHandAllCase.Add("24567"); SelectHandAllCase.Add("34567"); //모든 경우의 수 미리 등록

	StateTurnAllHandCase.Add("12345"); StateTurnAllHandCase.Add("12346"); StateTurnAllHandCase.Add("12356");
	StateTurnAllHandCase.Add("12456"); StateTurnAllHandCase.Add("13456"); StateTurnAllHandCase.Add("23456");//6가지 일때 경우의 수 미리 등록
}

// Called when the game starts or when spawned
void AHandRankManagerBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHandRankManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FPlayerData AHandRankManagerBase::RankHand(const TArray<FCard> CardArray)
{
	InitializeTempCards(); //임시 변수 초기화

	if (CardArray.Num() == 5 || CardArray.Num() == 2) //5장일 때와 2장일 때만 작동해야 함
	{
		MakeCardsCount(CardArray); //카드 숫자별로 장수가 저장되어있는 배열 생성
		CardCounting(); //카드 장수별로 내림차순 정렬된 문자열 생성 (핸드랭크 판단에 사용됨)

		if (TempCardsCount[14] == 1 && IsStraight() && IsFlush(CardArray)) //A가 있고 스트레이트고 플러쉬이면 로얄 스트레이트 플러쉬
		{
			RankString = "6ROFL";
			RankTextOutput = FText::FromString(TEXT("로얄 스트레이트 플러쉬"));
			HandRank = EHandRank::RoyalStraightFlush_1;
		}
		else if (IsFlush(CardArray) && IsStraight()) //스트레이트고 플러쉬이면 스트레이트 플러쉬
		{
			RankString = "5STFL";
			RankTextOutput = FText::FromString(TEXT("스트레이트 플러쉬"));
			HandRank = EHandRank::StraightFlush_2;
		}

		else if (IsStraight())
		{
			RankString = "312ST";
			RankTextOutput = FText::FromString(TEXT("스트레이트"));
			HandRank = EHandRank::Straight_6;
		}

		else if (IsFlush(CardArray))
		{
			RankString = "313FL";
			RankTextOutput = FText::FromString(TEXT("플러쉬"));
			HandRank = EHandRank::Flush_5;
		}
		// 각 케이스별로 족보 넣어주고 핸드랭킹 변경
		switch (UKismetStringLibrary::Conv_StringToInt(RankString))
		{
		case 11111:
		case 11000:
			RankTextOutput = FText::FromString(TEXT("하이카드")); //전부 한장씩인데 스트레이트가 아니라면
			HandRank = EHandRank::HighCard_10;
			break;
		case 20000:
		case 21110:
			RankTextOutput = FText::FromString(TEXT("원 페어")); //같은카드 두장이 있으면 원페어
			HandRank = EHandRank::OnePair_9;
			break;
		case 22100:
			RankTextOutput = FText::FromString(TEXT("투 페어")); //두 장씩 두 쌍이 나오면 투페어
			HandRank = EHandRank::TwoPair_8;
			break;
		case 31100:
			RankTextOutput = FText::FromString(TEXT("트리플")); //같은카드 세장이면 트리플
			HandRank = EHandRank::ThreeOfAKind_7;
			break;
		case 32000:
			RankTextOutput = FText::FromString(TEXT("풀하우스")); //같은카드 세장, 두장 조합이면 풀하우스
			HandRank = EHandRank::FullHouse_4;
			break;
		case 41000:
			RankTextOutput = FText::FromString(TEXT("포카드")); //같은카드 네장이면 포카드
			HandRank = EHandRank::FourOfAKind_3;
			break;
		default:
			break;
		}

		SetTieBreaker(); //족보가 비길때를 대비해 키커 설정

		FString LeftS; FString RightS;

		UKismetStringLibrary::Split(NHDataBase::GetEnumNameToString(HandRank), "_", LeftS, RightS);
		TempHandRankInt = UKismetStringLibrary::Conv_StringToInt(RightS); //핸드랭크 뒷부분 스플릿해서 넣어주기

		FPlayerData ReturnPlayerData; //반환용 변수

		ReturnPlayerData.handRankInt = TempHandRankInt;
		ReturnPlayerData.tieBreaker = TempTieBreaker;
		ReturnPlayerData.cardCount = TempCardsCount;
		ReturnPlayerData.playerIndex = PlayerIndex;
		ReturnPlayerData.bestHand = CardArray; 
		ReturnPlayerData.rankTextOutput = RankTextOutput.ToString();
		//반환용 변수에 데이터 저장.

		return ReturnPlayerData;
	}
	else //입력받은 cardArray가 2장 혹은 5장이 아님.
	{
		FPlayerData ReturnPlayerData;
		ReturnPlayerData.handRankInt = -1;
		ReturnPlayerData.tieBreaker = -1;
		ReturnPlayerData.playerIndex = PlayerIndex;
		ReturnPlayerData.bestHand.Empty();
		ReturnPlayerData.rankTextOutput = FString("Error");

		return ReturnPlayerData;
	}
}

void AHandRankManagerBase::MakeCardsCount(const TArray<FCard> cardArray)
{
	for (int i = 0; i < TempCardsCount.Num(); i++) //tempCardsCounts 전체를 돎.
	{
		for (int j = 0; j < cardArray.Num(); j++)
		{
			if (cardArray[j].CardPower == i)
			{
				TempCardsCount[i] = TempCardsCount[i] + 1;
			}
		}
	}
	if (TempCardsCount[2] == 1 && TempCardsCount[3] == 1 && TempCardsCount[4] == 1
		&& TempCardsCount[5] == 1 && TempCardsCount[14] == 1)
	{
		TempCardsCount[1] = 1;
		TempCardsCount[14] = 0;
	} //스트레이트 일 때 A가 1의 역할을 하도록


}

void AHandRankManagerBase::CardCounting()
{
	for (int i = 1; i < 5; i++) //한 숫자당 최대 나올수 있는 건 4장까지
	{
		for (int j = 1; j < 15; j++) //A가 14이므로 14번 돈다
		{
			if (TempCardsCount[j] == i)
			{
				RankString = RankString.Append(FString::FromInt(i)); //한 숫자당 몇장의 카드인지 저장
			}
		}
	}

	RankString = RankString.Reverse(); //내림차순으로 변경

	if (RankString.Len() == 1)
	{
		RankString = RankString.Append(FString::FromInt(0));
	}
	if (RankString.Len() == 2)
	{
		RankString = RankString.Append(FString::FromInt(0));
	}
	if (RankString.Len() == 3)
	{
		RankString = RankString.Append(FString::FromInt(0));
	}
	if (RankString.Len() == 4)
	{
		RankString = RankString.Append(FString::FromInt(0));
	} //5자리가 되도록 나머지 0으로 채움
}

//연속된 다섯장이 모두 한장씩 있으면 스트레이트, 단 한장이 시퀀서가 시작되고 한장이 아닌 카드가 발견되면 false
bool AHandRankManagerBase::IsStraight()
{
	for (int i = 0; i < TempCardsCount.Num(); i++)
	{
		if (TempCardsCount[i] == 1)
		{
			SequenceCounter++;
		}
		if (SequenceCounter > 0 && TempCardsCount[i] != 1)
		{
			break;
		}
	}

	if (SequenceCounter == 5)
	{
		return true;
	}

	return false;
}

//배열의 첫번째 문양과 나머지 카드의 문양이 전부 동일하면 플러쉬이다.
bool AHandRankManagerBase::IsFlush(TArray<FCard> CardArray)
{
	for (int i = 0; i < CardArray.Num(); i++)
	{
		if (CardArray[0].CardSuit == CardArray[i].CardSuit) {}
		else
		{
			return false;
		}
	}

	if (RankString == "20000" || RankString == "11000") //두장인 경우 일 때는 제외
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

void AHandRankManagerBase::SetTieBreaker() //족보에 따라 키커 설정
{
	switch (HandRank)
	{
	case EHandRank::RoyalStraightFlush_1:
		break; //가장강력한 패 이므로 타이 브레이커는 없다.
	case EHandRank::StraightFlush_2:
	case EHandRank::Flush_5:
	case EHandRank::Straight_6:
	case EHandRank::HighCard_10:
		for (int i = 0; i < TempCardsCount.Num(); i++)
		{
			if (TempCardsCount[i] != 0)
			{
				if (i > TempTieBreaker)
				{
					TempTieBreaker = i;
				}
			}
		}
		break; //스트레이트 플러쉬, 플러쉬, 스트레이트, 하이카드는 가장 높은 숫자가 키커가 된다.
	case EHandRank::TwoPair_8:
		for (int i = 0; i < TempCardsCount.Num(); i++)
		{
			if (TempCardsCount[i] == 2)
			{
				if (i > TempTieBreaker)
				{
					TempTieBreaker = i;
				}
			}
		}
		break; //투페어 일 땐 가장 높은 페어의 숫자가 키커가 된다.
	case EHandRank::FourOfAKind_3:
	case EHandRank::FullHouse_4:
	case EHandRank::ThreeOfAKind_7:
	case EHandRank::OnePair_9:
		int32 maxValue;
		UKismetMathLibrary::MaxOfIntArray(TempCardsCount, TempTieBreaker, maxValue); //가장 많이 나온 장수를 TieBreaker로 설정
	default:
		break;
	}
}

bool AHandRankManagerBase::MakeBestHand(const TArray<FCard> IncludeCommunityCardHands, TArray<FCard>& BestHands)
{
	if (IncludeCommunityCardHands.Num() == 2 ||
		IncludeCommunityCardHands.Num() == 5 ||
		IncludeCommunityCardHands.Num() == 6 ||
		IncludeCommunityCardHands.Num() == 7)
	{
		switch (IncludeCommunityCardHands.Num())
		{

		case 2:
			InitializeTempCards();
			RankHand(IncludeCommunityCardHands);
			BestHands = IncludeCommunityCardHands; //두장 일땐 경우의 수가 한가지 이므로 현재 핸드가 베스트핸드.
			break;

		case 5:
			InitializeTempCards();
			RankHand(IncludeCommunityCardHands);
			BestHands = IncludeCommunityCardHands; //다섯장 일 땐 경우의 수가 한가지 이므로 현재 핸드가 베스트핸드.
			break;

		case 6:
			for (int i = 0; i < StateTurnAllHandCase.Num(); i++)
			{
				TempHand.Empty();
				for (int j = 0; j < 5; j++)
				{
					TempHand.Add(IncludeCommunityCardHands[
						UKismetStringLibrary::Conv_StringToInt(
							UKismetStringLibrary::GetCharacterArrayFromString(StateTurnAllHandCase[i])[j]) - 1]);
					//6장 카드로 만드는 모든 경우가 저장된 배열중 하나를 뽑고
					//그 중 한자리씩 가져와 includeCommnunityCardHand에서 해당하는 번호에 맞는 카드를 tempHand에 추가해준다.

				}
				InitializeTempCards();
				RankHand(TempHand);
				VsBestHand();
				//해당 케이스의 핸드랭크와 역대 베스트 핸드와 비교해 높은 랭크의 패를 저장한다.
			}

			InitializeTempCards();
			RankHand(TempBestHand);

			BestHands = TempBestHand;
			break;

		case 7:
			for (int i = 0; i < SelectHandAllCase.Num(); i++)
			{
				TempHand.Empty();
				for (int j = 0; j < 5; j++)
				{
					TempHand.Add(IncludeCommunityCardHands[
						UKismetStringLibrary::Conv_StringToInt(
							UKismetStringLibrary::GetCharacterArrayFromString(SelectHandAllCase[i])[j]) - 1]);
					//7장 카드로 만드는 모든 경우가 저장된 배열중 하나를 뽑고
					//그 중 한자리씩 가져와 includeCommnunityCardHand에서 해당하는 번호에 맞는 카드를 tempHand에 추가해준다.
				}
				InitializeTempCards();
				RankHand(TempHand);
				VsBestHand();
				//해당 케이스의 핸드랭크와 역대 베스트 핸드와 비교해 높은 랭크의 패를 저장한다.
			}

			InitializeTempCards();
			RankHand(TempBestHand);

			BestHands = TempBestHand;
			break;

		default:
			break;
		}
		InitializeTempCards();
		InitializeBestHand();
		return true;
	}

	else
	{
		return false; // 입력값 오류로 false 반환
	}


}

void AHandRankManagerBase::InitializeTempCards() //TempCard 변수들 초기화
{
	TempCardsCount.Empty();
	TempCardsCount.Init(0, 15);
	SequenceCounter = 0;
	RankString = "";
	RankTextOutput = FText::FromString("");
	TempTieBreaker = 0;
	HandRank = EHandRank::HighCard_10;
	TempHandRankInt = 10;

}

void AHandRankManagerBase::InitializeBestHand() //BestHand 변수들 초기화
{
	TempBestHand.Empty();
	TempBestTieBreaker = 0;
	TempBestHandRankInt = 20;
	TempBestHandExtraTwoPairPower = 0;
	TempBestHandExtraTieBreakers.Empty();
	TempBestHandCardsCount.Empty();

}

void AHandRankManagerBase::SetBestHand() //BestHand에 변수 직접 지정
{
	TempBestHand = TempHand;
	TempBestTieBreaker = TempTieBreaker;
	TempBestHandCardsCount = TempCardsCount;
	TempBestHandRankInt = TempHandRankInt;
}

void AHandRankManagerBase::VsBestHand() //임시핸드와 베스트핸드를 비교해 강한걸 베스트핸드로 지정
{
	if (TempHandRankInt < TempBestHandRankInt)
	{
		SetBestHand();
		return;
	}
	else if (TempHandRankInt == TempBestHandRankInt)
	{
		if (TempTieBreaker > TempBestTieBreaker)
		{
			SetBestHand();
			return;
		}
		else if (TempTieBreaker == TempBestTieBreaker)
		{
			TieBreakerSame();
			return;
		}
	}
}

void AHandRankManagerBase::TieBreakerSame() //타이 브레이커가 같을 때 처리
{
	TempHandExtraTieBreakers.Empty();
	TempBestHandExtraTieBreakers.Empty();

	for (int i = 0; i < TempCardsCount.Num(); i++)
	{
		if (TempCardsCount[i] == 2)
		{
			TempHandExtraTwoPairPower = i;
		}
		else if (TempCardsCount[i] == 1)
		{
			TempHandExtraTieBreakers.Add(i);
		}
	}

	for (int i = 0; i < TempBestHandCardsCount.Num(); i++)
	{
		if (TempBestHandCardsCount[i] == 2)
		{
			TempBestHandExtraTwoPairPower = i;
		}
		else if (TempBestHandCardsCount[i] == 1)
		{
			TempBestHandExtraTieBreakers.Add(i);
		}
	}

	switch (HandRank)
	{
	case EHandRank::RoyalStraightFlush_1:
	case EHandRank::StraightFlush_2:
	case EHandRank::Straight_6:
		return;
		break;
	case EHandRank::Flush_5:
	case EHandRank::FourOfAKind_3:
	case EHandRank::OnePair_9:
	case EHandRank::ThreeOfAKind_7:
	case EHandRank::HighCard_10:
		IsChop();
		break;
	case EHandRank::FullHouse_4:
	case EHandRank::TwoPair_8:
		IsChopWithTwoPair();
		break;
	default:
		break;
	}
}

void AHandRankManagerBase::IsChop() //타이 브레이커가 같을 때 나머지 카드들 비교
{
	for (int i = 0; i < TempHandExtraTieBreakers.Num(); i++)
	{
		if (TempHandExtraTieBreakers[i] > TempBestHandExtraTieBreakers[i])
		{
			SetBestHand();
			return;
		}
		else if (TempHandExtraTieBreakers[i] < TempBestHandExtraTieBreakers[i])
		{
			return;
		}
		else if (TempHandExtraTieBreakers[i] == TempBestHandExtraTieBreakers[i])
		{
			continue;
		}
		else
		{
			return;
		}
	}
	return;
}

void AHandRankManagerBase::IsChopWithTwoPair() //풀하우스, 투페어 일 때 나머지 카드들 비교
{
	if (TempBestHandExtraTwoPairPower > TempHandExtraTwoPairPower)
	{
		return;
	}
	else if (TempBestHandExtraTwoPairPower < TempHandExtraTwoPairPower)
	{
		SetBestHand();
		return;
	}
	else if (TempBestHandExtraTwoPairPower == TempHandExtraTwoPairPower)
	{
		IsChop();
	}
	else
	{
		return;
	}
}

int32 AHandRankManagerBase::GetPlayerIndex()
{
	return PlayerIndex;
}

void AHandRankManagerBase::SetPlayerIndex(int32 Index)
{
	PlayerIndex = Index;
}

FText AHandRankManagerBase::GetrankTextOutputText()
{
	return RankTextOutput;
}
