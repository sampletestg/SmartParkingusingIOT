#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9 
MFRC522 mfrc522(SS_PIN, RST_PIN);

Servo myServo;  // Create a servo object

void setup() {
    Serial.begin(9600);
    SPI.begin();     
    mfrc522.PCD_Init();  
    myServo.attach(6);   // Connect servo to pin 6
    myServo.write(0);    // Set servo to initial position
    Serial.println("Scan your RFID card...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    Serial.print("Card UID: ");
    String UID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        UID += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(UID);

    // Check for a specific RFID tag (replace with your tag's UID)
    if (UID) {  // Replace with your card's UID
        Serial.println("Access Granted! Rotating Servo...");
        myServo.write(90);  // Rotate servo 90 degrees
        delay(2000);        // Hold position for 2 seconds
        myServo.write(0);   // Return to the initial position
    } else {
        Serial.println("Access Denied!");
    }

    mfrc522.PICC_HaltA();
}
