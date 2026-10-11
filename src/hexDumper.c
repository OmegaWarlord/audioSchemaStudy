#include <stdio.h>

extern int add_numbers(int a, int b);
extern char dump_reg(char* temp);

int main(int argc, char *argv[]) {
    printf("%d\n", argc);
    if(argc > 1){
        printf("%s\n", argv[1]);
    }
    printf("Result of adding 5 and 10: %d\n", add_numbers(5, 10));
    printf("Result of dump_reg: %c\n", dump_reg("se"));
    return 0;
    //fdsahfja
}