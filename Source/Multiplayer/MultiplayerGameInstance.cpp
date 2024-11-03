// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"

#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;
}

void UMultiplayerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UMultiplayerGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->AddToViewport();
	Menu->bIsFocusable = true;
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

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