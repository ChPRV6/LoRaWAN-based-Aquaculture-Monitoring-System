
#include <LoRa.h>
#include <SPI.h>
 
#define ss 5
#define rst 14
#define dio0 2
 
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
 
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
  int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize) 
  {
    
    Serial.print("Received packet '");
 
    while (LoRa.available())              // read packet
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      /*
      String Param1=LoRaData.substring(16,20);
      float Param11=atof(Param1);
      Serial.print("Temperature is ");
      Serial.print(Param11);
      String Param2=LoRaData.substring(38,41);
      float Param22=atof(Param2);
      Serial.print("Transparency is ");
      Serial.print(Param22);
      String Param3=LoRaData.substring(56,59);
      float Param33=atof(Param3);
      Serial.print("PH is ");
      Serial.print(Param33);
      */
    }
    Serial.print("' with RSSI ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }
}