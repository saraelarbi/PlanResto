#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SERVO_PIN 8
Servo myservo; // Create instance of our motor
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create instance of our reader
void setup() {
 Serial.begin(9600);
 SPI.begin();
 mfrc522.PCD_Init();
 Serial.println("Arduino RFID lock");
 myservo.attach(SERVO_PIN);
 myservo.write(90);
}
void loop(){
 //Look for new cards
 if ( ! mfrc522.PICC_IsNewCardPresent() ){
 return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial() ) {
 return;
 }
// If a card is detected, execute the following:
 Serial.println("Time to open");
// Print the card's ID
String content= "";
 byte letter;
 for( byte i = 0; i < mfrc522.uid.size; i++ ){
 content.concat(String(mfrc522.uid.uidByte[i], HEX));
 if( i < mfrc522.uid.size-1 ) content+="-";
 }
 content.toUpperCase();
 Serial.println();
 Serial.println("UID tag :’" + content + "‘");
 Serial.println("Authorized access");
 myservo.write(90); // Flip open lock
 myservo.write(0); // Close lock
 
}
