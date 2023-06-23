#ifndef VOIDSTACK
#define VOIDSTACK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./debug.c"

typedef struct VStack{
    void* elements;
    int size;
    int elemSize;
    int capasity;

}VStack;

VStack makeVStack(int elemsize){
    VStack a;
    a.capasity=10;
    a.size=0;
    a.elemSize=elemsize;
    a.elements= malloc(elemsize*a.capasity);

    return a;
}



void * Vpop(VStack *stack){

    if (stack->size>0){
        //what
        void* ret= stack->elements + --stack->size *stack->elemSize; //?
        return ret;
    }

    printf("Stack Underflow attempring to pop from empty array\n");
    PrintStackTrace();
    exit(2);
}




void _IncreaseVStackCap(struct VStack* stack){

    stack->capasity*=2;
    //save
    void *l= malloc(stack->elemSize * stack->capasity);
    //move stack.list to l
    for (int i=0; i<stack->size;i++){
        //(*l)[i]=(*stack->list)[i];
        void * pos=stack->elements + i * stack->elemSize;
        memcpy( l + i * stack->elemSize, pos,  stack->elemSize );
    }
    free(stack->elements);//?
    stack->elements=l;
}



void Vpush(VStack* stack, void*elem){

    if (stack->size == stack->capasity){
        //inclrease stackcap
        _IncreaseVStackCap(stack);
    }

    //(*stack->list)[stack->size++]=value;
    //this is an adress not what i want
    
    //printf("adding elem %i\n", *(int*)elem );
    //printf("adress of elem %d\n", elem );

    //copy elem to elements + pos*elemsize
    //this is pointer to element not pointer to pointer of elem
    memcpy(stack->elements + stack->size++ *stack->elemSize, elem, stack->elemSize);
}



void destroyVStack(VStack *stack){
    //this probably needs to free all enements not just the one
    free(stack->elements);
}


/*
 * print stack information
 * */
void printVStack(struct VStack stack){
    printf("Vstack size:%i, stack cap:%i \n", stack.size, stack.capasity);
    for(int i=0 ;i<stack.size;i++){
        printf("index :%i is %i \n", i, *((int*)stack.elements+i) );//shit
    }
}






#endif
