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
    if(!sensor.isReady()){
        printf("sensor is not ready waiting 50ms");
        sleep_ms(50);
    }

    DHT_Data data;

    while(true) {
        sensor.getData(data);
        printf("tempature: %f , humidity: %f", data.tempature, data.humidity);
        sleep_ms(1000);
    }
    printf("Done.\n");


    return 0;

}

void DHT20::getData(DHT_Data &data) {
    printf("in get data\n");
    uint8_t outBuf[2];
    outBuf[0] = 0x33;
    outBuf[1] = 0x00;

    printf("requesting data\n");
    i2c_write_blocking(i2c_default,0xAC ,outBuf, 2, false);
    sleep_ms(50);

    uint8_t inBuf[7];
    printf("sent message, reading data\n");
    i2c_read_raw_blocking(i2c_default,inBuf, 7);
    printf("received data\n");


    float humidity = inBuf[1] << 12 | inBuf[2] << 4 | inBuf[3] >> 4;
    float tempature = (inBuf[3] << 16 | inBuf[4] << 8 | inBuf[5]) &  0xffff;
    humidity = (humidity / pow(2, 20)) * 100;
    tempature = ((tempature / pow(2,20)) * 200) - 50;

    data.humidity = humidity;
    data.tempature = tempature;


}

bool DHT20::isReady() {
    uint8_t buf[1];
    buf[0] = 0x71;

    i2c_write_raw_blocking(i2c_default, buf, 1);
    i2c_read_raw_blocking(i2c_default, buf, 1);

    if(buf[0] == 0x18){
        return true;
    }
    else{
        printf("DHT20 is NOT ready\n");
        return false;
    }
}

void DHT20::intializeRegisters() {
    printf("resetting registers\n");
    uint8_t buf[1];
    buf[0] = 0;
    printf("sending reset to 0x1b\n");

    i2c_write_blocking(i2c_default, 0x1B, buf,1, false);
    printf("sending reset to 0x1c\n");
    i2c_write_blocking(i2c_default, 0x1c, buf,1, false);
    printf("sending reset to 0x1e\n");
    i2c_write_blocking(i2c_default, 0x1e, buf,1, false);
    printf("finshed resetting");
}

