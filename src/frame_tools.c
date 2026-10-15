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

frame_t *parse_frame_header(uint8_t *raw) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->header = (uint32_t)(raw[0]|raw[1]|raw[2]|raw[3]);
    frame->data = (&raw[4]);
    return frame;
}