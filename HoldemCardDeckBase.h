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

//컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* Root; // 카드 루트 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* CardSpawnLoc; // 카드 스폰할 위치를 담을 변수


//함수
	UFUNCTION(BlueprintCallable)
		/*카드 스폰 후 움직이기*/
		AHoldemCardBase* SpawnCardAndMove(FTransform CardTrans, const FCard CardInfo, bool CanSee, bool CanClick);

		/* 덱 초기화 후 구성 */
	UFUNCTION(BlueprintCallable)
	void InitializeDeck();

		/* 덱 셔플 */
	UFUNCTION(BlueprintCallable)
	void ShuffleDeck();

	UFUNCTION(BlueprintCallable)
	FCard GetDeckTopCard(); // 최상위 카드 구하는 함수

	/*모든 카드 뒤집기*/
	void RotateAllSpawnCard();

	/*모든 카드 제거*/
	void DestroyAllSpawnCard();

//레퍼런스
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ref")
		/*홀덤 카드 클래스 레퍼런스*/
		TSubclassOf<class AHoldemCardBase> HoldemCardClass;

//변수
	TArray<FCard> deck;

	/*스폰한 카드 배열*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AHoldemCardBase*> SpawnedCardArray;
};
