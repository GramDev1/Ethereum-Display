/*
 * Project ethdisplay
 * Description:
 * Author:
 * Date:
 */
#include "SevSeg.h"
SevSeg seg;
Timer timer(30000,getETH);
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  seg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  Particle.subscribe("hook-response/eth", update);
  timer.start();
}
// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  seg.refreshDisplay();

}
//YES, IT SHOULD BE A NUMBER
void write(String number) {
  float update = number.toFloat();
  seg.setNumber(update,2);
}
//This will only be called on the hook recieve, so..
void update(const char *event, const char *data){
  String num = String(data);
  write(num);
}
//Publish some data
void getETH(){
  Particle.publish("eth","nerp",PRIVATE);
}
