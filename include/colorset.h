



int HighOn = 1;
int Level = 255;
int LevelRed = 255;
int LevelGreen = 5;
int LevelBlue =5;


void colorset_set(int SPIN, int color){
    int finalcolor = color;
    if (HighOn < 1){
        finalcolor = 255 - color;
    }
    analogWrite(SPIN, finalcolor);
}


void colorset_setup(){
    analogWriteRange(255);
    colorset_set(PinGreen,LevelGreen);
    colorset_set(PinBlue,LevelBlue);
    colorset_set(PinRed,LevelRed);
}

void colorset_loop(){


}



