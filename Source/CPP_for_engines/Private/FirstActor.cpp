#include "FirstActor.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/RotatingMovementComponent.h"


AFirstActor::AFirstActor()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_Rotate =CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotate"));
}
