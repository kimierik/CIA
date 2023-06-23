#include "./ulits/datastructures.c"
#include <stdio.h>
#include "./instructions.c"
#include "./cpu.c"
#include "compiler/lexer.c"
//




int main(){ 
    //make some code give to machine and run 
    //see if workka
    printf("running main\n");

    /*
    int code[7]= 
    {
        ICONST,99,
        ICONST,2, 
        IADD, 
        PRINT_INT,
        HALT       
    };
     * */
    //something that uses array thing. idkman
    //there sp should be at 5

    struct Stack st=makeStack();
    push(&st,'a');
    push(&st,'s');
    push(&st,'d');
    push(&st,'f');
    push(&st,'(');
    push(&st,')');


    Lexer l =MakeLexer(st);

    VStack thing= LexString(&l);//fails here


    printf("Vstack size:%i, stack cap:%i \n", thing.size, thing.capasity);
    for(int i=0 ;i<thing.size;i++){
        printf("index :%i is %s \n", i, ((Token*)thing.elements+i)->value );//shit
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

