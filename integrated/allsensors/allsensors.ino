#include <OneWire.h>
#include <DallasTemperature.h>
const int oneWireBus = 4;     // GPIO where the DS18B20 is connected to
const int potPin=A0;
float DO; // Dissolved oxygen 
float ph;
float Value=0; // Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus); // Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(115200);  // Start the Serial Monitor  // Start the DS18B20 sensor
  sensors.begin();
  pinMode(potPin,INPUT);
  delay(1000);
}
void loop() {+
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  int sensorValue = analogRead(27);
  float voltage = sensorValue * (5.0 / 1024.0);
  Serial.println ("Turbidity Value:");
  Serial.println (voltage);
   Value= analogRead(potPin);
    float voltage1=Value*(3.3/4095.0);
    ph=(3.3*voltage1);
    Serial.println("The PH of the terminal is given by: ");
    Serial.println(ph);
    //DO=random(680,800)/100.0;
   // Serial.println("The Dissolved Oxygen in ppm units is ");
    //Serial.println(DO);
    delay(500);
}