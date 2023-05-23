#include "mbed.h"
DigitalIn Up(p15);
DigitalIn Down(p12);
DigitalIn Reset(p14);
DigitalIn Right(p16);
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myLed3(LED3);
DigitalOut myLed4(LED4);

int main() {
    while(1) {
        if (Right == 1) // if right turn led3 on
            myLed3 = 1;
        if (Up == 1) // if up turn led2 on
            myled2 = 1;
        if (Down == 1) // if down turn led4 on
            myLed4 = 1;
        if(Reset == 1){ // if the button is pushed turn all leds off
            myled2 = 0;
            myLed3 = 0;  
            myLed4 = 0;  
        }
            
    }
}
