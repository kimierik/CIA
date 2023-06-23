#ifndef VOIDTEST
#define VOIDTEST
#include "../ulits/VoidStack.c"


void TestVoidStack(){
    VStack a = makeVStack(sizeof(int));

    int aa=1;
    int ab=23;
    int ac=5;

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);

    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);
    push(&a,&aa);
    push(&a,&ab);
    push(&a,&ac);


    //hmmmmm
    int * asdf=  pop(&a);

    printStack(a);

    //does not get value?
    printf("popped %i\n", * asdf);

    destroyStack(&a);

}


#endif
