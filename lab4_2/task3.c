#include "mbed.h"
#include <stdio.h>

DigitalOut myled(LED3);
void blink();
void print();
int gen();
Timeout t;
InterruptIn button(p14);

int main() {
    int n = 0;
    while(1) {
        if (button == 1){
            n = gen();
            t.attach(&blink, n);
        }
    }
}

void blink(){
    myled = 1;
    wait(0.1);
    myled = 0;
}
void print(int x)
{
    for (int n = x; n >= 0; --n)
    {
        printf("%d\n", n);
        wait(1);
    }
}

int gen(){
    int range = 10 - 5 + 1;
    int num = rand() % range + 5;


    return num;
}
