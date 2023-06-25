#ifndef VOIDTEST
#define VOIDTEST
#include "../ulits/VoidStack.c"
#include "../compiler/lexer.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void TestVoidStack(){
    VStack a = makeVStack(sizeof(int));

    int aa=1;
    int ab=23;
    int ac=5;


   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);

   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);
   Vpush(&a,&aa);
   Vpush(&a,&ab);
   Vpush(&a,&ac);


    //hmmmmm
    int * asdf=  Vpop(&a);

    printVStack(a);

    //does not get value?
    printf("popped %i\n", * asdf);

    destroyVStack(&a);


    VStack b = makeVStack(sizeof(Token*)); //why the fuck do you not work if you are token*
                                          //when we only put token poinnters into the list

    //token a pointer = tap
    
    //need to have allocated strings for clenaing funtion to work
    char* tap=malloc(sizeof(char)*5);
    char* tas="adsf";
    memcpy(tap,tas,sizeof(char)*5);

    //printf("made string %s at %p\n", tas,tap);


    Token *ta=makeToken(Identifier,tap);
    //Token *tb=makeToken(Comma,"adsf1233");
    //Token *tc=makeToken(Identifier,tas);
    Vpush(&b, &ta);
    //Vpush(&b, &tb);
    //Vpush(&b, &tc);

    /*
    printf("Vstack size:%i, stack cap:%i \n", b.size, b.capasity);
    for(int i=0 ;i<b.size;i++){
        //what the fuck is this not a token
        
        Token* tok=((Token*)b.elements+i);
        printf("troken %p \n",tok);

        printf("index :%i is %s, type: %s \n", i, tok->value, stringifyToken( tok->type));
    }
     * */

    destroyPointerVstack(&b,&CleanToken);








}


#endif
