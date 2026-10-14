#ifndef MP3_PARSE_TOOLS_H
#define MP3_PARSE_TOOLS_H

typedef enum {
    MPEG_VERSION_2_5 = 0,
    MPEG_VERSION_RESERVED = 1,
    MPEG_VERSION_2 = 2,
    MPEG_VERSION_1 = 3
} mpeg_version_t;

typedef struct {
    uint32_t header;
    mpeg_version_t version;
} frame_t;

frame_t* parse_frame_header(uint32_t header);

#endif // MP3_PARSE_TOOLS_H