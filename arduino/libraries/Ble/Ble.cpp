#include "Ble.h"
#define SERVICE_UUID            "C6FBDD3C-7123-4C9E-86AB-005F1A7EDA01"
#define CHARACTERISTIC_UUID_RX  "B88E098B-E464-4B54-B827-79EB2B150A9F"
#define CHARACTERISTIC_UUID_TX  "D769FACF-A4DA-47BA-9253-65359EE480FB"

Ble::Ble(){
	BLECharacteristic *pCharacteristic;
	deviceConnected = false;
}   
 
// функции обратного вызова, которые будут запускаться
// при подключении и отключении BLE-клиента от BLE-сервера:
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {    
	//deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {    
	//deviceConnected = false;

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
    String s;
    if(rxValue.length() > 0) {      
      for(int i = 0; i < rxValue.length(); i++) {
        s=s+rxValue[i];
      }
    }
   
   
  }
};
 
void Ble::begin(){ 

	Serial.println("Ble::begin"); //debug
	deviceConnected = false;

	// создаем BLE-устройство:
	BLEDevice::init("ESP32_Board");

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

} 


bool Ble::send(const String &s){
	  // Если устройство подключено... 
/* 	if(deviceConnected) {	
		pCharacteristic->setValue(s.c_str());
		// отправляем значение Android-приложению:
		pCharacteristic->notify();     
    }  */ 
} 	

String Ble::recv(){

} 	
