#include "Arduino.h"
#include "SPI.h"

SPIClass SPI_2(2);

void SPI_write32(uint32_t data){
    uint16_t top_bits = data >> 16;    //Shifting away the lowest 16 bits
    uint16_t bottom_bits = data & 0xFFFF; // Binary AND to only preserve the lowest 16 bits
    SPI.write16(top_bits);
    SPI.write16(bottom_bits);
}
void SPI2_write32(uint32_t data){
    uint16_t top_bits = data >> 16;    //Shifting away the lowest 16 bits
    uint16_t bottom_bits = data & 0xFFFF; // Binary AND to only preserve the lowest 16 bits
    SPI_2.write16(top_bits);
    SPI_2.write16(bottom_bits);
}
uint8_t writeLEDFrame(uint8_t brightness,
    uint8_t blue, uint8_t green, uint8_t red){
    // Send 1 LED frame according to APA102C specification
    if(brightness > 31){
        Serial1.println("Brightness out of range 0-31");
        return 1; 
    }
    uint8_t start = (0b111 << 4) | brightness;
    uint32_t frame = (start << 24) | (blue << 16) | (green << 8) | red;
    SPI_write32(frame);
    return 0;
}
uint8_t writeLEDFrame2(uint8_t brightness,
    uint8_t blue, uint8_t green, uint8_t red){
    // Send 1 LED frame according to APA102C specification
    if(brightness > 31){
        Serial1.println("Brightness out of range 0-31");
        return 1; 
    }
    uint8_t start = (0b111 << 4) | brightness;
    uint32_t frame = (start << 24) | (blue << 16) | (green << 8) | red;
    SPI2_write32(frame);
    return 0;
}


void setup()
{
    Serial1.begin(9600);
    Serial1.println("Hello there.");

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE_0); // Might want to test this with other modes.
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

uint8_t loop_count = 0;
void loop()
{
   loop_count++;
   if(loop_count > 25){
       loop_count = 0;
   }
     // Writing start frame
    SPI_write32(0x00000000);
    SPI2_write32(0x00000000);
    //delay(100);
    // Writing all LED's
    for(int i=0; i<25; i++){
        // if(loop_count % 2 == 0){
        //     uint8_t rand1 = rand() % 255;
        //     uint8_t rand2 = rand() % 255;
        //     uint8_t rand3 = rand() % 255;
            
        //     writeLEDFrame(1, rand1, rand2, rand3);
        // }
        if(i==loop_count){
            writeLEDFrame(1, 0x00, 0x00, 0xFF);
            writeLEDFrame2(1, 0x00, 0x00, 0xFF);
        }
        else{
            writeLEDFrame(0,0x00,0x00,0x00);
            writeLEDFrame2(0,0x00,0x00,0x00);
        }
    }

    //Writing end frame
    SPI_write32(0xFFFFFFFF); //End frame needs to be n/2 1'bits where n is number of leds.
    SPI2_write32(0xFFFFFFFF); //End frame needs to be n/2 1'bits where n is number of leds.

    delayMicroseconds(1000);

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
