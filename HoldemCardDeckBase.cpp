// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldemCardDeckBase.h"

#include "HoldemCardBase.h"
#include "../../NFTHoldemGame.h"

#include "Components/SceneComponent.h"

#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AHoldemCardDeckBase::AHoldemCardDeckBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CardSpawnLoc = CreateDefaultSubobject<USceneComponent>(TEXT("CardSpawnLoc"));
	CardSpawnLoc->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHoldemCardDeckBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHoldemCardDeckBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//카드 스폰 이후 움직이게 하는 함수
AHoldemCardBase* AHoldemCardDeckBase::SpawnCardAndMove(FTransform CardTrans, const FCard CardInfo, bool CanSee, bool CanClick)
{
	AHoldemCardBase* TempCard = nullptr;

	if (HoldemCardClass)
	{
		FVector SpawnLoc = CardSpawnLoc->GetComponentLocation();
		FRotator SpawnRot = CardTrans.Rotator();

		//카드 스폰
		TempCard = GetWorld()->SpawnActor<AHoldemCardBase>(HoldemCardClass, SpawnLoc, SpawnRot);
		if (TempCard)
		{
			//스폰한 카드 저장
			SpawnedCardArray.Add(TempCard);

			//뒤집혀서 스폰
			if (SpawnRot.Roll > 1.f || SpawnRot.Roll < -1.f)
			{
				TempCard->IsRotate = true;
				NHLOG_WARNING(TEXT("IsRotate is true"));
			}

			//클릭, 보이기 변수 설정
			TempCard->SetCanClickAndSeeCard(CanSee, CanClick);

			//카드 숫자 문자 설정
			TempCard->SetCardTexture(CardInfo);

			//목표 위치 설정
			TempCard->SetSplineEndPoint_CPP(CardTrans.GetLocation());

			//카드 스케일 설정
			TempCard->SetCardScale(CardTrans);

			//움직이기
			TempCard->MoveCard_CPP(false, 4.f, 0); 

			return TempCard;
		}
	}

	return TempCard;
}

void AHoldemCardDeckBase::InitializeDeck() // 덱 초기화 시 설정
{
	FCard card;
	deck.Empty(); // 덱에 카드가 없는지 확인

	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			switch (i)
			{
			case 0:
				card.CardSuit = ECardShape::Spade;

				break;
			case 1:
				card.CardSuit = ECardShape::Clover;
				break;
			case 2:
				card.CardSuit = ECardShape::Heart;
				break;
			case 3:
				card.CardSuit = ECardShape::Diamond;
				break;
			default:
				break;
			}
			card.CardPower = j;	
			deck.Add(card);			
		}
	}

}

void AHoldemCardDeckBase::ShuffleDeck()
{
	int32 LastIndex = deck.Num() - 1;

	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
		{
			deck.Swap(i, Index);
		}
	}
}

FCard AHoldemCardDeckBase::GetDeckTopCard()
{
	FCard tempCard;
	tempCard = deck[0];
	deck.RemoveAt(0); //덱 맨 윗 카드를 삭제하도록 설정. 필요 없을시 주석처리

	NHLOG_WARNING(TEXT("%d %s, "), tempCard.CardPower, *NHDataBase::GetEnumNameToString(tempCard.CardSuit));

	//return deck.Pop(); //덱의 마지막 인덱스를 반환하려면 주석 해제.
	return tempCard; //덱의 첫번째 인덱스 삭제 후 반환
}

void AHoldemCardDeckBase::RotateAllSpawnCard()
{
	for (auto Elem : SpawnedCardArray)
	{
		//스폰한 모든 카드 뒤집기
		Elem->CardRotate();
	}
}

void AHoldemCardDeckBase::DestroyAllSpawnCard()
{
	//모든 카드 제거
	for (auto Elem : SpawnedCardArray)
	{
		Elem->Destroy();
	}
	SpawnedCardArray.Empty();
}
