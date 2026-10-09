#include <stdio.h>

extern int add_numbers(int a, int b);
extern char dump_reg(char *dump_string, int string_length);

int main(int argc, char *argv[]) {
    printf("%d\n", argc);
    if(argc > 1){
        printf("%s\n", argv[1]);
    }
    printf("Result of adding 5 and 10: %d\n", add_numbers(5, 10));
    printf("%c\n",dump_reg("Hello, World!", 13));
    return 0;
}