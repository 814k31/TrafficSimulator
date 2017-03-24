// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "TrafficSimWheelRear.h"

//Car wheels rear
UTrafficSimWheelRear::UTrafficSimWheelRear()
{
	ShapeRadius = 35.f;
	ShapeWidth = 10.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 0.f;
}
