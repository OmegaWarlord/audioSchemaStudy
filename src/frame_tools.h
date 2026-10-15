#ifndef FRAME_TOOLS_H
#define FRAME_TOOLS_H

//Maybe create enums later

typedef struct {
    uint32_t header;
    uint8_t *data;
} frame_t;

uint8_t *get_raw_frame(uint8_t *data, int frame_len);

frame_t *parse_frame_header(uint8_t *header);

#endif // FRAME_TOOLS_H