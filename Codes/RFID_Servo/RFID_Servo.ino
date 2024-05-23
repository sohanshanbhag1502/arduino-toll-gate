// Modules required for RFID Sensor
#include <SPI.h>
#include <MFRC522.h>

// Modules required for Servo Motor
#include <Servo.h>

// Modules required for Proximity Sensor
#include <HCSR04.h>

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

// Configure the pins for Proximity Sensor
#define DUMP_REGS
// Configure the pins for RFID Sensor
#define SS_PIN 10
#define RST_PIN 9
// Configure the pins for Weight Sensor
const int HX711_dout = 6; //mcu > HX711 dout pin
const int HX711_sck = 7; //mcu > HX711 sck pin

// Create an instance of the servo motor
Servo myservo;

// Create an instance of the proximity sensor
HCSR04 hc(A3, A2);

// Create an instance of the Weight sensor
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

// Create an instance of the RFID sensor
int pos = 0; 
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Function to initialize all sensors
void setup(){
    // Start the serial communication on the baud rate of 9600
    Serial.begin(9600);

    // Initialise the RFID sensor
    Serial.println("Initialising RFID Sensor...");
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("RFID Sensor initialised successfully");
    Serial.println();

    // Initialise the Servo Motor
    Serial.println("Initialising Servo Motor...");
    myservo.attach(5);
    Serial.println("Servo Motor Initialised successfully");
    Serial.println();

    // Initializing the HX-711 Weight Sensor
    Serial.println("Initializing HX711 Weight Sensor");
    LoadCell.begin();
    float calibrationValue=700;
    unsigned long stabilizingtime = 2000; 
    boolean _tare = true;
    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag()) {
      Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    }
    else {
      LoadCell.setCalFactor(calibrationValue);
      Serial.println("HX711 Weight Sensor is initialized");
      Serial.println();
    }

    delay(1000);
    Serial.println("All components initialised successfully");
    Serial.println("Waiting for the vehicle...");
}

// Function will be running continuously
void loop(){
    // Detect if any vehicle is near the gate
    int dist=hc.dist();
    Serial.println(dist);
    myservo.write(180);
    if (dist<=2){
        // If Vehicle is detected check for RFID tag
        if (!mfrc522.PICC_IsNewCardPresent()){
            return;
        }

        if (!mfrc522.PICC_ReadCardSerial()){
            return;
        }

        // If RFID tag is detected check the tag ID
        Serial.println("RFID tag detected");
        Serial.print("UID tag :");
        String content= "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++){
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }

        Serial.println();
        Serial.print("Message : ");
        content.toUpperCase();

        if (content.substring(1) == "53 5E 2D 0E"){
            // If the RFID tag is authorized, open the gate
            Serial.println("Authorized access");

            // Reading weight from Weight Sensor
            float i = LoadCell.getData();
            Serial.println(i);
            myservo.write(90);
            if (0<=i && i<=5){
              Serial.println("Detected Vehicle Type:Car");
            }
            else if (5<i && i<=10){
              Serial.println("Detected Vehicle Type:Truck or Bus");
            }

            // Wait for vehicle to pass through the gate
            delay(10000);

            // Close the gate
            Serial.println();
    	    myservo.write(180);
            Serial.println("Waiting for the vehicle...");
            Serial.println();
        }
        else{
            // If the RFID tag is not authorized, keep the gate closed
            Serial.println("Access denied");
            Serial.println("Waiting for the vehicle...");
        }
    }
    else{
        // If no vehicle is detected, keep the gate closed
        return;
    }
}