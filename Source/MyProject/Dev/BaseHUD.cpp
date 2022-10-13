// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/BaseHUD.h"

#include "Engine/Canvas.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCross();
}

void ABaseHUD::DrawCross()
{
	int32 CenterX = Canvas->SizeX;
	int32 CenterY = Canvas->SizeY;
	const TInterval<float> Center(CenterX * 0.5, CenterY * 0.5);
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FColor Color = FColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, Color, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, Color, LineThickness);
}