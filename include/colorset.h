



int HighOn = 1;
int Level = 255;
int LevelRed = 255;
int LevelGreen = 5;
int LevelBlue =5;
int LevelDimm = 100;
int DimmStep = 10;
int DimmStepDelay = 750;
int switchStatus;


void setMaxCorrelation(){
    int Max = 255;
    float fac1;
    float fac2;
    float MaxF;
    MaxF = (float)Max;
    fac1 = MaxF / LevelRed;
    fac2 = MaxF / LevelBlue;
    if (fac2 < fac1){fac1 = fac2;}
    fac2 = MaxF / LevelGreen;
    if (fac2 < fac1){fac1 = fac2;}
    fac1 = fac1 * 100;
    LevelRed = ((int)fac1 * LevelRed);
    LevelBlue = ((int)fac1 * LevelBlue);
    LevelGreen = ((int)fac1 * LevelGreen);
    LevelRed = LevelRed / 100;
    LevelBlue = LevelBlue / 100;
    LevelGreen = LevelGreen / 100;
}

void SetLevelRed(int Red){
    LevelRed = Red;
    SetRed(Red);
}


void SetLevelGreen(int Green){
    LevelGreen = Green;
    SetGreen(Green);
}
void SetLevelBlue(int Blue){
    LevelBlue = Blue;
    SetBlue(Blue);
}

void colorset_set(int SPIN, int color){
    int finalcolor = color;
    if (HighOn < 1){
        finalcolor = 255 - color;
    }
    finalcolor = finalcolor * LevelDimm / 100;
    analogWrite(SPIN, finalcolor);
}


void colorset_setup(){
    analogWriteRange(255);
    analogWriteFreq(64000);
    LevelRed = GetRed();
    LevelGreen = GetGreen();
    LevelBlue = GetBlue();
    LevelDimm = GetDimm();
    setMaxCorrelation();
    colorset_set(PinGreen,LevelGreen);
    colorset_set(PinBlue,LevelBlue);
    colorset_set(PinRed,LevelRed);
    switchStatus = 1;
}



void SetNewDimm(int NeDimm){
    static int lastDimm;

    LevelDimm = NeDimm;
    SetDimm(LevelDimm);
    LevelRed = GetRed();
    LevelGreen = GetGreen();
    LevelBlue = GetBlue();
    setMaxCorrelation();
    
    if(NeDimm > lastDimm){
        for (int i = lastDimm; i <= NeDimm; i++){
            LevelDimm = i;
            colorset_set(PinGreen,LevelGreen);
            colorset_set(PinBlue,LevelBlue);
            colorset_set(PinRed,LevelRed);
            delay(2); 
        }
    }
    if(NeDimm < lastDimm){
        for (int i = lastDimm; i >= NeDimm; i--){
            LevelDimm = i;
            colorset_set(PinGreen,LevelGreen);
            colorset_set(PinBlue,LevelBlue);
            colorset_set(PinRed,LevelRed); 
            delay(10);
        }
    }
    LevelDimm = GetDimm(); 

    colorset_set(PinGreen,LevelGreen);
    colorset_set(PinBlue,LevelBlue);
    colorset_set(PinRed,LevelRed); 


    lastDimm = NeDimm;   
}

void colorset_dimmdowm(){
    static unsigned long LastDimStep;
    int DimmStepFinal;
    static int direction; //1 ->down , 2 -> up
    if (direction < 1){direction = 1;}    
    if (LastDimStep < millis() - (unsigned long)DimmStepDelay ){
        if(mdebug == 1){
            SERIAL.print("Dimming from ");
            SERIAL.print(LevelDimm);
        }        
        if (LevelDimm < DimmStep){
            direction = 2;
        } 
        if (LevelDimm > (100 - DimmStep)){
            direction = 1;
        }
        if (direction == 1){
            LevelDimm = LevelDimm - DimmStep;
        }else{
            LevelDimm = LevelDimm + DimmStep;
        }

        //if ()
//        LevelDimm = LevelDimm - DimmStepFinal;
        SetNewDimm(LevelDimm);
        if(mdebug == 1){
            SERIAL.print(" to ");
            SERIAL.print(LevelDimm);
            SERIAL.print(" with step ");
            SERIAL.println(DimmStep);
        }
        LastDimStep = millis();
    }
}
 

void colorset_loop(){


}



