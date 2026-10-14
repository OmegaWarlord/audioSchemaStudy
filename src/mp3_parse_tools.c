#include <stdint.h>
#include <stdlib.h>
#include "mp3_parse_tools.h"

frame_t* parse_frame_header(uint32_t header) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->header = header;
    return frame;
}