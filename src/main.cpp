#include <Arduino.h>

#define UseWifi 1

#define SensorPin 4 //D2
#define RelayPin 5 //D1

#define PinGreen 12
#define PinRed 13
#define PinBlue 14

#define RelayON 1
#define RelayOFF 0




#include "wifi_and_ota.h"
#include "setup_master.h"
#include "switching.h"
#include "loop_master.h"
#include "colorset.h"

void setup() {
    setup_master(); 
}

void loop() {
    loop_master();
}