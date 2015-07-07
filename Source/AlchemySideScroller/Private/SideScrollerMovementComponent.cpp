// Fill out your copyright notice in the Description page of Project Settings.

#include "AlchemySideScroller.h"
#include "SideScrollerCharacter.h"
#include "SideScrollerMovementComponent.h"


USideScrollerMovementComponent::USideScrollerMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}


void USideScrollerMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USideScrollerMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USideScrollerMovementComponent::IsClimbing() const
{
	return CharacterOwner && (Cast<ASideScrollerCharacter>(CharacterOwner))->bIsClimbing;
}