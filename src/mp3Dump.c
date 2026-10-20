#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

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
        unsigned frame_length = find_frameLen(file_data, i);
        if(frame_length != 0) {

            unsigned file_header = (file_data[i] <<24 | file_data[i+1] <<16 | file_data[i+2] <<8 | file_data[i+3]);
            unsigned short data_start = (file_data[i+4] <<1 | file_data[i+5] >>7);

            fprintf(fptr, "%d, %d, %08X, %d\n", i, frame_length, file_header, data_start);

            side_test(&file_data[i+4]);
        }
    }

    //Close files
    fclose(fptr);
    close(file);
    munmap(file_data, file_stat.st_size);

    return 0;
}