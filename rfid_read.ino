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
 
#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN   9    
#define SS_PIN    10   
 
MFRC522 mfrc522(SS_PIN, RST_PIN);  

byte blue_uid[] = {0x52, 0xC3, 0x01, 0x49};
byte red_uid[] = {0x53, 0x8D7, 0x99, 0x1A};
 
int blue_led = 5;
int red_led = 3; 
 
bool blue_check = false;
bool red_check = false;
 
 
void setup() {
  Serial.begin(9600); 
  SPI.begin();        
  mfrc522.PCD_Init(); 
  pinMode(blue_led, OUTPUT);
  pinMode(red_led, OUTPUT);
}
 
void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("Read UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    } 
    Serial.println();
 
   
    blue_check = false;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] == blue_uid[j]) {
        blue_check = true;
        digitalWrite(blue_led, LOW);
      }
    }
 
   
    red_check = false;
    for (int i=0; i<4; i++) {
      if (mfrc522.uid.uidByte[i] == red_uid[i]) {
        red_check = true;
        digitalWrite(red_led, LOW);
      }
    }
 

  
    mfrc522.PICC_HaltA();
    delay(3000);
    digitalWrite(blue_led, HIGH);
    digitalWrite(red_led, HIGH);
  }
 
}
