#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Motor A connections
int enA = 6;
int in1 = 5;
int in2 = 4;

void setup() {
  
    Serial.begin(115200);

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    //return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    //return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "90 89 C6 32") //change here the UID of the card/cards that you want to give access
  {
    turn_motor();
      delay(4000);
      
    stop_motor();
    delay(10000);
  }
 else   
  if(digitalRead(1)==HIGH) {  // Check if there is data available on the serial port
    String data = Serial.readStringUntil('\n'); // Read a line of text from the serial port
    delay(4000);
    turn_motor();
      delay(4000);
    stop_motor();
  }
}
void turn_motor() {
    analogWrite(enA, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void stop_motor(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
