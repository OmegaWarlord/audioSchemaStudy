#include <stdio.h>

extern int add_numbers(int a, int b);
extern int dump_reg(int temp, int string_length);

int main(int argc, char *argv[]) {
    printf("%d\n", argc);
    if(argc > 1){
        printf("%s\n", argv[1]);
    }
    printf("Result of adding 5 and 10: %d\n", add_numbers(5, 10));
    printf("Result of dump_reg: %d\n", dump_reg(0, 10));
    return 0;
}