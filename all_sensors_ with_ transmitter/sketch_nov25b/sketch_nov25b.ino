#include <OneWire.h>
#include <DallasTemperature.h>
#include <LoRa.h>
#include <SPI.h>
#define ss 5
#define rst 14
#define dio0 2
int data;
int temper,volt,PH;
int counter = 0;
const int oneWireBus = 4;     // GPIO where the DS18B20 is connected to
const int potPin=A0;
float DO; // Dissolved oxygen 
float ph;
float Value=0; // Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus); // Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(115200);
  sensors.begin();
  pinMode(potPin,INPUT);
  delay(1000);
   while (!Serial);
  Serial.println("LoRa Sender");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
  
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  int sensorValue = analogRead(27);
  float voltage = sensorValue * (5.0 / 1024.0);
  Serial.println ("Transperancy Value:");
  Serial.println (voltage);
   Value= analogRead(potPin);
    float voltage1=Value*(3.3/4095.0);
    ph=(3.3*voltage1);
    Serial.println("The PH of the terminal is given by: ");
    Serial.println(ph);
   
    temper=temperatureC*10;
    temper=temper*1000000;
    volt=voltage*100;
    volt=volt*1000;
    PH=ph*100;
    if(temper<0)
    {
      data=temper-volt-PH;
    }
    else{
      data=temper+volt+PH;
    }
   
    //DO=random(680,800)/100.0;
   // Serial.println("The Dissolved Oxygen in ppm units is ");
    //Serial.println(DO);
    delay(500);
Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();   //Send LoRa packet to receiver
  LoRa.print(data);
  LoRa.endPacket();
 
  counter++;

 delay(1000);

}