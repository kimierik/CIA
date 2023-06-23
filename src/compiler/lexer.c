#ifndef LEXER_C
#define LEXER_C

//#include "../ulits/datastructures.c"
#include "./lexer.h"
#include "stdio.h"
#include "stdlib.h"

#include "../ulits/debug.c"
#include "../ulits/VoidStack.c"





//decls
Token* makeToken(TokenType type, char* val);
//TOken L has copy of char not pointer to single char on lexer stack
Token* makeTokenL(TokenType type, char val);

Token* NextToken(Lexer*lexer);

int isLetter(char c);
int isNumber(char c);
char* getLiteral(Lexer*lexer);





/* -------------------------------------------------- FUNCTIONS -------------------------------------------------- 
 * */





Lexer MakeLexer(struct Stack string){ 
    Lexer lex;
    lex.string=string;
    lex.pos=0;
    return lex;
}


VStack LexString(Lexer*lexer){

    VStack stack=makeVStack(sizeof(Token));
    
    //mallof space for token
    //place token there
    //or mallic on make token

    while(lexer->pos < lexer->string.size){
        //printf("lexing...\n");
        Token*a=NextToken(lexer) ;
        //printf("token done... %i\n", a->type);
        
        Vpush(&stack,a);
    }



    return stack;
}



//gives the next token 
Token* NextToken(Lexer*lexer){
//what is at position
    char c= indexAt(&lexer->string, lexer->pos);
    //printf("lexing char  %c\n",c);


    //make token from it
    switch (c) {
        case '(':
            lexer->pos++;
            return makeToken(Lparen,NULL);
        case ')':
            lexer->pos++;
            return makeToken(Rparen,NULL);

        case '{':
            lexer->pos++;
            return makeToken(Lsquirly,NULL);
        case '}':
            lexer->pos++;
            return makeToken(Rsquirly,NULL);

        case '"':
            lexer->pos++;
            return makeToken(DoubleQuote,NULL);
        case '\'':
            lexer->pos++;
            return makeToken(SingleQuote,NULL);


        case ';':
            lexer->pos++;
            return makeToken(Semicolon,NULL);
        case '=':
            lexer->pos++;
            return makeToken(Equals,NULL);

        case '+':
            lexer->pos++;
            return makeTokenL(Operator,c);
        case '-':
            lexer->pos++;
            return makeTokenL(Operator,c);
        case '*':
            lexer->pos++;
            return makeTokenL(Operator,c);
        case '/':
            lexer->pos++;
            return makeTokenL(Operator,c);
            

        default:
            break;
    }


    //if identifier
    if (isLetter(c)) {  
        //printf("isletter: sw\n");
        char* a = getLiteral(lexer);
        //printf("has lit %s: sw\n",a);
        return makeToken(Identifier, a);
    }  


    if (isNumber(c)) {  }  
    
    //string literal 
    if (c=='"'){
        char* a = getLiteral(lexer);
        return makeToken(StringLiteral, a);
    }

    //char literal  // ( ' )
    if (c==39){}


    printf("error making token from: %c\n" ,c);
    PrintStackTrace();
    exit(2);
    //else crash
}


//returns literal untill whitespace or " so we can use it ad id or sthing
char* getLiteral(Lexer*lexer){

    char c= indexAt(&lexer->string,lexer->pos);
    //printf("getliteral got %c\n",c);
    // constrruct char* ??
    // or make char array and return it
    // we can use stack but we need to have a refrence of it somewhere or it will leak?
    // we could make a stack
    // then make an array from the size of the stack->size
    // then return the array?
    struct Stack a= makeStack();


    //this never runs into these characters?
    //printf("whil\n");
    while (c!='"' && c!=' ' && c!='\n' && c!='\t' && c!='\r' && c!='(' ){
        //printf("char is %c \n",c);
        push(&a,c);
        c=indexAt(&lexer->string, ++lexer->pos);
    }

    //printf("whil end\n");
    //?? 
    //stack has the thing sting now
    char* ret =malloc(sizeof(char) * a.size+ sizeof(char) ); //+1 for null termination

    for (int i=0; i<a.size;i++){
        ret[i]=indexAt(&a,i);
    }

    //null terminate string
    //printf("attemping to set nullterminatior\n");
    ret[a.size]='\0';


    //printf("%s\n",ret);

    return ret;

}


int isLetter(char c){
    if( (c>='a' && c<='z') || (c>='A' && c<='Z' )){
        return 1;
    }
    return 0;
}

int isNumber(char c){
    if( c>='0' && c<='1'){
        return 1;
    }
    return 0;
}


Token* makeToken(TokenType type, char* val){
    Token * a= malloc(sizeof(Token));
    a->type=type;
    a->value=val;
    return a;
}


Token* makeTokenL(TokenType type, char val){
    Token * a= malloc(sizeof(Token));
    a->type=type;
    a->v=val;
    return a;
}



void CleanToken(Token*token){
    if(token && token->value){
        free(token->value);
    }

    if (token){
        free(token);
    }
    token=NULL;
}



void CleanLexer(Lexer *lexer){
    
    removeStack(lexer->string);
    lexer=NULL;
}



#endif
