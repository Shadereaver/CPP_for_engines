﻿#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile::Handle_Hit);

	_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	_ProjectileMovement->UpdatedComponent = RootComponent;
	_ProjectileMovement->InitialSpeed = 3000.f;
	_ProjectileMovement->MaxSpeed = 3000.f;
	_ProjectileMovement->bRotationFollowsVelocity = true;
	_ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.f;
}

void AProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == nullptr || OtherActor == this || OtherComp == nullptr || GetInstigator() == OtherActor) {return;}

	UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this,
		UDamageType::StaticClass());

	if (OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * _Mass, GetActorLocation());
	}
	Destroy();
}

