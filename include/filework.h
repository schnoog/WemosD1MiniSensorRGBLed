
#include "FS.h"

void filework_setup(){
    SPIFFS.begin();

    if (!SPIFFS.exists("/Red.txt")){
        File f = SPIFFS.open("/Red.txt", "w");
        f.println("255");
        f.close();
    }

    if (!SPIFFS.exists("/Blue.txt")){
        File f = SPIFFS.open("/Blue.txt", "w");
        f.println("255");
        f.close();
    }
    if (!SPIFFS.exists("/Green.txt")){
        File f = SPIFFS.open("/Green.txt", "w");
        f.println("255");
        f.close();
    }    
    if (!SPIFFS.exists("/Dimm.txt")){
        File f = SPIFFS.open("/Dimm.txt", "w");
        f.println("100");
        f.close();
    }

}
void filework_loop(){

}

void SetGreen(int PinSet){
    File f = SPIFFS.open("/Green.txt", "w");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        
    }
    f.println(PinSet);
    f.close();    
}

void SetRed(int PinSet){
    File f = SPIFFS.open("/Red.txt", "w");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        
    }
    f.println(PinSet);
    f.close();    
}

void SetBlue(int PinSet){
    File f = SPIFFS.open("/Blue.txt", "w");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        
    }
    f.println(PinSet);
    f.close();    
}
int GetRed(){
    File f = SPIFFS.open("/Red.txt", "r");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        return 255;
    }
    String s=f.readStringUntil('\n');
    int out = s.toInt();
    return out;
}

int GetGreen(){
    File f = SPIFFS.open("/Green.txt", "r");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        return 255;
    }
    String s=f.readStringUntil('\n');
    int out = s.toInt();
    return out;
}

int GetBlue(){
    File f = SPIFFS.open("/Blue.txt", "r");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        return 255;
    }
    String s=f.readStringUntil('\n');
    int out = s.toInt();
    return out;
}

int GetDimm(){
    File f = SPIFFS.open("/Dimm.txt", "r");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        return 100;
    }
    String s=f.readStringUntil('\n');
    int out = s.toInt();
    
    return out;
}

void SetDimm(int DimmLevel){
    File f = SPIFFS.open("/Dimm.txt", "w");
    if (!f) {
        SERIAL.println("Coulnd't open file");
        
    }
    f.println(DimmLevel);
    f.close();    
}