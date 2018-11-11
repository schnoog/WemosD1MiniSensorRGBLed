
int val = 0;
int lastval = 0;


void loop_master(){

    if(UseWifi == 1){
        ota.loop();
    }

    val = digitalRead(SensorPin);     // read the input pin
//    digitalWrite(BUILTIN_LED, val);  // sets the LED to the button's value
//    Serial.print("Value: ");
//    Serial.println(val);

    if (lastval == 0){
        if(val == 1){
            SetSwitch();
            delay(1000);
        }
    }
    lastval = val;

delay(10);
}