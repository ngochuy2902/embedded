#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include<SPI.h>

File myFile;
RTC_DS1307 rtc;
byte pinTemp = A0;

//mosi 11 miso 12 sck 13 cs 4 sdcard
//rtc SDA A4 SCL A5
//lm35 A0


int pre_temp = 0;
void setup () 
{
  Serial.begin(9600);
  pinMode(pinTemp, INPUT);
  if (!SD.begin(4)) {
    Serial.println("Khong thay the SD");
    while (1);
  }
  while(SD.exists("TEMPP.TXT")) SD.remove("TEMPP.TXT");
  
  
  
  if ( !rtc.begin()) 
  {
    Serial.print("Khong thay RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.print("RTC khong chay!");
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// to set the time manualy 
   
}
void  getTime()
{
  DateTime now = rtc.now();
  myFile.print(now.hour());
  Serial.print(now.hour());
  myFile.print(':');
  Serial.print(':');
  myFile.print(now.minute());
  Serial.print(now.minute());
  myFile.print(':');
  Serial.print(':');
  myFile.print(now.second());
  Serial.print(now.second());
  myFile.print("   ");
  Serial.print("   ");
  
}
void getTemp()
{
  int temp = (5.0*analogRead(A0)*100.0/1024.0);
  if(temp != pre_temp)
  {
    getTime();
    myFile.print("Nhiet do: ");
    Serial.print("Nhiet do: ");
    myFile.print(temp);
    Serial.print(temp);
    myFile.print("\n");
    Serial.print("\n");
    pre_temp = temp;
  }
}

void loop () 
{
   myFile=SD.open("TEMPP.TXT", FILE_WRITE);
   if(myFile){
    getTemp();
   }else{
    Serial.print("Loi!");
   }
   myFile.close();
  delay(3000);
}
