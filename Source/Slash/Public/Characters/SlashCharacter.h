
#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class UBoxComponent;
class AWeapon;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponEnableCollision(ECollisionEnabled::Type CollisionEnabled);

protected:
	virtual void BeginPlay() override;
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* SlashContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RotationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PickUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PickUp();
	void Attack();

private:

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;
	
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;
	
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;
	
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	
	/*
	 * Animation Montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	
public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
};
