#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "frame_tools.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) { // make it able to cast arguments from terminal for output
    if(argc == 0) return 1;

    int file = open(argv[1], O_RDONLY);

    struct stat file_stat;

    fstat(file, &file_stat);

    uint8_t *file_data = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    close(file);

    printf("%lld\n", file_stat.st_size);
    printf("%02X\n", file_data[368188]);

    /*

    FILE *fptr;
    fptr = fopen("./output/output.csv", "w");
    if (fptr == NULL) {
        printf("Error opening file"); 
        return 1;
    }
    
    int frames = 0;
    for(int i = 0; i < file_stat.st_size - 1; i++) {
        if((file_data[i] == 0xFF) && (file_data[i+1] == 0xFB)) {
            frame_t *frame = get_frame(&file_data[i]);
            if(frame) {
                printf("%d\n", i);
                dump_frame(fptr, frame);
                free(frame);
                frames++;
            }
        }
    }

    fclose(fptr);

    printf("Total frames: %d\n", frames);

    */
    
    munmap(file_data, file_stat.st_size);
    return 0;
}