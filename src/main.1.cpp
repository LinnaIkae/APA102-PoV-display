#include "Arduino.h"
#include "Servo.h"
#define MOTOR PA1

int onTime;
void setup()

//min pwm 44000. max 65535, startup with 27000?

{
    Serial1.begin(9600);
    pinMode(PA1, PWM);

    // This is necessary to start the ESC reliably.
    // Numbers might change.
    Serial1.println("Startup with 10000 - 20000 duty cycle slope.");
    for(int i = 10000; i<30000; i+=1000){
        pwmWrite(MOTOR, i);
        Serial1.println(i);
        delay(500);
    }

    Serial1.println("Motor starting...");
    onTime = 47000;
    pwmWrite(MOTOR, onTime);
}

void loop()
{

    // onTime += 1000;
    // if(onTime > 65535){
    //     onTime = 10000;
    // }
    // pwmWrite(MOTOR, onTime);
    // Serial1.print("New onTime:");
    // Serial1.println(onTime);
    // delay(500);
}
