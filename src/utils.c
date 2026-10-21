#include "utils.h"

//Easier way to extract bits from byte arrays
unsigned get_bits(unsigned char *data, int sbit, int count) {

    //Finding the ending bit
    int ebit = sbit + count;

    int sbyt = sbit >> 3;
    int ebyt = ebit >> 3;

    sbit %= 8;
    ebit %= 8;

    unsigned result = ((unsigned)data[sbyt] << (32 - (8 - sbit))) >> (32 - (8 - sbit));

    if(sbyt != ebyt) {
        while(++sbyt != ebyt) {
            result <<= 8;
            result += data[sbyt];
        }
        result <<= ebit;
        result += data[ebyt] >> (8-ebit);
    } else if (ebit != 8) {
        result >>= (8-ebit);
    }

    return result;
}

/*
unsigned get_bits_next(unsigned char *data, int *count, int amount) {
    unsigned result = get_bits(&data[0], *count, *count+amount);
    *count += amount;
    return result;
} 
*/

int sign(int val) {
    return (val > 0) - (val < 0);
}