// Fill out your copyright notice in the Description page of Project Settings.
#include "ProjectileWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	if (!HasAuthority()) return;
	
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		//log to console
		//UE_LOG(LogTemp, Warning, TEXT("SocketTransform: %s"), *SocketTransform.ToString());
		// From muzzle flash socket to hit location from TraceUnderCrosshairs
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		//log to console
		//UE_LOG(LogTemp, Warning, TEXT("ToTarget: %s"), *ToTarget.ToString());
		FRotator TargetRotation = ToTarget.Rotation();
		if (ProjectileClass && InstigatorPawn)
		{
			FActorSpawnParameters SpawnParams;
			//log to console
			//UE_LOG(LogTemp, Warning, TEXT("SocketTransform.GetLocation(): %s"), *SocketTransform.GetLocation().ToString());
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = InstigatorPawn;
			UWorld* World = GetWorld();
			if (World)
			{
				World->SpawnActor<AProjectile>(
					ProjectileClass,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParams
					);
				////log to console
				//UE_LOG(LogTemp, Warning, TEXT("Spawned projectile"));
				////log to console
				//UE_LOG(LogTemp, Warning, TEXT("SocketTransform: %s"), *SocketTransform.GetLocation().ToString());
				//UE_LOG(LogTemp, Warning, TEXT("TargetRotation: %s"), *TargetRotation.ToString());
				//UE_LOG(LogTemp, Warning, TEXT("=====================================================helloas================================="));
				//change NoCollision to Weapon from Overhead Widget
				//GetWeaponMesh()->SetCollisionProfileName(FName("NoCollision"));
				
			}
		}
	}
}