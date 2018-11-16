#define BOUNCE_WITH_PROMPT_DETECTION
#include <Bounce2.h>
Bounce debouncer = Bounce(); // Instantiate a Bounce object

int LongPress = 500;
int ResetFullLength = 30000;
int FullSwitchDelay = 1000;

void SwitchPower(int PowerState){
    static unsigned long LastSwitchTime;
    if(LastSwitchTime < (millis()- FullSwitchDelay)){
    if (PowerState == 1){
    SERIAL.println("Switch LEDs on");
        SetNewDimm(100);
    }else{
    SERIAL.println("Switch LEDs off");        
        SetNewDimm(0);
    }
    }
}


void SetSwitch(){
    if(switchStatus == 0){
        switchStatus = 1;
        digitalWrite(RelayPin,RelayON);
    }else{
        switchStatus = 0;
        digitalWrite(RelayPin,RelayOFF);
    }
SwitchPower(switchStatus);
SERIAL.print("Switched to " );
SERIAL.println(switchStatus);

}


void sensor_setup(){
        debouncer.attach(SensorPin); // Attach the debouncer to a pin with INPUT_PULLUP mode
        debouncer.interval(10); // Use a debounce interval of 25 milliseconds
        //debouncer.debugOutput()
}

void sensor_loop(){
    static byte OldVal;
    static byte NewVal;
    static unsigned long triggered;
    int doSwitch;
    debouncer.update(); // Update the Bounce instance
   
    NewVal = debouncer.read();
    doSwitch = 1;
    if( debouncer.rose() ){
        triggered = millis();
    }

    if (NewVal == HIGH){
        if(NewVal == OldVal){
            //wenn länger als x gedrückt dimmen
            if (debouncer.duration() > LongPress){
                    colorset_dimmdowm();
                    doSwitch = 0;
            }
        }
    }else{

    } 



   if ( debouncer.fell() ) {  // Call code if button transitions from HIGH to LOW

     if(debouncer.previousDuration()> LongPress){
                if(mdebug == 1){
                    SERIAL.print( "Untriggered after :");
                    SERIAL.println(debouncer.previousDuration());
                }       
     }else{
                if(mdebug == 1){
                    SERIAL.print( millis()/1000);
                    SERIAL.println("s - Switched");
                }       
         SetSwitch();
     }
   }
   OldVal = NewVal;
}

