#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

frame_t* parse_frame_header(uint32_t header) {
    frame_t* frame = malloc(sizeof(frame_t));
    frame->header = header;
    frame->version = (header >> 19) & 0x3;
    frame->layer = (header >> 17) & 0x3;
    frame->protection_bit = (header >> 16) & 0x1;
    frame->bitrate_index = (header >> 12) & 0xF;
    frame->sampling_rate_index = (header >> 10) & 0x3;
    frame->padding_bit = (header >> 9) & 0x1;
    frame->private_bit = (header >> 8) & 0x1;
    frame->channel_mode = (header >> 6) & 0x3;
    frame->mode_extension = (header >> 4) & 0x3;
    frame->copyright = (header >> 3) & 0x1;
    frame->original = (header >> 2) & 0x1;
    frame->emphasis = header & 0x3;
    frame->frame_length = 0; 
    return frame;
}