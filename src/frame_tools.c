#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

int find_frameLength(uint32_t header) {
    //Calculating Frame Length

    int length = 0;

    //uint8_t br_index = ((frame->header >> 12) & 0x03);
    //uint8_t sr_index = ((frame->header >> 10) & 0x02);
    int p = (int)((header >> 9) & 0x01);

    int br = 0, sr = 0;

    printf("hello\n");
    
    

    printf("%d, %d, %d, %d\n", br, sr, p, length);

    return length;
}

frame_t *get_frame(uint8_t *data, int frame_length) {
    
    frame_t *frame = malloc(frame_length);

    frame->header = (uint32_t)( (data[0]<<24) | (data[1]<<16) | (data[2]<<8) | (data[3]));
    find_frameLength(frame->header);
    frame->data_length = frame_length-4;
    frame->data = malloc(frame_length - 4);

    for(int i = 0; i < frame_length - 4; i++) {
        frame->data[i] = data[4 + i];
    }

    return frame;
}

void dump_frame(FILE *fptr, frame_t *frame) { //Dumps frame into CSV
    fprintf(fptr, "%08X, ", frame->header);
    for(int i = 0; i < frame->data_length; i++) {
        fprintf(fptr, "%02X, ", frame->data[i]);
    }
    fprintf(fptr, "\n");
}