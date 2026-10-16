#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "mp3_tools.h"

const int brs[] = {0, 320, 400, 480, 560, 640, 800, 960, 1120, 1280, 1600, 1920, 2240, 2560, 3200, 0};
const int srs[] = {441, 480, 320, 0};

int validate_frame(uint8_t *data, int index) {
    if(!data) return 0;

    //Checks to see if Frame Header starts with 0xFFFB
    if(!((data[index] == 0xFF) && (data[index + 1] == 0xFB))) return 0;

    int br_index = (int)((data[index + 2] >> 4) & 0xF);
    int sr_index = (int)((data[index + 2] >> 2) & 0x3);

    //Bitrate, samplerate, & padding ready to use
    int br = brs[br_index];
    int sr = srs[sr_index]; 
    int p = (int)((data[index + 2] >> 1) & 0x1);

    //Null Check
    if((br == 0) || (sr == 0)) return 0;

    //Final calculation
    return (144*br)/sr+p;
}