



int HighOn = 1;
int Level = 255;
int LevelRed = 255;
int LevelGreen = 5;
int LevelBlue =5;

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
    analogWrite(SPIN, finalcolor);
}


void colorset_setup(){
    analogWriteRange(255);
    LevelRed = GetRed();
    LevelGreen = GetGreen();
    LevelBlue = GetBlue();
    colorset_set(PinGreen,LevelGreen);
    colorset_set(PinBlue,LevelBlue);
    colorset_set(PinRed,LevelRed);
}

void colorset_loop(){


}



