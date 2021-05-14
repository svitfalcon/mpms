//////////////////////////////////////////////////////////////Team ID: eYHC#86 ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////S Vignesh, Reethik Chitragupt, Suparna C////////////////////////////////////////////////////////// 
///////////////////////////////////////
///////LIBRARIES///////////////////////
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Wire.h>
#include "MAX30105.h"                             //MAX3010x library
#include "heartRate.h"                            //Heart rate calculating algorithm

MAX30105 particleSensor;                              

///////OXIMETER SENSOR PARAMETERS///////////////////////
const byte RATE_SIZE = 10;                        //Increase this for more averaging. 10 is good.
byte rates[RATE_SIZE];                            //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;                                //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;
int i=0,i1=0,Valid=0;
int arrayofbpm[10];
/////////////////////////////////////////////////////////


///////////////////FIREBASE CONNECTION PARAMETERS////////
#define FIREBASE_HOST "https://multi-patient-monitoring-sys-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "fcljzdsGLTzMLdBaghpxhh4UeH8Lnf7Xn2dfSXWC"
FirebaseData firebaseData;
FirebaseJson json;
FirebaseJson json1;
/////////////////////////////////////////////////////////

/////////////WiFi CONNECTION PARAMETERS/////////////////
#define WIFI_SSID "Shdv1234"
#define WIFI_PASSWORD "shdv1234"
AsyncWebServer server(80);
///////////////////////////////////////////////////////

//////////////////SETUP FUNCTION//////////////////////
void setup() {  
  Serial.begin(9600);                             // Initialize Serial communication at baud rate of 9600
  // Initialize sensor//
  particleSensor.begin(Wire, I2C_SPEED_FAST);     //Use default I2C port, 400kHz speed
  particleSensor.setup();                         //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);      //Turn Red LED to low to indicate sensor is running
  
  //Initialize WiFi//
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to the firebase
  Firebase.reconnectWiFi(true);
  /////

  ////////////////////////////////////////////////////////////////////////////

}


//////////////////////////////////FUNCTION TO READ OXIMETER VALUE/////////////

int readsensor() {
  long irValue = particleSensor.getIR();    //Reading the IR value it will permit us to know if there's a finger on the sensor or not
  Serial.println(i);                                           //Also detecting a heartbeat
  if(irValue > 7000){                                           //If a finger is detected
    int Status_of_sensor=1;
    Serial.print("BPM:");
    Serial.println("loop1");
    
    if (checkForBeat(irValue) == true)                        //If a heart beat is detected
    {
      Serial.print("BPM:");Serial.println(beatAvg);      //We sensed a beat!
      long delta = millis() - lastBeat;                   //Measure duration between two beats
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM

    if (beatsPerMinute < 255 && beatsPerMinute > 20)               //To calculate the average we strore some values (4) then do some math to calculate the average
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

}
  if (irValue < 7000){       //If no finger is detected it inform the user and put the average BPM to 0 or it will be stored for the next measure
     beatAvg=0;
     Serial.print("BPM:");Serial.println("Place ur finger");
     int Status_of_sensor=0;
     }
return(beatAvg);
}

////////////////////////////////MAIN LOOP//////////////////////////////////

void loop()
{ 
  String Reading;
  float h ;
  if(Valid==0){
  for(int i=0; i<500;i++){
  h = readsensor();}
  }
  else{
  for(int i=0; i<50;i++){
  h = readsensor();}  }
  Serial.println(h);
  Serial.println("////////////////////Sending___data/////////////////////////");
  if(h!=0){
  Valid =1;  
  arrayofbpm[i1]=h;
  for(int p=0;p<i1;p++){
  Reading = Reading +","+ String(arrayofbpm[p]);
  }}
  boolean res;
  Serial.println("////////////////////data____sent/////////////////////////");
  json.set("/data", Reading);//arrayofbpm);
  if(h != 0){
      res= Firebase.updateNode(firebaseData,"/ID01",json);
      json1.set("/status", "ACTIVE");
      Firebase.updateNode(firebaseData,"/ID01",json1);
  }else{
      json1.set("/status", "place your finger");
      res= Firebase.updateNode(firebaseData,"/ID01",json1);
      Reading=" ";  
      Valid =0;    
  }
  
 if (res)     
    {
      Serial.println("PASSED");
      Serial.println();
    }
 else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println();
    }
  delay(100);
  i1+=1;
  if(i1==10){i1=0;}
}
