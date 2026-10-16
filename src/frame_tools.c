#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

frame_t *get_frame(uint8_t *data, int frame_length) {
    frame_t *frame = malloc(frame_length);
    frame->data_length = frame_length-4;
    frame->header = (uint32_t)( (data[0]<<24)|
                                (data[1]<<16)|
                                (data[2]<<8)|
                                (data[3]));
    frame->data = malloc(frame_length - 4);
    for(int i = 0; i < frame_length - 4; i++) {
        frame->data[i] = data[4 + i];
    }
    return frame;
}

void dump_frame(FILE *fptr, frame_t *frame) {
    //printf("Dumping frame: %d, %08X\n", frame->data_length, frame->header);
    fprintf(fptr, "%08X, ", frame->header);
    for(int i = 0; i < frame->data_length; i++) {
        fprintf(fptr, "%02X, ", frame->data[i]);
    }
    fprintf(fptr, "\n");
}