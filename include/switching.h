

int switchStatus = 0;


void SetSwitch(){
    if(switchStatus == 0){
        switchStatus = 1;
        digitalWrite(RelayPin,RelayON);
    }else{
        switchStatus = 0;
        digitalWrite(RelayPin,RelayOFF);
    }

Serial.print("Switched to " );
Serial.println(switchStatus);

}