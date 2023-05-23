/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "C12832.h"
#include "RGBLed.h"
#include <cstdio>
LocalFileSystem local("local");
DigitalIn Up(p15);
DigitalIn Down(p12);
DigitalIn Left(p13);
DigitalIn Right(p16);
DigitalOut led(LED3);
DigitalOut blinker1(LED1);
DigitalOut blinker2(LED2);
DigitalOut blinker3(LED3);
DigitalOut blinker4(LED4);

InterruptIn Start(p14);

C12832 lcd(p5,p7,p6,p8,p11);

RGBLed myRGBled(p23,p24,p25);

AnalogIn pot(p19);

int highscore = 0;

bool stats = false;
int velX = 4, velY = 4;
float del = 0.0;
//rectangle
    static char rek[]={
        0x70,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x50,
        0x70,
        
        
        };
        
        Bitmap Bitrek = {
        8,
        16,
        1,
        rek
        };

int create_file(){
        FILE *File1 = fopen("/local/example.txt", "r"); // Open file in read mode

    if (File1 == NULL) {
        // create file if does not exist
        File1 = fopen("/local/example.txt", "w"); // Open file in write mode

        if (File1 == NULL) {
            return 1;
        }

        fclose(File1);

    } else {
        fclose(File1);

    }
    return 0;
}
int high_score(){
        int j = 0;
        int i = 0;
        FILE* File1 = fopen("/local/example.txt","r"); 
        while(!feof(File1)){
            fscanf(File1, "%d", &j);
            if(j > i){
            i = j;
            }
        }
        
        fclose(File1);
        return i;
}

void update_hs(int score){
    lcd.cls();
    lcd.locate(1.0,1.0);
    lcd.printf("New highscore : %d", score);
    wait(0.02);

    FILE* File1 = fopen("/local/example.txt","a");
    fprintf(File1, "\n%d", score);
    fclose(File1);

    for(int i = 0; i < 7; i++){
        blinker1 = blinker2 = blinker3 = blinker4 = 1;
        wait(0.01);
        blinker1 = blinker2 = blinker3 = blinker4 = 0;
        wait(0.01);
    }
    
}
void play(){
    lcd.cls();
    //t.reset();
    int x = 60;
    int y = 15;
    int score = 0;
    float xPos = 115;
    float yPos = 15;
    int radius = 2;
    //t.start();
    while (1) {
   // lcd.rect(120, yPos1, 115, yPos2, 1); 
    lcd.locate(xPos, yPos);  
    lcd.print_bm(Bitrek, xPos, yPos);
    lcd.copy_to_lcd();
    x -= velX;
    y -= velY;
        
    if(Up == 1){
        if(yPos>=2){                
            yPos = yPos-2;
            lcd.locate(xPos, yPos);
            lcd.cls();
            lcd.print_bm(Bitrek, xPos, yPos);
            lcd.copy_to_lcd();
        }
    }
    if(Down == 1){
        if(yPos<16){                                
            yPos = yPos+2;
            lcd.locate(xPos, yPos);
            lcd.cls();
            lcd.print_bm(Bitrek, xPos, yPos);
            lcd.copy_to_lcd();
        }
    }

    if (x >= 128 - radius || x <= radius) {
       velX = -velX;
    }
    if (y >= 30 - radius || y <= radius) {
       velY = -velY;
    }
    if(x <= 123 && x > 110 && (y>yPos && y<(yPos + 16))){
        velX = -velX;
    }
    if(x == 128 && (y>yPos && y<(yPos + 16))){
        velX = -velX;
    }
    if(x < 2){
        score ++;
        myRGBled.setColor(RGBLed::GREEN);
    }
    else{
        myRGBled.setColor(RGBLed::BLACK);
    }

    if(x > 120){
        lcd.cls();
        lcd.locate(1.0,1.0);
        lcd.printf("Hahaha, Game over xd\n");
    //lcd.printf("Total time is %.2f sec\n", t.read());
    myRGBled.setColor(RGBLed::RED);
        wait(0.01);
        highscore = high_score();
    
    if(score > highscore)
        update_hs(score);
    break;
    }
    lcd.locate(5, 18);
    lcd.printf("score : %d ",score);

    lcd.circle(x, y, radius,1);//print a circle
    wait(del);
    lcd.cls();
    }

}
void start_screen(){ //Displays start menu//
    lcd.cls();
    lcd.locate(0,0);
    int potInput = pot * 2;
    lcd.printf("Press joystick to play...");
        if(potInput == 0){ //EASY
        velX = 4;
        velY = 4;
        del = 0.01;
        lcd.locate(0,10);
        lcd.printf("Easy");
    }

    else if(potInput == 1){ //HARD
        velX = 8;
        velY = 8;
        del = 0.006;
        lcd.locate(0,10);
        lcd.printf("Hard");
        }
    wait(0.005);
        if(stats == true){
    play();
    }
}
void test(){
    stats = true;
}


int main(){
    Start.rise(&test);
    create_file();
    

while(1){
    start_screen();
    wait(0.1);
    start_screen();
    stats = false;
    wait(0.01);
}
}

