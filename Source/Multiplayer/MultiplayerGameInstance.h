// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

#include "MultiplayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UMultiplayerGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void LoadMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void InGameLoadMenu();
	
	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(const FString& Address);
private:
	TSubclassOf<class UUserWidget> MenuClass; //class yazmak forward decklarition oluyor galiba, include u burada yapmadik diye belirttik, normalde gerek yok
	TSubclassOf<class UUserWidget> InGameMenuClass;
	
	class UMainMenu* Menu;
};
