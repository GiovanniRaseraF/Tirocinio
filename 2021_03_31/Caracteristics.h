#ifndef CYNEXO_BLE_CARACTERISTICS
#define CYNEXO_BLE_CARACTERISTICS
#include <ArduinoBLE.h>

class Service{
public:
	Service() {};

	BLEStringCharacteristic logReportMessageCharacteristic = BLEStringCharacteristic(
		"19B10001-E8F2-537E-4F6C-D104768A1214",
		BLERead | BLENotify,
		50
	);

    BLEService logReportServiceUUID{ "19B10000-E8F2-537E-4F6C-D104768A1214" };
};

#endif