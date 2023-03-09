#include <stdio.h>

#include "DHT20.h"

int main() {


    stdio_init_all();
    printf("start\n");


    i2c_init(i2c_default, 100000);

    printf("i2c init pass\n");


    DHT20 sensor = DHT20(8,9);
    printf("created sensor\n");

    sensor.intializeRegisters();
    printf("init registers\n");
    sleep_ms(100);
    while(!sensor.isReady()){

        printf("sensor is not ready waiting 50ms");
        sleep_ms(50);
    }

    DHT_Data data;

    while(true) {
        sensor.getData(data);
        printf("tempature: %f , humidity: %f\n", data.tempature, data.humidity);
        sleep_ms(1000);
    }
    printf("Done.\n");


    return 0;

}

void DHT20::getData(DHT_Data &data) {
    uint8_t outBuf[3]=  {0xAC, 0x33, 0x00};

    i2c_write_blocking(i2c_default,_I2CAddress ,outBuf, 3, false);

    sleep_ms(50);

    uint8_t inBuf[7];
    i2c_read_blocking(i2c_default,_I2CAddress, inBuf, 7, false);


    uint32_t humidity = inBuf[1] << 12 | inBuf[2] << 4 | (inBuf[3]&0xf0) >> 4;
    uint32_t tempature = (inBuf[3]&0xf) << 16 | inBuf[4] << 8 | inBuf[5];


    data.humidity = humidity * 9.5367431640625e-5;;
    data.tempature = tempature * 1.9073486328125e-4 - 50;


}

bool DHT20::isReady() {
    uint8_t buf[1];

    i2c_read_blocking(i2c_default, _I2CAddress, buf, 1, false);

    if(buf[0] == 0x18){


        return true;
    }
    return false;
}

void DHT20::intializeRegisters() {
    uint8_t reset1[3] = {0x1B,0x00,0x00};
    uint8_t reset2[3] = {0x1C,0x00,0x00};
    uint8_t reset3[3] = {0x1E,0x00,0x00};

    i2c_write_blocking(i2c_default, _I2CAddress, reset1,1, false);
    i2c_write_blocking(i2c_default, _I2CAddress, reset2,1, false);
    i2c_write_blocking(i2c_default, _I2CAddress, reset3,1, false);
}

