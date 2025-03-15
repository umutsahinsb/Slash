
#include "Items/Treasure.h"
#include "Characters/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* Character = Cast<ASlashCharacter>(OtherActor);
	if (Character)
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
		}
		Destroy();
	}
}
