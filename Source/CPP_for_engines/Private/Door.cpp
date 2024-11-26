#include "Door.h"

#include "NavModifierComponent.h"
#include "StartGameTimer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavAreas/NavArea_Null.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("_Collider"));
	RootComponent = _Collider;

	_NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("_NavModifier"));
	_NavModifier->SetAreaClass(UNavArea_Null::StaticClass());

	_bHasStarted = false;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADoor::Handle_Overlap);
}

void ADoor::Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGameMode* GameMode = Cast<AGameMode>(UGameplayStatics::GetGameMode(this));
	if (UKismetSystemLibrary::DoesImplementInterface(GameMode, UStartGameTimer::StaticClass()) && ! _bHasStarted)
	{
		IStartGameTimer::Execute_StartTimer(GameMode);
	}
	
	if (_bHasStarted)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 999999, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	_bHasStarted = true;
}
