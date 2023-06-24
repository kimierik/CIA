#include "./ulits/datastructures.c"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "./instructions.c"
#include "./cpu.c"
#include "compiler/lexer.c"
//




int main(){ 
    //make some code give to machine and run 
    //see if workka
    //printf("running main\n");


    struct Stack st=makeStack();

    char* filename="./examples/test.bar";

    FILE *fptr; 
    fptr=fopen(filename,"r");

    if (!fptr){
       printf("unable to open file %s: %s \n ", filename,strerror(errno));
       exit(2);
    }
    char buffer[2];
   
    while(fgets(buffer,2,fptr)){ 
        //incase we get null char
        if(buffer[0]==0){
            break;
        }
        push(&st,buffer[0]);
    }


    Lexer l =MakeLexer(st);

    VStack thing= LexString(&l);//fails here


    printf("Vstack size:%i, stack cap:%i \n", thing.size, thing.capasity);
    for(int i=0 ;i<thing.size;i++){
        printf("index :%i is %s, type: %i \n", i, ((Token*)thing.elements+i)->value, ((Token*)thing.elements+i)->type);
    }


    int code[27]={

        ARRAY,5,

        ICONST,'h',
        REPL,0,
        ICONST,'e',
        REPL,1,
        ICONST,'l',
        REPL,2,
        ICONST,'o',
        REPL,3,
        ICONST,'\n',
        REPL,4,

        PRINT_CH,
        PRINT_CH,
        PRINT_CH,
        PRINT_CH,
        PRINT_CH,


    };

    struct Cpu cpu=makeCpu();

    for (int i=0;i<27;i++){
        push(&cpu.instructions,code[i]);
    }

    runAllInstructions(&cpu,0);
    

    
    

    return 0;
}

