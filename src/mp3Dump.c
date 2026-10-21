#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"
#include "frame_tools.h"
#include "mp3_tools.h"


int main(int argc, char *argv[]) {
    if(argc == 0) return 1;

    int file = open(argv[1], O_RDONLY);

    struct stat file_stat;
    fstat(file, &file_stat);

    unsigned char *file_data = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    FILE *fptr = fopen("./output/output.csv", "w");
    if(fptr == NULL) return 1;

    for(int i = 0; i < file_stat.st_size; i++) {
        struct Frame *frame = create_frame(file_data, i);
        if(frame != NULL) {;
            unsigned short data_start = get_bits(&file_data[i+4], 0, 9);

            fprintf(fptr, "%d, %d, %08X, %d\n", i, frame->frame_size, frame->header, data_start);
            printf("Valid\n");
        } else {
            free(frame);
        }
    }

    //Close files
    fclose(fptr);
    close(file);
    munmap(file_data, file_stat.st_size);

    return 0;
}