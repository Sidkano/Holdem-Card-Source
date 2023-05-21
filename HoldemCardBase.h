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

//함수
	UFUNCTION(BlueprintImplementableEvent)
		/*스플라인 EndPoint 찍기 - 블프로*/
		void SetSplineEndPoint_CPP(FVector EndLoc);

	UFUNCTION(BlueprintImplementableEvent)
		/*카드 움직이기 블프로*/
		void MoveCard_CPP(bool ReverseMove, float CardSpeed, int32 CardIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		/*텍스처 바꾸기 블프로*/
		void SetCardTexture(FCard Card);

	/*클릭, see 변수 세터*/
	void SetCanClickAndSeeCard(bool canClicked, bool canSee);

	UFUNCTION(BlueprintImplementableEvent)
	/*카드 회전 시키기*/
	void CardRotate();

	UFUNCTION(BlueprintImplementableEvent)

	/* 카드 크기 조정 */
	void SetCardScale(FTransform transform);

	UFUNCTION(BlueprintImplementableEvent)
		/*카드 뒤집기*/
		void CardRotate_180();

	UFUNCTION(BlueprintImplementableEvent)
		/*카드 올리기*/
		void CardLocationOffset(FVector AddOffset);

	UFUNCTION(BlueprintImplementableEvent)
		/*카드 이펙트 실행*/
		void CardEffectActive();

//변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*뒤집을 때 체크*/
		bool CanClickCard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*카드를 볼 수 있는지 체크*/
		bool CanSeeCard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*카드를 회전시킬 수 있는지 체크*/
		bool IsRotate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Card")
		/*카드의 우위를 체크하는 구조체*/
		FCard MyData;
};
