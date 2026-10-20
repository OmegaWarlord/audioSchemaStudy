#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mp3_tools.h"

const int brs[] = {0, 320, 400, 480, 560, 640, 800, 960, 1120, 1280, 1600, 1920, 2240, 2560, 3200, 0};
const int srs[] = {441, 480, 320, 0};

unsigned find_frameLen(unsigned char *data, int index) {
    if(!data) return 0;

    //Checks to see if Frame Header starts with 0xFFFB
    if(!((data[index] == 0xFF) && (data[index + 1] == 0xFB))) return 0;

    //Bitrate, samplerate, & padding ready to use
    int br = brs[(data[index + 2] >> 4) & 0xF];
    int sr = srs[(data[index + 2] >> 2) & 0x3]; 
    int p = (int)((data[index + 2] >> 1) & 0x1);

    //Null Check
    if((br == 0) || (sr == 0)) return 0;

    //Final calculation
    return (144*br)/sr+p;
}

void side_test(unsigned char *data) {
    
    //Extracting info
    unsigned short main_data_begins = (data[0] <<1 | data[0] >>7);

    //printing it
    printf("Main Data Begins: %d\n", main_data_begins);
    printf("");
}