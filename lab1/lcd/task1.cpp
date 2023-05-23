#include "mbed.h"
#include "C12832.h"
AnalogIn mypotentiometer(p20);
C12832 lcd(p5,p7,p6,p8,p11);
int main() {
    while(1) {
        float reading = mypotentiometer.read();//Read voltage from potentiometer
        lcd.locate(1,1);
        lcd.printf("The voltage is : %f V",reading);//print the value on lcd
        wait(0.1);
        lcd.cls();
        
    }
}


