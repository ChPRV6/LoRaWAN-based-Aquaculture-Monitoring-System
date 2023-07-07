#include <LoRa.h>
#include <stdbool.h>
#include <SPI.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
unsigned int cnt;
int data1;
int temp1;
float temp;
int ph;
float PH;
int turb;
float TURB;
#define ss 5
#define rst 14
#define dio0 2
void setup() 
{ Serial.begin(11500);
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
  lcd.begin(16, 2);
    lcd.setRGB(100,100,100);   
    delay(1000);
    }
 
void loop() 
{
  lcd.setCursor(0,1);
  lcd.print("Temp^ Tran^ PH^ ");
  int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize) 
  {
  cnt=0;
    Serial.print("Received packet '");
     lcd.setCursor(0,0);
    while(LoRa.available())              // read packet
    {
      String LoRaData = LoRa.readString();
      data1=LoRaData.toInt();
      temp1=data1/(1000000); // for temperature
      temp=temp1/10.00;
      turb=(data1)/1000;
      if(data1<0)
      {
       turb=turb-temp1*1000;
       
       ph=data1-turb*1000-temp1*1000000;
       PH=-ph/100.00;

       TURB=-turb/100.00;
      }
      else
      { turb=turb-(1000)*temp1;
        ph=data1-turb*1000-temp1*1000000;
        PH=ph/100.00;

       TURB=turb/100.00;
        
      }

     lcd.print(temp);
      lcd.print(" ");
       lcd.print(TURB);
      lcd.print(" ");
       lcd.print(PH);
      lcd.print(" ");
      //lcd.setRGB(0,200,0);
      if((temp<26.00)|(temp>32.00))
      {  //is temp in range ?
       lcd.setRGB(255,0,0);
        
        // if((PH<6.40)|(PH>8.80))
        //   {  //is ph in range?
        //    if(TURB<4.00)
        //     {
        //        lcd.setRGB(255,0,0);
        //     }
        //   else{
        //        lcd.setRGB(0,100,100);
        //      }
        //   }
        //   else if(TURB<4.00)
        //      {
        //        lcd.setRGB(168,168,100);
        //      }
        //   else{
        //         lcd.setRGB(245,35,0);
        //       }
      }
      else if((PH<6.40)|(PH>8.80))
      {// //is ph in range?
      //      if(TURB<4.00)
      //     {
      //       lcd.setRGB(255,110,0);
      //     }
      //     else{
      //         lcd.setRGB(0,0,255);
      //     }
          lcd.setRGB(255,0,0);
      }
      else if(TURB<4.00)
      {
        lcd.setRGB(255,0,0);
      }
      else
      {
        lcd.setRGB(0,235,0);
      }
      //lcd.print(data1);
     //lcd.print(LoRaData);
     delay(10000);
    }
    Serial.print("' with RSSI ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
    }
  else if(cnt==200)
  {  cnt=0;
     lcd.setRGB(0,0,0);
  }
else{
  cnt++;
  }
}