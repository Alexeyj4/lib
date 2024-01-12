#pragma once
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <arduino.h>

//bool deviceConnected;

class Ble{
  public:	 
    Ble();
	String s;
	void begin();
	bool connected();
	bool send(String s);//return 1-ok //0-not ok
	String recv();//""-not to received	
	//bool deviceConnected;
	BLECharacteristic *pCharacteristic;
	
};