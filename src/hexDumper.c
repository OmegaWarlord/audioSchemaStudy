#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main() {

    int file = open("./MP3Examples/korok.mp3", O_RDONLY);

    int frames = 0;

    struct stat file_stat;

    fstat(file, &file_stat);

    uint8_t *file_data = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    close(file);

    for(int i = 0; i < file_stat.st_size - 1; i++) {
        if((file_data[i] == 0xFF) && ((file_data[i+1] >> 1) == 0x7D)) {
            uint8_t *frame_raw = get_raw_frame(&file_data[i], 626); //still seperate so it can be freed
            frame_t *frame = parse_frame_raw(frame_raw);
            printf("%08X %02X\n", frame->header, frame->data[0]);
            free(frame);
            frames++;
        }
    }

    printf("Total frames: %d\n", frames);
    
    munmap(file_data, file_stat.st_size);
    return 0;
}