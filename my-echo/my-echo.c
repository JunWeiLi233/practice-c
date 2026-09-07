#include <stdio.h>
#include <string.h>

const char* nlopt = "-n";

int main(int argc, const char* argv[]){
    if(argc < 2 )
    {
        printf("\n");
        return 0;
    }

    int enable_newline = strcmp(argv[1], nlopt);

    for(int i=enable_newline?1:2;i<argc;i++){
        printf("%s", argv[i]);
        if(i != argc-1){
            printf(" ");
        }
    }
    if(enable_newline){
        printf("\n");
    }
}