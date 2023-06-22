#ifndef INSTUCTIONS
#define INSTUCTIONS

#include <stdio.h>
#include <stdlib.h>
#include "./ulits/debug.c"

enum{


    PRINT_CH,
    PRINT_INT,

    CHCONST,
    ICONST,

    ARRAY,

    HALT,
    JUMP,

    LOAD,
    SAVE,
    REPL,

    JLT,
    JEQ,

    IADD,
    IMUL,
    ISUB,
    IDIV,

    CALL,
    RET,

};


struct _thing{
    char* name;
    int nops;
};


struct _thing _getInstrucitoninfo(int opcode){

    switch (opcode) {
        case PRINT_CH:{
                struct _thing a;;
                a.name="PRINT_CH";
                a.nops=0;
                return a;
            }


        case PRINT_INT: {
                struct _thing a;;
                a.name="PRINT_INT";
                a.nops=0;
                return a;
            }

        case ARRAY:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }


        case CHCONST:{
                struct _thing a;;
                a.name="CHCONST";
                a.nops=1;
                return a;
            }


        case ICONST:{
                struct _thing a;;
                a.name="ICONST";
                a.nops=1;
                return a;
            }

        case HALT:{
                struct _thing a;;
                a.name="HALT";
                a.nops=0;
                return a;
            }

        case JUMP:{
                struct _thing a;;
                a.name="JUMP";
                a.nops=1;
                return a;
            }

        case LOAD:{
                struct _thing a;;
                a.name="LOAD";
                a.nops=1;
                return a;
            }

        case SAVE:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }

        case REPL:{
                struct _thing a;;
                a.name="REPL";
                a.nops=1;
                return a;
            }

        case JLT:{
                struct _thing a;;
                a.name="JLT";
                a.nops=1;
                return a;
            }

        case JEQ:{
                struct _thing a;;
                a.name="JEQ";
                a.nops=1;
                return a;
            }

        case IADD:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }

        case IMUL:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }

        case ISUB:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }

            break;
        case IDIV:{
                struct _thing a;;
                a.name="ARRAY";
                a.nops=1;
                return a;
            }

        case CALL:{
                struct _thing a;;
                a.name="call";
                a.nops=2;
                return a;
            }

        case RET:{
                struct _thing a;;
                a.name="ret";
                a.nops=1;
                return a;
            }
        default:{
                printf("cannot make internal struct for debugging %i\n",opcode);
                PrintStackTrace();
                exit(2);
            }
    }

    printf("switch case fucked%i\n",opcode);
    PrintStackTrace();
    exit(2);

}


void printInstruction(int instructions[], int adress){
    int opcode= instructions[adress];

    switch (opcode) {
        case PRINT_CH:
            break;
        case PRINT_INT:
            break;
        case ARRAY:
            break;
        case CHCONST:
            break;
        case ICONST:
            break;
        case HALT:
            break;
        case JUMP:
            break;
        case LOAD:
            break;
        case SAVE:
            break;
        case REPL:
            break;
        case JLT:
            break;
        case JEQ:
            break;
        case IADD:
            break;
        case IMUL:
            break;
        case ISUB:
            break;
        case IDIV:
            break;
        case CALL:
            break;
        case RET:
            break;
    }

}




#endif
