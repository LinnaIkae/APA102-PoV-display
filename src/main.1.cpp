#include "Arduino.h"
#include "HardwareTimer.h"
#define MOTOR PA8

HardwareTimer timer(1);

void setup()
{
    Serial1.begin(9600);
    Serial1.println("Hello there");
    pinMode(MOTOR, PWM);
    // Frame time = 20 ms
    // On time 1-2 ms
    // SysClk frequency = 72 MHz
    // Overflow = 65535 (default)
    // Prescaler = 21 => Scaled input frequency = ~3,43 MHz
    // Overflow frequency = 3,43.. MHz / 65535 = 52,3166 Hz
    // Period = 19 ms
    timer.pause();
    timer.setPrescaleFactor(21);
    timer.refresh();
    timer.resume();

    Serial1.println("Starting pwm on 1ms duty cycle");
    pwmWrite(MOTOR, 3449);
    delay(10000);

}

void loop()
{
    Serial1.println("PWM cycling through lowest to highest");
    for(int duty=3549; duty < 6898; duty+=100){    
        Serial1.print("Writing new duty: ");
        Serial1.println(duty);
        pwmWrite(MOTOR, duty);
        // duty% = newDuty/65535 * 100%
        // duty ms = newDuty/65535 * 19 ms
        // duty 1 ms:
        //   newDuty = (1 ms * 65535) / 19 ms = 3449
        // duty 2 ms:
        //   newDuty = 6898
        delay(2000);
    }
}
