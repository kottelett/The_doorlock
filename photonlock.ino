#include <NexaCtrl/NexaCtrl.h>

#define TX_PIN D4
#define RX_PIN A1

const static unsigned long controller_id = 1234567;
unsigned int lock = 1;
bool light = false;

NexaCtrl nexaCtrl(TX_PIN, RX_PIN);
IPAddress remoteIP(192, 168, 1, 109);
String wifi = "null";
bool isLocked =false;

void setup(){

    Serial.begin(9600);
    Particle.publish("POWERGONE", "");    
    Particle.function("lock", lockToggle);
}
void loop(){

 if(wifi.length() >= 1 && isLocked == false) {
    lockToggle("unlock");
    isLocked = true; 
 }
 
 if(wifi.length() == 0 && isLocked == true) {
    lockToggle("lock");
    isLocked = false;
}

delay(2000);
wifi = WiFi.ping(remoteIP) + "";

}




int lockToggle(String args){
  
  if(args == "lock"){
    nexaCtrl.DeviceOn(controller_id, lock);
    light = true;
    return 1;
  }
  
  if(args == "unlock"){
    nexaCtrl.DeviceOff(controller_id, lock);
    light = false;
    return 2;
  }
  
  if(light){
    nexaCtrl.DeviceOff(controller_id, lock);
    light = false;
    return 1;
  }
  
  else{
    nexaCtrl.DeviceOn(controller_id, lock);
    light = true;
    return 2;
  }
  
}