#pragma once
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <arduino.h>
#define SERVICE_UUID            "C6FBDD3C-7123-4C9E-86AB-005F1A7EDA01"
#define CHARACTERISTIC_UUID_RX  "B88E098B-E464-4B54-B827-79EB2B150A9F"
#define CHARACTERISTIC_UUID_TX  "D769FACF-A4DA-47BA-9253-65359EE480FB"

bool BleDeviceConnected_;
String BleReceivedString_;

class Ble{
  public:	 
    Ble();
	String s;
	void begin();
	bool connected();
	bool send(String s);//return 1-ok //0-not ok
	String recvd();//""-not received	
	void clr();//clear received string
	BLECharacteristic *pCharacteristic;
	
};

Ble::Ble(){
	BLECharacteristic *pCharacteristic;
	BleDeviceConnected_ = false;
}   
 
// функции обратного вызова, которые будут запускаться
// при подключении и отключении BLE-клиента от BLE-сервера:
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {    
	BleDeviceConnected_ = true;
  };
  void onDisconnect(BLEServer* pServer) {    
	BleDeviceConnected_ = false;

    // Начинаем рассылку оповещений:
    pServer->getAdvertising()->start();
    //  "Ждем подключения..."
  }
};

 //функция обратного вызова, которая будет запускаться
 //при получении нового значения от Android-приложения:
class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    BleReceivedString_="";
    if(rxValue.length() > 0) {      
      for(int i = 0; i < rxValue.length(); i++) {
        BleReceivedString_=BleReceivedString_+rxValue[i];
      }
    }
   
   
  }
};
 
void Ble::begin(){ 

	//Serial.println("Ble::begin()"); //debug
	BleDeviceConnected_ = false;

	// создаем BLE-устройство:
	BLEDevice::init("MA41tester");

	// создаем BLE-сервер:
	BLEServer *pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Создаем BLE-сервис:
	BLEService *pService = pServer->createService(SERVICE_UUID);

	// Создаем BLE-характеристику:
	pCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID_TX,
		BLECharacteristic::PROPERTY_NOTIFY);
    
	pCharacteristic->addDescriptor(new BLE2902());

	BLECharacteristic *pCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID_RX,
		BLECharacteristic::PROPERTY_WRITE);

	pCharacteristic->setCallbacks(new MyCallbacks());

	// Запускаем сервис:
	pService->start();

	// Начинаем рассылку оповещений:
	pServer->getAdvertising()->start();
	delay(500);       
}

bool Ble::connected(){
	return BleDeviceConnected_;
} 


bool Ble::send(String s){
	//Serial.println("Ble::send()");//debug
	//Serial.println(s);//debug
	//Serial.println(s);//debug
	  // Если устройство подключено... 
	if(BleDeviceConnected_) {
		//Serial.println("Device connected; send value");//debug
		pCharacteristic->setValue(s.c_str());
		// отправляем значение Android-приложению:
		pCharacteristic->notify();     
    }  
	return 1;
} 	

String Ble::recvd(){	
	return BleReceivedString_;
} 	

void Ble::clr(){
	BleReceivedString_="";	
}