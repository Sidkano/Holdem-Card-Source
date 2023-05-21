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

AHoldemCardBase* AHoldemCardDeckBase::SpawnCardAndMove(FTransform CardTrans, const FCard CardInfo, bool CanSee, bool CanClick)
{
	AHoldemCardBase* TempCard = nullptr;

	if (HoldemCardClass)
	{
		FVector SpawnLoc = CardSpawnLoc->GetComponentLocation();
		FRotator SpawnRot = CardTrans.Rotator();

		//ī�� ����
		TempCard = GetWorld()->SpawnActor<AHoldemCardBase>(HoldemCardClass, SpawnLoc, SpawnRot);
		if (TempCard)
		{
			//������ ī�� ����
			SpawnedCardArray.Add(TempCard);

			//�������� ����
			if (SpawnRot.Roll > 1.f || SpawnRot.Roll < -1.f)
			{
				TempCard->IsRotate = true;
				NHLOG_WARNING(TEXT("IsRotate is true"));
			}

			//Ŭ��, ���̱� ���� ����
			TempCard->SetCanClickAndSeeCard(CanSee, CanClick);

			//ī�� ���� ���� ����
			TempCard->SetCardTexture(CardInfo);

			//��ǥ ��ġ ����
			TempCard->SetSplineEndPoint_CPP(CardTrans.GetLocation());

			//ī�� ������ ����
			TempCard->SetCardScale(CardTrans);

			//�����̱�
			TempCard->MoveCard_CPP(false, 4.f, 0); //0926 �ӵ� ���� (��ȣ)

			return TempCard;
		}
	}

	return TempCard;
}

void AHoldemCardDeckBase::InitializeDeck()
{
	FCard card;
	deck.Empty();

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
	deck.RemoveAt(0); //�� �� �� ī�带 �����ϵ��� ����. �ʿ� ������ �ּ�ó��

	NHLOG_WARNING(TEXT("%d %s, "), tempCard.CardPower, *NHDataBase::GetEnumNameToString(tempCard.CardSuit));

	//return deck.Pop(); //���� ������ �ε����� ��ȯ�Ϸ��� �ּ� ����.
	return tempCard; //���� ù��° �ε��� ���� �� ��ȯ
}

void AHoldemCardDeckBase::RotateAllSpawnCard()
{
	for (auto Elem : SpawnedCardArray)
	{
		//������ ��� ī�� ������
		Elem->CardRotate();
	}
}

void AHoldemCardDeckBase::DestroyAllSpawnCard()
{
	//��� ī�� ����
	for (auto Elem : SpawnedCardArray)
	{
		Elem->Destroy();
	}
	SpawnedCardArray.Empty();
}
