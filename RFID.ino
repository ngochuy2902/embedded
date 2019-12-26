/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <SPI.h> //thư viện chuẩn giao tiếp Serial Peripheral Bus
#include <MFRC522.h> //khai báo thư viện của RFID
#define SS_PIN 10 //SDA pin
#define RST_PIN 9 //Reset pin
#define LED 4 //Led
MFRC522 mfrc522(SS_PIN, RST_PIN); 
long int lasttime = 0;
long int last=0;
int check=0;
int ledstt=0;
void setup() 
{
  Serial.begin(9600);
  SPI.begin(); // khởi tạo SPI bus
  mfrc522.PCD_Init(); // khởi tạo MFRC522
  pinMode(LED, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void getInfo()
{
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void loop() 
{
// Tìm thẻ mới
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Đọc UID của thẻ
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  //getInfo();

  Serial.print("UID tag: ");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  if (content.substring(1) == "9A 21 95 02") //Cấp UID quyền truy cập cho thẻ
  {
    check = 1;
    last = millis();
    Serial.println("Access allowed");
    Serial.println("--------------------");
    delay(300);
    if (millis() - lasttime < 1000)
    {
      digitalWrite(LED, LOW);
      check=0;
      ledstt=0;
    }
    lasttime = millis();
  }
  Serial.print("check = ");
  Serial.println(check);
  Serial.print("Lasttime = ");
  Serial.println(millis() - lasttime);
  if (millis - last > 2000 && check == 1)
    {
      digitalWrite(LED, HIGH);
      last = millis();
    }
}
