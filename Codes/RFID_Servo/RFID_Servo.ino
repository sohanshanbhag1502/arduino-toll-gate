// Modules required for RFID Sensor
#include <SPI.h>
#include <MFRC522.h>

// Modules required for Servo Motor
#include <Servo.h>

// Modules required for Proximity Sensor
#include <Wire.h>
#include <APDS9930.h>

// Configure the pins for Proximity Sensor
#define DUMP_REGS
// Configure the pins for RFID Sensor
#define SS_PIN 10
#define RST_PIN 9
// Configure the pins for Servo Motor
#define SERVO_PIN 5
#define GATE_CLOSE 0
#define GATE_OPEN 90

// Create an instance of the servo motor
Servo myservo;

// Create an instance of the proximity sensor
APDS9930 apds = APDS9930();
float ambient_light = 0;
uint16_t ch0 = 0;
uint16_t ch1 = 1;

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

    // Initialise the Servo Motor
    Serial.println("Initialising Servo Motor...");
    myservo.attach(SERVO_PIN);
    Serial.println("Servo Motor Initialised successfully");

    // Initialise the Proximity Sensor
    Serial.println("Initialising APDS-9930 Proximity Sensor...");
    if (apds.init()) {
        Serial.println(F("APDS-9930 initialised successfully"));
    } else {
        Serial.println(F("Something went wrong during APDS-9930 init!"));
    }
    if ( apds.enableLightSensor(false) ) {
        Serial.println(F("Light sensor initialised successfully"));
    } else {
        Serial.println(F("Something went wrong during light sensor init!"));
    }
    #ifdef DUMP_REGS
        uint8_t reg;
        uint8_t val;

        for(reg = 0x00; reg <= 0x19; reg++) {
            if( (reg != 0x10) && \
                (reg != 0x11) )
            {
            apds.wireReadDataByte(reg, val);
            Serial.print(reg, HEX);
            Serial.print(": 0x");
            Serial.println(val, HEX);
            }
        }
        apds.wireReadDataByte(0x1E, val);
        Serial.print(0x1E, HEX);
        Serial.print(": 0x");
        Serial.println(val, HEX);
    #endif

    // Wait for all components to initialise and calibrate
    delay(1000);
    Serial.println("All components initialised successfully");
}

// Function will be running continuously
void loop(){
    // Close the gate
    myservo.write(GATE_CLOSE);
    Serial.println("Waiting for the vehicle...")

    // Detect if any vehicle is near the gate
    if (!apds.readAmbientLightLux(ambient_light) ||
        !apds.readCh0Light(ch0) || 
        !apds.readCh1Light(ch1) ) {
        Serial.println(F("Error reading light values"));
    }
    else if (ambient_light < 50){
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
            myservo.write(GATE_OPEN);
            Serial.println("Authorized access");
            Serial.println();

            // Wait for vehicle to pass through the gate
            delay(10000);
        }
        else{
            // If the RFID tag is not authorized, keep the gate closed
            Serial.println("Access denied");
        }
    }
    else{
        // If no vehicle is detected, keep the gate closed
        return;
    }
}