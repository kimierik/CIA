#ifndef PARSER_H
#define PARSER_H
#include "../ulits/macros.h"
#include "../ulits/VoidStack.c"


/*
 * goe: Greater or eq
 * GT: greater than
 * LT: less than
 * LOE: less or eq
 * */
typedef enum Opps{
    Add,
    Sub,
    Div,
    Mul,

    Eq,
    GT,
    GOE,
    LT,
    LOE,
}Opps;



typedef struct Statement{
    char* Id;
    void* statement;
}Statement;

typedef struct Expr{
    char* Id;
    void* expression;
}Expr;


typedef struct IliteralNode{
    int value;
}IliteralNode;

typedef struct StringLiteralNode{
    char* value;
    u8 valLen;
}StringLiteralNode;

typedef struct CustomTypeNode{
    char* name;
    u8* nameLen;
}CustomTypeNode;


/*
 * Body: Pointer to Vstack of Statement**
 * name and name's string len if needed
 * params: Pointer to Vstack of Expr**
 * */
typedef struct FunctionDeclNode{
    VStack* Body; 
    char*retValName;
    u8 retVnamelen;

    char* name;
    u8 namelen;

    VStack* params;

}FunctionDeclNode;


/*
 * arguments: Pointer to Vstack of Expr**
 * name and name len if needed
 * */
typedef struct FunctionCallNode{
    char* name;
    u8 nameLen;
    VStack* arguments;

}FunctionCallNode;


typedef struct VariableRefrenceNode{
    char* name;
    u8 nameLen;
}VariableRefrenceNode;

/*
 * name and name len
 * nth is how manyeth variable this is assigned in the function
 *  so first variable to be assigned will be 0 and the second 1
 * */
typedef struct VariableDeclNode{
    char* name;
    u8 nameLen;

    u8 nth;
}VariableDeclNode;


typedef struct VariableAssigmentNode{
    char* name;
    u8 nameLen;

    Expr* value;
}VariableAssigmentNode;


typedef struct OpNode{
    Expr* l;
    Expr* r;
    Opps opp;
}OpNode;




typedef struct Parser{
    VStack tokens;
    int position;
}Parser;


/* -------------------------------------------------- FUNCTIONS -------------------------------------------------- */ 

FunctionDeclNode* _ParseFunctionDecleration(Parser* parser);
FunctionCallNode* _ParseFunctionCall(Parser* parser);

// to parse expression inside ()
VStack* _ParseExpressions(Parser* parser);


#endif
