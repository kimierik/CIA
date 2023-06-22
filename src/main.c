#include "./ulits/datastructures.c"
#include <stdio.h>
#include "./instructions.c"
#include "./cpu.c"
//




int main(){ 
    //make some code give to machine and run 
    //see if workka

    
    printf("running main\n");
    int code[7]= 
    {
        ICONST,99,
        ICONST,2, 
        IADD, 
        PRINT_INT,
        HALT       
    };

    struct Cpu cpu=makeCpu();
    cpu.instructions.list=&code;

    for (int i=0;i<7;i++){
        push(&cpu.instructions,code[i]);

    }

    runAllInstructions(&cpu);
    
    

    return 0;
}

