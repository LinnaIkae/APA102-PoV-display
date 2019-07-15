#include "Arduino.h"
#include "HardwareTimer.h"
#define MOTOR PA1

HardwareTimer timer(1);

void handler_motor_up(void){
    digitalWrite(MOTOR, HIGH);
}

void handler_motor_down(void){
    digitalWrite(MOTOR, LOW);
}

void setup()
{
    Serial1.begin(9600);
    Serial1.println("Hello there");
    pinMode(PA1, OUTPUT);
    // Desired frequency = 500 Hz
    // SysClk frequency = 72 MHz
    // Prescaler = 72 => Scaled frequency = 1 MHz
    // Overflow = 2000
    // Overflowing frequency = 500 Hz.
    timer.pause();
    timer.setPrescaleFactor(72);
    timer.setOverflow(2000);
    timer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 0);
    timer.setMode(TIMER_CH2, TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH2, 1000); // Set to 1 ms pulse initially.
    timer.attachInterrupt(TIMER_CH1, handler_motor_up);
    timer.attachInterrupt(TIMER_CH2, handler_motor_down);
    timer.refresh();
    timer.resume();
}

void loop()
{
    if(Serial1.available() > 0){
        int newCompare = Serial1.read();
        Serial1.println(newCompare);
        timer.setCompare(TIMER_CH2, newCompare);
        delay(500);
    }
}
