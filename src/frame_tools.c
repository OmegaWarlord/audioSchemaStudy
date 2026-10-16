#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

const int bitrates[] = {0, 32000, 40000, 48000, 56000, 64000, 80000, 96000, 112000, 128000, 160000, 192000, 224000, 256000, 320000, 0};
const int samplerates[] = {44100, 48000, 32000, 0};

int find_frameLength(uint32_t header) { //Calculating Frame Length

    //Finding Indexs for bitrate & samplerate
    int br_index = (int)((header >> 12) & 0xF);
    int sr_index = (int)((header >> 10) & 0x3);

    //Bitrate, samplerate, & padding ready to use
    int br = bitrates[br_index];
    int sr = samplerates[sr_index]; 
    int p = (int)((header >> 9) & 0x1);

    //Final calculation
    int length = (144*br)/sr+p;

    return length;
}

frame_t *get_frame(const uint8_t *data) {
    if(!data) return NULL;
    
    //Frame decleration
    frame_t *frame = malloc(sizeof(frame_t));
    if(!frame) return NULL;

    //Set Header
    frame->header = (uint32_t)( (data[0]<<24) | (data[1]<<16) | (data[2]<<8) | (data[3]));

    //Find & Set frame Length
    int frame_length = find_frameLength(frame->header);
    if(frame_length == 0) return NULL;
    frame->data_length = (frame_length - 4);

    //Copy frame data to object
    frame->data = malloc(frame->data_length);
    if(!frame->data) return NULL;
    memcpy(frame->data, &data[4], frame->data_length);

    return frame;
}

void dump_frame(FILE *fptr, frame_t *frame) { //Dumps frame into CSV
    fprintf(fptr, "%08X, ", frame->header);
    for(int i = 0; i < frame->data_length; i++) {
        fprintf(fptr, "%02X, ", frame->data[i]);
    }
    fprintf(fptr, "\n");
}