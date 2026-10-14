#include <stdio.h>
#include <stdint.h>
#include "mp3_parse_tools.h"

int main() {

    FILE *data_stream = fopen("./MP3Examples/proofofhero.mp3", "rb");

    if(data_stream == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    uint8_t buffer[4];
    int frames = 0;
    //int valid_frames = 0;
    while(fread(buffer, sizeof(uint8_t), 2, data_stream) > 0) {
        if((buffer[0] == 0xFF) && ((buffer[1] & 0xE0) == 0xE0)) {
            frames++;
            printf("%02X %02X %02X %02X\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        } 
    }

    printf("Total frames: %d", frames);

    fclose(data_stream);

    return 0;
}