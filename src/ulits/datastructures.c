#ifndef DATASTRUCTURES
#define DATASTRUCTURES



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "./debug.c"




struct Stack{ 
    int size;
    int capasity;
    int (*list)[];
};


/*
 * makes stack
 * this should be used over making it yourself
 * size is the size and does not point at anything
 * */
struct Stack makeStack(){
    struct Stack a ;
    a.capasity=10;
    a.size=0;

    a.list = malloc(sizeof(int)*a.capasity);

    return a;
}



/*
 * pop top element of stack
 * */
int pop(struct Stack* stack){
    //if size is more than 0
    //

    if (stack->size>0){
        //what
        int ret= (*stack->list)[--stack->size];
        return ret;
    }

    printf("Stack Underflow attempring to pop from empty array\n");
    PrintStackTrace();
    exit(2);
}

/*
 * private fn increase stack capasity
 * */
void _IncreaseStackCap(struct Stack* stack){

    stack->capasity*=2;
    //save
    int (*l)[]= malloc(sizeof(int)*stack->capasity);
    //move stack.list to l
    for (int i=0; i<stack->size;i++){
        (*l)[i]=(*stack->list)[i];
    }
    free(stack->list);//?
    stack->list=l;
}




/*
 * push to stack
 * */
void push(struct Stack *stack,int value){
    //if size at cap
    if (stack->size == stack->capasity){
        //inclrease stackcap
        _IncreaseStackCap(stack);
    }
    (*stack->list)[stack->size++]=value;
}




/*
 * print stack information
 * */
void printStack(struct Stack stack){
    printf("stack size:%i, stack cap:%i \n", stack.size, stack.capasity);
    for(int i=0 ;i<stack.size;i++){
        printf("index :%i is %i \n", i, (*stack.list)[i]);
    }
}

int indexAt(struct Stack *stack,int i){
    //printf("attempting to index :%i \n",i);
    int a= (*stack->list)[i];
    //printf("retrieved :%i=%c\n",a,a);
    return a;
}

//same as index at except does not take ref takes copy
int indexAtCop(struct Stack stack,int i){
    return (*stack.list)[i];
}

void setAt(struct Stack *stack,int i,int val){
    (*stack->list)[i]=val;//does this not work?
}





/*
 * deallocate everything that the stack has allocated
 * */
void removeStack(struct Stack *stack){
    free(stack->list);
}



#endif
