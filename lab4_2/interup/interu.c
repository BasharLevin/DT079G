/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <stdio.h>

void ISR1();                     
void ISR2();
InterruptIn intr(p14);  
DigitalOut led_1(LED1); 
DigitalOut led_2(LED2);      
DigitalOut led_3(LED3);

int main(){

intr.rise(&ISR1);         
intr.fall(&ISR2);         

while(1){
    
    led_1 =!led_1;
    
    wait(0.1);             
    
    }

    return 0;

}



void ISR1(){
led_2 =! led_2;  
wait(0.025);  

}

void ISR2(){
led_3 =! led_3;  
wait(0.025);  

}

