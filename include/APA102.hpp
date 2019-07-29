#pragma once

#include <vector>
#include "SPI.h"
#include "Arduino.h"

typedef struct{
    uint8_t b, g, r;
} color_BGR;

class APA102 {
    public:
    APA102(uint16_t num_leds, SPIClass& SPI_n, uint8_t brightness);
    virtual ~APA102();

    bool writeFrame(color_BGR bgr);
    bool writeLeds(std::vector<color_BGR> bgr_vect);
    private:
    uint16_t num_leds;
    uint16_t end_frame_bits;
    SPIClass& SPI_n;
    uint8_t brightness;

};