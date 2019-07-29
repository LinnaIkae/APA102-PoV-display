#include "APA102.hpp"
APA102::APA102(uint16_t num_leds, SPIClass& SPI_n, uint8_t brightness):
    num_leds(num_leds), SPI_n(SPI_n), brightness(brightness) {
        this->end_frame_bits = num_leds/2;
    };

bool APA102::writeFrame(color_BGR bgr){
    // Send 1 LED frame according to APA102C specification
    uint8_t start = (0b111 << 4) | this->brightness;
    uint32_t frame = (start << 24) | (bgr.b << 16) | (bgr.g << 8) | bgr.r;
    uint16_t top_bits = frame >> 16;    //Shifting away the lowest 16 bits
    uint16_t bottom_bits = frame & 0xFFFF; // Binary AND to only preserve the lowest 16 bits
    SPI_n.write16(top_bits);
    SPI_n.write16(bottom_bits);
    return true;
}

bool APA102::writeLeds(std::vector<color_BGR> bgr_vect){
    // Writes all the leds. Input is a pointer to an array of structs of color.
    // Writing start frame
    SPI_n.write16(0x0000);
    SPI_n.write16(0x0000);
    for(auto bgr: bgr_vect){
        // Iterate through the array with bgr which is a pointer
        // Every iteration the pointer should move to the next struct beginning.
        // The bgr is then defererenced and passed to writeFrame.
        this->writeFrame(bgr);
    }
    // Writing end frame 
    for(int i=0; i<this->end_frame_bits; i+=16){
        SPI_n.write16(0xFFFF);
    }
    return true;
}
