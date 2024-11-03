// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UMultiplayerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UMultiplayerGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UMultiplayerGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	PlayerController->ClientTravel(Address,TRAVEL_Absolute);
}