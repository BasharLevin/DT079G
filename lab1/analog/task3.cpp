#include "mbed.h"
AnalogIn mypotentiometer(p20);
int main()
{
    
    float total_v=0; 
    float myled = 0;
    while(1) {
        
        for(int i = 0; i <20;i++){   
            float myled = mypotentiometer.read();//reads from potentiometer
            
        total_v +=myled;  
           
        }
        
        printf("the reading is : %f \n\r",total_v);
        printf("The avarge is : %f \n\r",total_v/20);// divided by 20 to get the avg
         wait(1.0);
        myled = 0;
        total_v = 0;
    }
}