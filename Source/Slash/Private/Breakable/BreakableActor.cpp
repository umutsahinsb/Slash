
#include "Breakable/BreakableActor.h"

#include "Components/CapsuleComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Items/Treasure.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>("GeometryCollection");
	SetRootComponent(GeometryCollection);
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(GetRootComponent());
	
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint)
{
	if (bBroken) return;
	bBroken = true;
	UWorld* World = GetWorld();
	if (World && TreasureClasses.Num()>0)
	{
		const int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);
		
		FVector Location = GetActorLocation();
		World->SpawnActor<ATreasure>(TreasureClasses[Selection], Location, FRotator(0, 0, 0));
	}
}

