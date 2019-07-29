#include <vector>
#include "Arduino.h"
#include "SPI.h"
#include "APA102.hpp"

SPIClass SPI_2(2);

APA102 strip1(25, SPI, 2);
APA102 strip2(25, SPI_2, 2);

void setup()
{
    Serial1.begin(9600);
    Serial1.println("Hello there.");

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE_0);
    SPI.setClockDivider(SPI_CLOCK_DIV4); // 76 MHz / 4 = 19 MHz about.
    // 38 MHz is too much (for 72 leds), the data gets garbled and random colours appear.

    SPI_2.begin(); 
    SPI_2.setBitOrder(MSBFIRST);
    SPI_2.setDataMode(SPI_MODE_0);
    SPI_2.setClockDivider(SPI_CLOCK_DIV4);
   
    // pinMode(MOTOR, PWM);

    // timer.pause();
    // timer.setPrescaleFactor(21);
    // timer.refresh();
    // timer.resume();

    // startMotor(MOTOR);
    // delay(5000);
}

void loop()
{

    delayMicroseconds(1000);
    color_BGR all_b = {255, 0, 0};
    color_BGR all_g = {0, 255, 0};
    color_BGR all_r = {0, 0, 255};

    std::vector<color_BGR> colors1 = {all_b, all_b, all_b, all_g, all_g, all_b, all_b, all_b, all_g, all_g,
    all_b, all_b, all_b, all_g, all_g, all_b, all_b, all_b, all_g, all_g, all_b, all_b, all_b, all_g, all_g};
    std::vector<color_BGR> colors2;
    colors2 = colors1;
    colors2[2] = {122,122,12};

    strip1.writeLeds(colors1);
    strip2.writeLeds(colors2);
    // Serial1.println("PWM cycling through lowest to highest");
    // for(int duty=3549; duty < 6898; duty+=100){    
    //     if(duty == 4449){
    //         resetMotor(MOTOR);
    //     }
    //     else{
    //     setMotorSpeed(MOTOR, duty);
    //     }
    //     delay(2000);
    // }
}
