#include "./ulits/datastructures.c"
#include <stdio.h>
#include "./instructions.c"
#include "./cpu.c"
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

