#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

SYSTEM_POWER_STATUS status;

int getBatteryPercent() {
	GetSystemPowerStatus(&status);
	
	return status.BatteryLifePercent;
}

int getACLine() {
	GetSystemPowerStatus(&status);

	return status.ACLineStatus;
}

int getBatteryTimeRemaining() {
	GetSystemPowerStatus(&status);

	return status.BatteryLifeTime;
}