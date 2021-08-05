#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

BLEService service("3e1feeec-b4dc-495b-b117-b71d7a0fbe1b");
BLECharacteristic characteristic("9116561c-c7cd-4002-9376-f5c0661761b0", BLENotify | BLERead, 12);

void setup() {
  IMU.begin();
  Serial.begin(9600);
  

  

  service.addCharacteristic(characteristic);

  if (!BLE.begin()) {
    Serial.println("no");
  }

  BLE.setLocalName("Jimmy's Nano");
  BLE.setDeviceName("Jimmy's Nano");

  BLE.addService(service);

  BLE.setAdvertisedService(service);

  BLE.advertise();
  
}
float x, y, z;



void loop() {
  IMU.readAcceleration(x, y, z);
  float buffer[12]{x, y, z};
  if (BLE.connected()) {
    characteristic.writeValue(buffer, 12);
  }
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
}
