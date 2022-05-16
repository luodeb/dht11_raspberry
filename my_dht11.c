#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void hello(int a){
    printf("%d",a);
}

unsigned long init_dht11(int pinNumber){ // 初始化dht11
    if (-1 == wiringPiSetup()) {
        printf("Setup wiringPi failed!");
        return 1;
    }
  
    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level 
    return 0;
}

unsigned long readSensorData(int pinNumber)
{   
    unsigned long databuf;
    unsigned char crc; 
    unsigned char i;
    int HIGH_TIME = 32;
  
    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 0); // output a high level 
    delay(25);
    digitalWrite(pinNumber, 1); // output a low level 
    pinMode(pinNumber, INPUT); // set mode to input
    pullUpDnControl(pinNumber, PUD_UP);
 
    delayMicroseconds(27);
    if (digitalRead(pinNumber) == 0) //SENSOR ANS
    {
        while (!digitalRead(pinNumber))
            ; //wait to high
 
        for (i = 0; i < 32; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            databuf = databuf * 2;
            if (digitalRead(pinNumber) == 1) //1
            {
                databuf++;
            }
        }
 
        for (i = 0; i < 8; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            crc *= 2;  
            if (digitalRead(pinNumber) == 1) //1
            {
                crc++;
            }
        }
        return databuf;
    }
    else
    {
        return 0;
    }
}

void preRead(int pinNumber){
    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level 
    // delay(3000);
}
