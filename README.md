# RFID Toll gate using Arduino

This project is a prototype of modern day tollgate and demonstrates the working of modern day fastag toll gates using RFID signals. <br>
This project mainly uses 3 sensors RFID, Weight and Ultrasonic. RFID sensor is used to detect RFID tag and authorize the vehicle. Weight sensor is used to detect the class of vehicle by checking the range in which weight falls into. Ultrasonic sensor is used to detect presence of a vehicle and activate the RFID sensor.

## Components Used:
- [Arduino Uno R3 Board (Compatible)](https://robocraze.com/products/uno-r3-board-compatible-with-arduino)
- [USB A to B Cable](https://robocraze.com/products/usb-a-b-cable-3-0-cm)
- [RC522 RFID Sensor](https://robocraze.com/products/rfid-rc522-mfrc)
- [HCSR04 Ultrasonic Sensor](https://robocraze.com/products/hc-sr-04-ultrasonic-sensor)
- [HX711 Weight Sensor with 50 Kg Weight Cell](https://robocraze.com/products/50kg-load-cell-hx711)
- [Tower Pro SG-90 Servo Motor](https://www.amazon.in/Robocraze-Tower-Micro-Servo-Motor/dp/B0825S18VV)
- [Breadboard](https://robocraze.com/products/half-breadboard)
- [2 x 1k ohm resistors](https://robocraze.com/products/1k-resistor-pack-of-10)
- [Jumper Wires](https://www.amazon.in/Girirajji-Jumper-Female-breadboard-jumper/dp/B09K7LRHW8/ref=sr_1_107?dib=eyJ2IjoiMSJ9.ZyTAcFuWnVCnS1JUy0xkE-dpsZKpGrHgU0VFawsljqDqCgrzRgXOFzpcL40Caf5bavWfC3UO4Zdm8g3WsHj76FAUjb90WqVaOicZ-PEs8BKBgtvmcMgyipPPqouuhLOf2z44sXwyT1RCG5QEVXaHC1t6mREIRHcN8-Z7sGZ6MJsQyLxCdfaUeSgFqzUFaLSboC-LlYNg5A3h3WVN-HNTQJlzDwZ9OGOZhq9v9hk1wI0A-Rz3GPGidK3rhXjr9N7NJYxNyryjx8Muvs2FA4_Yzk35b0ddkmb_zV7ofLyCGkI.wwx729SVV7U0XNH8ZYEjPBqNcc-Ny1KHuam7ijAUB90&dib_tag=se&keywords=Jumper%2BWire&qid=1716481188&sr=8-107&th=1)

## Circuit diagram:
![](https://github.com/sohanshanbhag1502/arduino-toll-gate/blob/main/Circuit.jpg)

## Instructions:
- Form the circuit with appropriate connections as shown in the diagram.
- Connect the arduino to Computer with USB A to B Cable.
- Download [Arduino IDE](https://www.arduino.cc/en/software) and install.
- Download all the libraries from [lib folder](https://github.com/sohanshanbhag1502/arduino-toll-gate/tree/main/lib).
- Open Arduino IDE, go to Sketch>Include Library>Add .zip file.
- Locate the downloaded modules and add them.
- Now download the code from [Codes folder](https://github.com/sohanshanbhag1502/arduino-toll-gate/tree/main/Codes/RFID_Servo).
- Open the code in Arduino IDE and upload it.

Note: To learn more about any component go to [Datasheets folder](https://github.com/sohanshanbhag1502/arduino-toll-gate/tree/main/Datasheets) and refer the components datasheet.
