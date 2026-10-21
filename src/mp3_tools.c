#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mp3_tools.h"
#include "utils.h"

const int brs[] = {0, 320, 400, 480, 560, 640, 800, 960, 1120, 1280, 1600, 1920, 2240, 2560, 3200, 0};
const int srs[] = {441, 480, 320, 0};

const unsigned char slen1[] = {0,0,0,0,3,1,1,1,2,2,2,3,3,3,4,4};
const unsigned char slen2[] = {0,1,2,3,0,1,2,3,1,2,3,1,2,3,2,3};

unsigned find_frameLen(unsigned char *data, int index) {
    if(!data) return 0;

    //Checks to see if Frame Header starts with 0xFFFB
    if(get_bits(&data[index], 0, 16) != 0xFFFB) return 0;

    //Bitrate, samplerate, & padding ready to use
    int br = brs[get_bits(&data[index], 16, 4)];
    int sr = srs[get_bits(&data[index], 20, 2)]; 
    int p = get_bits(&data[index], 22, 1);

    //Null Check
    if((br == 0) || (sr == 0)) return 0;

    //Final calculation
    return (144*br)/sr+p;
}

void side_test(unsigned char *data) {

    //Shortcut for get_bits
    unsigned char *d = &data[0];
    
    //Extracting info
    unsigned short mdb = get_bits(d, 0, 9);
    unsigned char sf0 = get_bits(d, 12, 4);
    unsigned char sf1 = get_bits(d, 16, 4);
    unsigned short p23 = get_bits(d, 20, 12);
    unsigned short bv = (data[4]<<1|data[5]>>7)&0x01FF;
    unsigned char gg = (data[5]<<1|data[6]>>7);
    unsigned char sfc = (data[6]>>3)&0x04;



    unsigned char ws = (data[6]>>2)&0x01;

    // 20+ 59 + 59 + 59 + 59
    printf("%X, %X, %X, %d, %X, %X, %X, %X\n", mdb, sf0, sf1, p23, bv, gg, sfc, ws);
}