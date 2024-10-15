#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

//Look at template sandbox patterns

void AWeapon_Hitscan::Fire()
{
	UWorld* const World = GetWorld();
	if (World == nullptr) {return;}

	FHitResult HitResult(ForceInit);
	FVector Start = _Muzzle->GetComponentLocation();
	FVector End = Start + (_Muzzle->GetForwardVector() * 1000);

	if (UKismetSystemLibrary::LineTraceSingle(World, Start, End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		{GetOwner()}, EDrawDebugTrace::ForDuration, HitResult, true,
		FLinearColor::Red,FLinearColor::Green, 5))
	{
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), _Damage, GetOwner()->GetInstigatorController(),
			GetOwner(), UDamageType::StaticClass());

		UE_LOG(LogTemp, Display, TEXT("Hit pos: %s"), *HitResult.ImpactPoint.ToString());
	}
	
	Super::Fire();
}
