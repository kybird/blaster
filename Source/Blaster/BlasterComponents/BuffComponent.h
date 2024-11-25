// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();
	friend class ABlasterCharacter;
	void Heal(float HealAmount, float HealingTime);
	void ReplenishShield(float ShieldAmount, float ReplenishTime);
	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime);
	void SetInitialSpeed(float BaseSpeed, float CrouchSpeed);
	void SetInitialJumpVelocity(float Velocity);
	void BuffJump(float BuffJumpVelocity, float BuffTime);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void HealRampUp(float DeltaTime);
	void ShieldRampUp(float DeltaTime);

private:
	UPROPERTY()
	class ABlasterCharacter* Character;

	
	/**
	* Heal buff
	*/
	bool bHealing = false;
	float HealingRate = 0;
	float AmountToHeal = 0.f;

	
	/**
	* Shield buff
	*/
	bool bReplenishingShiled = false;
	float ShieldReplenishRate = 0;
	float ShieldReplenishAmount = 0.f;


	/**
	* Speed buff
	*/
	FTimerHandle SpeedBuffTimer;
	void ResetSpeeds();
	float InitialBaseSpeed;
	float InitialCrouchSpeed;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);

	/**
	* Jump buff
	*/
	
	FTimerHandle JumpBuffTimer;
	void ResetJump();
	float InitialJumnVelocity;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastJumpBuff(float JumpVelocity);


	


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

		
};
