#include "Arduino.h"
#include "HardwareTimer.h"

#define MOTOR PA8

HardwareTimer timer(1);

void startMotor(uint8_t pin) {
    Serial1.println("Starting pwm on 1ms duty cycle to start the ESC");
    pwmWrite(pin, 3449);
}

void resetMotor(uint8_t pin){
    // This function has not been tested!
    Serial1.println("Resetting the ESC...");
    pwmWrite(pin, 6898);
    delay(500);
    pwmWrite(pin, 3449);
    delay(500);
}

void setMotorSpeed(uint8_t pin, uint16_t duty){
    Serial1.print("Writing new duty: ");
    Serial1.println(duty);
    pwmWrite(pin, duty);
}
