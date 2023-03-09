//
// Created by Waffles on 2/26/23.
//

#ifndef CAPSTONESPRING2023_DHT20_H
#define CAPSTONESPRING2023_DHT20_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"


//Struct to hold, should be a pointer to save space
typedef struct{
  float tempature;
  float humidity;
} DHT_Data;

//Decided to use C++ for easier use for teammates/future students
class DHT20 {

private:
    int _I2CAddress;
    uint _SDAPin;
    uint _SCLPin;


public:

    DHT20(uint SDAPin, uint SCLPin, int address = 0x38){
        _SDAPin = SDAPin;
        _SCLPin = SCLPin;
        _I2CAddress = address;


        gpio_set_function(_SDAPin, GPIO_FUNC_I2C);
        gpio_set_function(_SCLPin, GPIO_FUNC_I2C);
        gpio_pull_up(SDAPin);
        gpio_pull_up(SCLPin);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(SDAPin,SCLPin, GPIO_FUNC_I2C));



    }

    void getData(DHT_Data& data);

    bool isReady();

    void intializeRegisters();





};


#endif //CAPSTONESPRING2023_DHT20_H
