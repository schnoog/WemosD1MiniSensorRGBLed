

int switchStatus = 0;



void SwitchPower(int PowerState){
    if (PowerState == 1){
    SERIAL.println("Switch LEDs on");
        colorset_set(PinGreen,LevelGreen);
        colorset_set(PinBlue,LevelBlue);
        colorset_set(PinRed,LevelRed);
    }else{
    SERIAL.println("Switch LEDs off");        
        colorset_set(PinGreen,0);
        colorset_set(PinBlue,0);
        colorset_set(PinRed,0);
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