// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "TrafficSimWheelFront.h"


//Car wheels front
UTrafficSimWheelFront::UTrafficSimWheelFront()
{
	ShapeRadius = 35.f;
	ShapeWidth = 10.0f;
	bAffectedByHandbrake = false;
	SteerAngle = 50.f;
}
