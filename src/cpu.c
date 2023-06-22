#include "./ulits/datastructures.c"
#include <stdio.h>
#include <stdlib.h>
#include "./ulits/debug.c"
#include "./instructions.c"

struct Cpu{
    int ip;
    int fp;
    int sp;
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
    a.sp=-1;

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
            //this would be 
            //cpu-stack-list[++cpu->sp] = indexAt( cpu.instruuctions,cpu->ip++ )
            //cpu->stack[*] 
            //to 
            //cpu->stack->list[*]
            (*cpu->stack.list)[++cpu->sp]= (*cpu->instructions.list)[cpu->ip++];
            break;

        case PRINT_INT:
            printf("%i",(*cpu->stack.list)[cpu->sp--]);
            break;

        //pop 2 from stack->list and add
        case IADD:{
                int aa =(*cpu->stack.list)[cpu->sp--];
                int ba=(*cpu->stack.list)[cpu->sp--];
                (*cpu->stack.list)[++cpu->sp] = aa+ba;
            }
            break;

        case IMUL:{
                int am=(*cpu->stack.list)[cpu->sp--];
                int bm=(*cpu->stack.list)[cpu->sp--];
                (*cpu->stack.list)[++cpu->sp] = am*bm;
            }
            break;

        case ISUB:{
                int as=(*cpu->stack.list)[cpu->sp--];
                int bs=(*cpu->stack.list)[cpu->sp--];
                (*cpu->stack.list)[++cpu->sp] = as-bs;
            }
            break;

        case IDIV:{
                int ad=(*cpu->stack.list)[cpu->sp--];
                int bd=(*cpu->stack.list)[cpu->sp--];
                (*cpu->stack.list)[++cpu->sp] = ad/bd;
            }
            break;

        case LOAD:{
                int offset=(*cpu->instructions.list)[cpu->ip++];
                (*cpu->stack.list)[++cpu->sp]= (*cpu->stack.list)[cpu->fp+offset];
            }
            break;

        //push val on stack.list
        case SAVE:
            (*cpu->stack.list)[++cpu->sp]=(*cpu->instructions.list)[cpu->ip++];
            break;

        case REPL:{
                int roffset = (*cpu->instructions.list)[cpu->ip++];
                //stack.list at adress   is top of stack.list
                (*cpu->stack.list)[cpu->fp+roffset] = (*cpu->stack.list)[cpu->sp--];
            }
            break;


        case JUMP:
            cpu->ip=(*cpu->instructions.list)[cpu->ip];
            break;

        case JEQ:{

            int eql=(*cpu->stack.list)[cpu->sp--];
            int eqr=(*cpu->stack.list)[cpu->sp--];
            if (eql==eqr){
                cpu->ip=(*cpu->instructions.list)[cpu->ip];
            }else{
                //if we are not jumping we need to jump over the jump adress
                cpu->ip+=1;
            }
                 }
            break;

        case JLT:{

                int ltr=(*cpu->stack.list)[cpu->sp--];
                int ltl=(*cpu->stack.list)[cpu->sp--];
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
                int fnAddr=(*cpu->instructions.list)[cpu->ip++];             // next on stack is adress of the function on the cpu->instructions array (index)
                int fnArgsN=(*cpu->instructions.list)[cpu->ip++];            // next on the stack is the number of arguments that this function is called with
                (*cpu->stack.list)[++cpu->sp]=fnArgsN      ;                 // push the amount of arguments on the stack
                (*cpu->stack.list)[++cpu->sp]=cpu->fp       ;                  // push the frame pointer on the stac (so that when we exit the function we know whare we were on the stack)
                (*cpu->stack.list)[++cpu->sp]=cpu->ip        ;                 // push instruction pointer on stack (this is the return adress)
                cpu->fp=cpu->sp                            ;         // fp points to return addr on stack
                cpu->ip=fnAddr                              ;      // jump to fn addr
              }
            break;


            //return from function
        case RET:{
                int rValue= (*cpu->stack.list)[cpu->sp--];                   // every function returns what ever is on top of the stack.. all functions must return somethign
                cpu->sp = cpu->fp                      ;             // reset sp
                cpu->ip=(*cpu->stack.list)[cpu->sp--]      ;                   // top of stack is the return adress
                cpu->fp=(*cpu->stack.list)[cpu->sp--]       ;                  // top of stack is the frame pointer (to the callier function)
                cpu->sp-=(*cpu->stack.list)[cpu->sp--]       ;                 // top of stack is number of arguments .. pop it and sub it from the stack pointer (basically pop all arguments that were provided to this function)
                (*cpu->stack.list)[++cpu->sp] = rValue        ;              // leave the return value of this function on the stack
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




void runAllInstructions(struct Cpu* cpu){
    printf("running instructions. instruction size:%i   \n",cpu->instructions.size);
    while(cpu->ip<cpu->instructions.size) {
        _interpretNextCommand(cpu);
    }

}






