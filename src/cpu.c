#include "./ulits/datastructures.c"
#include <stdio.h>
#include <stdlib.h>
#include "./ulits/debug.c"
#include "./instructions.c"

struct Cpu{
    int ip;
    int fp;
    struct Stack stack;
    struct Stack instructions;
};

/*
 * makes cpu this should be used over making struct cpu manually
 * */
struct Cpu makeCpu(){
    struct Cpu a ;
    a.ip=0;
    a.fp=0;

    a.stack=makeStack();
    a.instructions=makeStack();


    return a;
}





/*
 * private interprets next comand
 * */
void _interpretNextCommand(struct Cpu* cpu){
    //takes next instruction and does what it is supposed to do
    int opcode= indexAt(&cpu->instructions, cpu->ip++);
    //printf("inretpreting opcode %i adress:%i \n",opcode, cpu->ip);


    //this is naively copied from 
    //https://github.com/kimierik/TSI/blob/main/src/Vm.ts
    switch (opcode) {
        
        case ICONST:
            //(*cpu->stack.list)[++cpu->sp]= (*cpu->instructions.list)[cpu->ip++];
            push(&cpu->stack,(*cpu->instructions.list)[cpu->ip++]);
            break;

        case PRINT_INT:
            printf("%i",(*cpu->stack.list)[--cpu->stack.size]);
            break;

        case PRINT_CH:
            printf("%c",(*cpu->stack.list)[--cpu->stack.size]);
            break;

        //pop 2 from stack->list and add
        case IADD:{
                int aa =(*cpu->stack.list)[--cpu->stack.size];
                int ba=(*cpu->stack.list)[--cpu->stack.size];
                (*cpu->stack.list)[cpu->stack.size++] = aa+ba;
            }
            break;

        case IMUL:{
                int am=(*cpu->stack.list)[--cpu->stack.size];
                int bm=(*cpu->stack.list)[--cpu->stack.size];
                (*cpu->stack.list)[cpu->stack.size++] = am*bm;
            }
            break;

        case ARRAY: {
                //probably does somehitng
                //allocates next x from stack
                //aka moves sp by x
                int size=(*cpu->instructions.list)[cpu->ip++];
                for (int i=0;i<size;i++){
                    push(&cpu->stack,0);
                    //(*cpu->stack.list)[++cpu->sp]= 0;
                }
            }
            break;


        case ISUB:{
                int as=(*cpu->stack.list)[--cpu->stack.size];
                int bs=(*cpu->stack.list)[--cpu->stack.size];
                (*cpu->stack.list)[cpu->stack.size++] = as-bs;
            }
            break;

        case IDIV:{
                int ad=(*cpu->stack.list)[--cpu->stack.size];
                int bd=(*cpu->stack.list)[--cpu->stack.size];
                (*cpu->stack.list)[cpu->stack.size++] = ad/bd;
            }
            break;

        case LOAD:{
                int offset=(*cpu->instructions.list)[cpu->ip++];
                (*cpu->stack.list)[cpu->stack.size++]= (*cpu->stack.list)[cpu->fp+offset];
            }
            break;

        //push val on stack.list
        case SAVE:
            (*cpu->stack.list)[cpu->stack.size++]=(*cpu->instructions.list)[cpu->ip++];
            break;

        case REPL:{//replaces element at next instructions adress with top of stack
                int roffset = (*cpu->instructions.list)[cpu->ip++];
                //stack.list at adress   is top of stack.list
                //(*cpu->stack.list)[cpu->fp+roffset] = (*cpu->stack.list)[cpu->sp--];
                //this does not set but otherwize works
                int a=(*cpu->stack.list)[--cpu->stack.size];
                //printf(" debug %i",a);
                setAt(&cpu->stack,cpu->fp+roffset,a);
                //(*cpu->stack.list)[cpu->fp+roffset] = (*cpu->stack.list)[cpu->stack.size--];
            }
            break;


        case JUMP:
            cpu->ip=(*cpu->instructions.list)[cpu->ip];
            break;

        case JEQ:{

            int eql=(*cpu->stack.list)[--cpu->stack.size];
            int eqr=(*cpu->stack.list)[--cpu->stack.size];
            if (eql==eqr){
                cpu->ip=(*cpu->instructions.list)[cpu->ip];
            }else{
                //if we are not jumping we need to jump over the jump adress
                cpu->ip+=1;
            }
                 }
            break;

        case JLT:{

                int ltr=(*cpu->stack.list)[--cpu->stack.size];
                int ltl=(*cpu->stack.list)[--cpu->stack.size];
                if (ltl<ltr){
                    cpu->ip=(*cpu->instructions.list)[cpu->ip];
                }else{
                    //if we are not jumping we need to jump over the jump adress
                    cpu->ip+=1;
                }
            }
            break;


        case CALL:{
                //all arguments should allready be on the stack
                int fnAddr=(*cpu->instructions.list)[cpu->ip++];            // next on stack is adress of the function on the cpu->instructions array (index)
                int fnArgsN=(*cpu->instructions.list)[cpu->ip++];           // next on the stack is the number of arguments that this function is called with
                (*cpu->stack.list)[cpu->stack.size++]=fnArgsN;                      // push the amount of arguments on the stack
                (*cpu->stack.list)[cpu->stack.size++]=cpu->fp;                      // push the frame pointer on the stac (so that when we exit the function we know whare we were on the stack)
                (*cpu->stack.list)[cpu->stack.size++]=cpu->ip;                      // push instruction pointer on stack (this is the return adress)
                cpu->fp=cpu->stack.size; //might be wrong stack size is not direct eq to sp                                           // fp points to return addr on stack
                cpu->ip=fnAddr;                                             // jump to fn addr
              }
            break;


            //return from function
        case RET:{
                     //NOTE stack.size might be incorrect here. direct copy from ts and sp in ts is different from stack.size
                int rValue= (*cpu->stack.list)[--cpu->stack.size];                      // every function returns what ever is on top of the stack.. all functions must return somethign
                cpu->stack.size = cpu->fp;                                              // reset sp
                cpu->ip=(*cpu->stack.list)[--cpu->stack.size];                          // top of stack is the return adress
                cpu->fp=(*cpu->stack.list)[--cpu->stack.size];                          // top of stack is the frame pointer (to the callier function)
                int spoffset=(*cpu->stack.list)[--cpu->stack.size];                     // top of stack is number of arguments .. pop it and sub it from the stack pointer (basically pop all arguments that were provided to this function)
                cpu->stack.size -= spoffset;
                (*cpu->stack.list)[cpu->stack.size++] = rValue;                         // leave the return value of this function on the stack
            }
            break;

        case HALT:
            return;
        
        default:
            printf("cannot inrerpret opcode :%i\n",opcode);
            PrintStackTrace();
            exit(2);
    }




}




void runAllInstructions(struct Cpu* cpu, int debug){
    printf("running instructions. instruction size:%i   \n",cpu->instructions.size);
    while(cpu->ip<cpu->instructions.size) {

        if (debug){

        struct _thing a=_getInstrucitoninfo( indexAt(&cpu->instructions, cpu->ip));
            switch (a.nops) {
                case 0:
                   printf("%s ",a.name);
                   break;
                case 1:
                   printf("%s %i ",a.name, indexAt(&cpu->instructions, cpu->ip));
                   break;

                case 2:
                   printf("%s %i %i ",a.name, indexAt(&cpu->instructions, cpu->ip),indexAt(&cpu->instructions, cpu->ip+1));
                   break;
           } 
        }

        //interpret the code itsetl
        _interpretNextCommand(cpu);

        if (debug){
            printf("[ ");
            for (int i=0;i<cpu->stack.size;i++){
                printf("%i ", indexAt(&cpu->stack, i));
            }

            printf("]\n");
        }

    }

}






