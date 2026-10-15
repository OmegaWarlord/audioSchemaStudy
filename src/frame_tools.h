#ifndef FRAME_TOOLS_H
#define FRAME_TOOLS_H

//Maybe create enums later

typedef struct {
    uint32_t header;
    uint8_t version :2;
    uint8_t layer :2;
    uint8_t protection_bit :1;
    uint8_t bitrate_index :4;
    uint8_t sampling_rate_index :2;
    uint8_t padding_bit :1;
    uint8_t private_bit :1;
    uint8_t channel_mode :2;
    uint8_t mode_extension :2;
    uint8_t copyright :1;
    uint8_t original :1;
    uint8_t emphasis :2;
    unsigned short frame_length;
} frame_t;

frame_t* parse_frame_header(uint32_t header);

unsigned short get_frame_length(frame_t* frame);

void print_frame(frame_t* frame);

#endif // MP3_PARSE_TOOLS_H