
int val = 0;
int lastval = 0;

unsigned long Timer1;
unsigned long Timer2;
unsigned long Timer3;
unsigned long Timer4;


void loop_master(){
    unsigned long NowIs = millis();
    if(UseWifi == 1){
        wifi_loop();
    }


    if(Timer1 < NowIs - 1000){                      //LOOP FOR SENSOR REED
            val = digitalRead(SensorPin);
            if (lastval == 0){
                if(val == 1){
                    SetSwitch();
                }
            }
            lastval = val;
    Timer1 = NowIs;
    }

    colorset_loop();
    webserver_loop();


}
