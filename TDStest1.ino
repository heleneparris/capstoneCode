#include "GravityTDS.h"                 
#include <Wire.h>
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



// // //------------code without sleep for troubleshooting purposes-----------------
// #include "GravityTDS.h"                 
// #include <Wire.h>
// GravityTDS gravityTds;
// int tdsPin = A1;
// int turbPin = A2;                   
// float volt;
// float ntu;
// float temperature = 25;
// float tdsValue = 0;
// float turb;
// float tds;
// float turbAvg;
// float tdsAvg;
// String sensorNum = "2";
// float sensorValue;

// void setup()
// {
//     //Serial.begin(115200);
//     gravityTds.setPin(tdsPin);
//     gravityTds.setAref(3.3);                //reference voltage on ADC
//     gravityTds.setAdcRange(4096);           //4096 for 12bit ADC -- Boron is 12bit
//     gravityTds.begin();                     //initialization
// }
 
// void loop(){
//   //defining sleep settings
//     //code to take sensor readings
//     gravityTds.update();  //sample and calculate

    

//     for(int i = 0; i<= 100; i++){
//     tdsAvg += gravityTds.getTdsValue();  // then get the value
//     //sensorValue += analogRead(turbPin);
//     }
//     tds = tdsAvg/500;
//     turbAvg = analogRead(turbPin);
//     turb = turbAvg * (6 / 4096.0);

//        Particle.publish("reading","?sensorNum="+sensorNum+"&turb="+turb+"&tds="+tds+"&time=", PRIVATE); //publising it to the cloud
//        delay(2000);

//     // volt = 0; xxx all this
//     // for(int i=0; i<800; i++)
//     // {
//     //     volt += ((float)analogRead(turbPin)/1023)*5;
//     // }
//     // volt = volt/800;
//     // //turb = round_to_dp(volt,2); xxx
//     // turb = volt;

//     //xxxxxxxxxxxxxxxxxxxxxxxxxx
//     // if(volt < 2.5){
//     //   turb = 3000;
//     // }else{
//     //   turb = -1120.4*(volt*volt)+5742.3*volt-4353.8;
//     // }
//     //xxxxxxxxxxxxxxxxxxxxxxxxxx
//    // turb = analogRead(turbPin)/1023*5;
//     //Particle.publish("Turbidity",String((float)analogRead(turbPin)/1023*5));
//      //publising it to the cloud
//     delay(2000);

//                                       // Woke by time
//    //code to take sensor readings
//    // gravityTds.update();  //sample and calculate
//     //tdsValue = gravityTds.getTdsValue();  // then get the value
//    // Particle.publish("TDS", String(tdsValue));
//     delay(2000);
    
// //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//     // volt = 0;
//     // for(int i=0; i<800; i++)
//     // {
//     //     volt += ((float)analogRead(turbPin)/1023)*5;
//     // }
//     // volt = volt/800;
//     // volt = round_to_dp(volt,2);
//     // if(volt < 2.5){
//     //   turb = 3000;
//     // }else{
//     //   turb = -1120.4*(volt*volt)+5742.3*volt-4353.8;
//     // }
//     //xxxxxxxxxxxxxxxxxxxxxxxxxxxx
//    // Particle.publish("Turbidity",String((float)analogRead(turbPin)/1023*5));
//       Particle.publish("reading","?sensorNum="+sensorNum+"&turb="+turb+"&tds="+tds+"&time=", PRIVATE); //publising it to the cloud

//     delay(5000);
// }
 

//---------------------rssi code--------------------------------------------//
// unsigned long old_time = 0;
// float strength;

// void setup() {

// }

// void loop() {
//   if (millis() - old_time > 5000) {
//     CellularSignal sig = Cellular.RSSI();
//     strength = sig.getStrength();
    
//     Particle.publish("Cellular Strength", String(strength) + "%", PRIVATE);
    
//     old_time = millis();
//   }
// }

