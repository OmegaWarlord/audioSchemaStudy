#ifndef FRAME_TOOLS_H
#define FRAME_TOOLS_H

#include<stdio.h>

//Maybe create enums later

typedef struct {
    int data_length;
    uint32_t header;
    uint8_t *data;
} frame_t;

int find_frameLength(uint32_t header);

int bitrate(int index);

int samplerate(int index);

frame_t *get_frame(uint8_t *data, int frame_length);

void dump_frame(FILE *fptr, frame_t *frame);

#endif // FRAME_TOOLS_H