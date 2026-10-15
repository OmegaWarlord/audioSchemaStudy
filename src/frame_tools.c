#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

uint8_t *get_raw_frame(uint8_t *data, int frame_length) { //Check this with valegrind
    uint8_t *frame_data = malloc(frame_length);
    for(int i = 0; i < frame_length; i++) {
        frame_data[i] = data[i];
    }
    return frame_data;
}

frame_t *parse_frame_header(uint32_t header) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->header = header;
    return frame;
}