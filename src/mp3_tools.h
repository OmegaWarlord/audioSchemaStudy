#ifndef MP3_TOOLS_H
#define MP3_TOOLS_H

#include <stdio.h>

//Sample & Bit rates
extern const int brs[];
extern const int srs[];

//Checks and sees if frame is valid and returns size
int validate_frame(uint8_t *data, int index);

#endif