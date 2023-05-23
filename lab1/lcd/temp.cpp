#include "mbed.h"
#include "C12832.h"
#include "LM75B.h"
DigitalOut myled(LED1);
C12832 lcd(p5,p7,p6,p8,p11);
LM75B tmp(p28,p27);
int main() {
    float board_temp;
    while(1) {
        
        lcd.locate(0,0); //clears LCD
        board_temp = tmp.read(); //read temperature
        //lcd.line(x0, y0, x1, y1, 1);
        lcd.line(4, 0, 4, 32, 1);
        lcd.line(0, 28, 128, 28, 1);
        float j;
        for (float i = 4; i<128; i++){
            j = tmp.read();
            lcd.pixel(i,28-j,1);
            lcd.copy_to_lcd();
            lcd.locate(5, 18);
            lcd.printf("temperature : %f C",j);
            wait(0.1);
            
        }
        lcd.cls();
        
     
    }
}


