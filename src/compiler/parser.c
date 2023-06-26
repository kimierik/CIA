#ifndef PARSER_C
#define  PARSER_C

#include "../ulits/VoidStack.c"
#include "parser.h"
#include <stdlib.h>




Parser _MakeParser(VStack tokens){
    Parser parser;
    parser.tokens=tokens;
    parser.position=0;
    return parser;
}


/*
 * takes list of tokens returns list of functoin declerations
 * */
VStack ParseFunctionDeclerations(VStack tokens){
    Parser parser=_MakeParser(tokens);
    VStack Decls= makeVStack(sizeof(FunctionDeclNode*));

    while(parser.position<parser.tokens.size){
        FunctionDeclNode* d=_ParseFunctionDecleration(&parser);
        //adress of d is a pointer to stack but that does not matter since we are copyng the value of it in vpush so we get the pointer to d not the adress
        Vpush(&Decls, &d);
    }


    return Decls;
}




//what the fuck does this take
//do we have a struct with all needed things that we pass around again
FunctionDeclNode* _ParseFunctionDecleration(Parser* parser){
    FunctionDeclNode* decl=malloc(sizeof(FunctionDeclNode));
    //return type, name,


    return decl;
}





#endif 
