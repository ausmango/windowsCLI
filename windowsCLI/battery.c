#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

SYSTEM_POWER_STATUS status;

int batteryPercent() {
	GetSystemPowerStatus(&status);
	
	return status.BatteryLifePercent;
}

int acLine() {
	GetSystemPowerStatus(&status);

	return status.ACLineStatus;
}

int batteryTimeRemaining() {
	GetSystemPowerStatus(&status);

	return status.BatteryLifeTime;
}