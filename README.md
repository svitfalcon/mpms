MULTI PATIENT MONITORING SYSTEM


DESCRIPTION:

Considering the present pandemic situation, we observe that the number of patients is only increasing day-by-day, whereas, the number of doctors and caretakers are limited. Monitoring a huge number of patients, by remembering or noting down their details, and then treating them is possible but one doctor or a caretaker can only monitor one or three patients at the max. Let's take an emergency situation. We all know that, during this pandemic situation, a patient's health cannot be determined. Therefore, each and every patient is to be monitored at the same time. A tiny human error or delay in checking on the patient can take a precious life. This situation can be avoided by implementing our idea, which is, “Multiple patient monitoring systems”. A system which can read all the parameters of patients and update the same in the database, dynamically. And also reflect the vital parameter and conditions of all the patients in Web user interface. This continuous monitoring system can also alert the doctors and caretakers in case of any emergency. 

HARDWARE COMPONENTS REQUIRED: 

1. ESP32 
2. Max30102 

 
ESP32 

ESP32 is a powerful microcontroller with dual-core CPU and it can be clocked at80,160 or 240 MHz. It has built-in WIFI and Bluetooth and supports various communication protocols. It has also got ultra-low power co-processor, which is used for small tasks. ESP32 has got a memory of 512KB SRAM. ESP32 is a battery friendly. 

![ESP32](https://user-images.githubusercontent.com/84200921/118837313-4da96980-b8e2-11eb-9057-1562bb8c4508.jpg)

Max30102 

MAX30102 is an integrated pulse oximeter and heart-rate monitor. It has Led's and photodiodes for measurements. Heartbeat and oxygen level can be monitored or measured and on placing the finger on the sensor, it notes down the readings. It supports I2C communication protocol.  


LIBRARY REQUIRED: 

Install the library “max3010x pulse and proximity sensor library” in Arduino IDE. This library supports both max30102 and max30105 modules. Here, we are using MAX30102 module. 
![max30102](https://user-images.githubusercontent.com/84200921/118838294-2ef7a280-b8e3-11eb-897b-1051543e5bf0.jpg)


PROCESS FLOW:

1.Make the connection as shown below
![connection](https://user-images.githubusercontent.com/84200921/118839162-e8ef0e80-b8e3-11eb-8243-b370eb260e1d.jpg)

2. Install Arduino IDE, which is an open-source software and is compatible with Mac, Linux and Windows OS. It is used to write the code and upload it onto the board (here ESP32). 
![arduino ide](https://user-images.githubusercontent.com/84200921/118840024-a5e16b00-b8e4-11eb-9318-a2f69e9289f6.jpg)

3.Install these llibraries in Arduino IDE
-ESPAsyncWebServer
-AsyncTCP
-WiFi
-FirebaseESP32
-Wire
-MAX30105
-heartRate
