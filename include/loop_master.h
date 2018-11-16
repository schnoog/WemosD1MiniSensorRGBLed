
int val = 0;
int lastval = 0;

unsigned long Cronny;
unsigned long Timer1;
unsigned long Timer2;
unsigned long Timer3;
unsigned long Timer4;
int intT1Wait = 1;
int intT2Wait;
int intT3Wait;
int intT4Wait;

void loop_master(){
   
    unsigned long NowIs = millis();
    if(UseWifi == 1){
        wifi_loop();
    }


/*
*
*   Runs every second
*/
    if(Cronny < NowIs - 1000){
        //colorset_dimmdowm();




        Cronny = NowIs;
    }
/*
*
*/


/*
    if(Timer1 < NowIs - intT1Wait){                      //LOOP FOR SENSOR REED
            intT1Wait = 1;
            val = digitalRead(SensorPin);
            if (lastval == 0){
                if(val == 1){
                    SetSwitch();
                    intT1Wait = 1000;
                }
            }
            lastval = val;
    Timer1 = NowIs;
    }
*/

/*********************************
 ********************************/

    colorset_loop();
    webserver_loop();
    filework_loop();
    sensor_loop();
}
