#pragma once
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <arduino.h>

class Ble{
  public:	 
    Ble();
	String s;
	void begin();
	bool send(String s);//1-ok //0-not ok
	String recv();//""-not to received	
	bool deviceConnected;
	BLECharacteristic *pCharacteristic;
	
};