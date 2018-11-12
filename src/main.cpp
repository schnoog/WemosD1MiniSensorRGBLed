#include <Arduino.h>

#define UseWifi 1
#define SensorPin 4 //D2
#define RelayPin 5 //D1
#define PinGreen 14
#define PinRed 12
#define PinBlue 13 //fixed
#define RelayON 1
#define RelayOFF 0


#include "wifi_and_ota.h"
#include "filework.h"

#include "colorset.h"

#include "switching.h"

#include "webserver.h"
/*
*
*
*/
#include "setup_master.h"
#include "loop_master.h"
void setup() {
    setup_master(); 
}

void loop() {
    loop_master();
}