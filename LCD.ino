#include <LiquidCrystal.h>

// Connections:
// VSS -> GND
// VDD -> 5V
// V0 -> Chiet ap
// RS to Arduino pin 12
// RW -> GND
// E to Arduino pin 11
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
// A + tro -> VCC
// K -> GND
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int button = 8;
int temSensor = A0;
float voltage = 0;
float sensor = 0;
float celsius = 0;
float fahrenheit = 0;
int cf = 1;
byte symbol[8] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
};
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
}
int count=0;
int lasttime = 0;
int stt = 1;
void loop()
{
  sensor = analogRead(temSensor);
  voltage = sensor*5.0/1024.0;
  celsius = voltage*100;         // Chuyển đổi mV sang độ C
  fahrenheit = ((celsius * 1.8)+32); // Đổi độ C sang độ F
  
  if (cf == 1)
  {
    lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
    lcd.print("Nhiet do: ");    // change text to whatever you like. keep it clean!
    lcd.setCursor(0,1);           // set cursor to column 0, row 1
    lcd.print(celsius);
    lcd.createChar(0, symbol);
    lcd.setCursor(6, 1);  
    lcd.write(byte(0));
    lcd.setCursor(7,1);
    lcd.print("C");
  }
  else
  {
    lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
    lcd.print("Nhiet do: ");    // change text to whatever you like. keep it clean!
    lcd.setCursor(0,1);           // set cursor to column 0, row 1
    lcd.print(fahrenheit);
    lcd.createChar(0, symbol);
    lcd.setCursor(6, 1);  
    lcd.write(byte(0));
    lcd.setCursor(7,1);
    lcd.print("F");
  }
  
  int buttonStatus = digitalRead(button);    //Đọc trạng thái button
  if (buttonStatus == HIGH)
  { // Nếu mà button bị nhấn
    lasttime = millis();
    cf = -cf;
    Serial.println(cf);
  }
  
  delay(150);
}
