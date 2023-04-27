/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/helen/OneDrive/Documents/schoolStuff/CRT499/code/TDStest1/TDStest1/src/TDStest1.ino"
#include "GravityTDS.h"                 
#include <Wire.h>
void setup();
void loop();
#line 3 "c:/Users/helen/OneDrive/Documents/schoolStuff/CRT499/code/TDStest1/TDStest1/src/TDStest1.ino"
GravityTDS gravityTds;
int tdsPin = A1;
int turbPin = A2;                   
float volt;
float ntu;
float temperature = 25;
float tdsValue = 0;

float turb;
float tds;
float turbAvg;
float tdsAvg;
String sensorNum = "2"; //XXX

void setup()
{
    //Serial.begin(115200);
    gravityTds.setPin(tdsPin);
    gravityTds.setAref(3.3);                //reference voltage on ADC
    gravityTds.setAdcRange(4096);           //4096 for 12bit ADC -- Boron is 12bit
    gravityTds.begin();                     //initialization
}
 
void loop(){
   if(Particle.connected()){
  //defining sleep settings
SystemSleepConfiguration config;
config.mode(SystemSleepMode::ULTRA_LOW_POWER)
   .gpio(D2, FALLING)
   .duration(12h);		     // Set seconds until wake
// Particle.publish("Going To Sleep");
SystemSleepResult result = System.sleep(config);    // Device sleeps here

if (result.wakeupPin() == D2) {              // Woke by pin interrupt
    //code to take sensor readings
    gravityTds.update();  //sample and calculate

    for(int i = 0; i<= 100; i++){
    tdsAvg += gravityTds.getTdsValue();  // then get the value
    //sensorValue += analogRead(turbPin);
    }
    tds = tdsAvg/500;
    turbAvg = analogRead(turbPin);
    turb = turbAvg * (5 / 4096.0); //XXX

       Particle.publish("reading","?sensorNum="+sensorNum+"&turb="+turb+"&tds="+tds+"&time=", PRIVATE); //publising it to the cloud
       delay(2000);
      
}
else {                                       // Woke by time
    //code to take sensor readings
    gravityTds.update();  //sample and calculate

    for(int i = 0; i<= 100; i++){
    tdsAvg += gravityTds.getTdsValue();  // then get the value
    //sensorValue += analogRead(turbPin);
    }
    tds = tdsAvg/500;
    turbAvg = analogRead(turbPin);
    turb = turbAvg * (5 / 4096.0); //XXX

       Particle.publish("reading","?sensorNum="+sensorNum+"&turb="+turb+"&tds="+tds+"&time=", PRIVATE); //publising it to the cloud
       delay(2000);
      }
}
 }
