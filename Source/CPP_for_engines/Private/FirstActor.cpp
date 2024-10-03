#include "FirstActor.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"



AFirstActor::AFirstActor()
{
	_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = _Box;
	
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);
}

void AFirstActor::BeginPlay()
{
	Super::BeginPlay();

	_Box->OnComponentHit.AddUniqueDynamic(this, &AFirstActor::Handle_ColliderHit);
}

void AFirstActor::Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}
