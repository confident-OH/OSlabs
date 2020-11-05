#include "main.h"

int main(int args, char** argv)
{
    if(args<2){
        printf("Command Error!\n");
    }
    if(args == 2){
        print_dir(argv[1]);
    }
    if(args == 3){
        if(!(strcmp("-lR", argv[1]))){
            print_dir(argv[2]);
        }else{
            printf("Command Error!\n");
        }
    }
    return 0;
}