#include <stdio.h>
#include <stdint.h>

extern int add_numbers(int a, int b);
extern char dump_reg(char* temp);

int main() {

    FILE *data_stream = fopen("./MP3Examples/korok.mp3", "rb");

    if(data_stream == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    uint8_t byte[30];

    fread(byte, sizeof(uint8_t), 30, data_stream);

    

    for(int i = 0; i < 30; i++) {
        printf("%02X " , byte[i]);
    }

    fclose(data_stream);

    return 0;
}