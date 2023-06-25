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

    //TODO fix this we are not storing tokens we are storing token pointers
    VStack stack=makeVStack(sizeof(Token*));
    
    //mallof space for token
    //place token there
    //or mallic on make token

    while(lexer->pos < lexer->string.size){
        //printf("lexing...\n");
        if(indexAt(&lexer->string,lexer->pos)==0){
            printf("would lex 0\n");
            break;
        }else{
            //printf("sending %c, %i to next token\n",indexAt(&lexer->string,lexer->pos),indexAt(&lexer->string,lexer->pos));
        }
        Token*a=NextToken(lexer) ;
        if (!a){
            break;
        }
        //printf("token done... %i\n", a->type);
        
        Vpush(&stack,&a);
    }



    return stack;
}



/*
 * gets next token. returns null at file, otherwize crashes
 * */
Token* NextToken(Lexer*lexer){
//what is at position
    char c= indexAt(&lexer->string, lexer->pos);
    //printf("lexing char  %c\n",c);

    //skip whitespace
    //we need to skip before this fn other wize we will get unknowh unless we do retunr null ptr
    while (c==' ' || c=='\n' || c== '\t' ||c=='\r'){
        c= indexAt(&lexer->string, ++lexer->pos);
    }
    

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
        case ',':
            lexer->pos++;
            return makeToken(Comma,NULL);

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

        case 0:
            return NULL;


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


    while (isNumber(c)){  
        //needs malloc
        char*literal=getLiteral(lexer);
        return makeToken(IntLiteral, literal);

    }
    
    //string literal 
    if (c=='"'){
        char* a = getLiteral(lexer);
        return makeToken(StringLiteral, a);
    }

    //char literal  // ( ' )
    if (c==39){}


    printf("error making token from: %c ,%i\n" ,c,c);
    PrintStackTrace();
    exit(2);
    //else crash
}


/*
 * returns literal untill whitespace or " so we can use it ad id or string or int literal
 * */
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
    while (c!='"' && c!=' ' && c!='\n' && c!='\t' && c!='\r' && c!='(' &&c !=')' && c != ',' ){
        //printf("char is %c \n",c);
        push(&a,c);
        c=indexAt(&lexer->string, ++lexer->pos);
    }

    //printf("whil end\n");
    //?? 
    //stack has the thing sting now
    char* ret =malloc(sizeof(char) * a.size+ sizeof(char) ); //+1 for null termination

    //does this leam mem?
    //arent we just reallocating something here
    for (int i=0; i<a.size;i++){
        ret[i]=indexAt(&a,i);
    }

    //null terminate string
    //printf("attemping to set nullterminatior\n");
    ret[a.size]='\0';

    //printf("allocced string %s at  %p",ret,ret);

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
    //printf("makes with val %s at %p\n",val,val);
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



//both of these variables are on the stack value/ and the token itself
//token should not be 
//but the value is  we make it as [] and return it so its somewhere on stack?
//idk about token that should most definetly be on the heap since we malloc it in makeToken
void CleanToken(Token*token){
    //printf("CleanToken fn %p\n",token);
    if(token && token->value){
        //printf("freeing value %s at %p\n", token->value, token->value);
        //what can you not free this char array?? 
        ////is it not on the heap?
        ///well we dont malloc it anywhere so i assume its not on the heap to be freed
        ///wait we do malloc it
        free(token->value);
    }

    if (token){
        //printf("token itself\n");
        //
        //whell this might be invalid since parameters are stack variables xd
        //wait  how is this a stack variable? this is allocated in the heap
        free(token);
    }
    token=NULL;
}



void CleanLexer(Lexer *lexer){
    
    removeStack(&lexer->string);
    lexer=NULL;
}



char* stringifyToken(TokenType tokentype){
    switch (tokentype){
        case Identifier:
            return "Identifier";

        case Lparen:
            return "Lparen";
        case Rparen:
            return "Rparen";

        case Lsquirly:
            return "Lsquirly";
        case Rsquirly:
            return "Rsquirly";

        case DoubleQuote:
            return "DoubleQuote";
        case SingleQuote:
            return "SingleQuote";


        case IntLiteral:
            return "IntLiteral";
        case StringLiteral:
            return "StringLiteral";
        case CharLiteral:
            return "CharLiteral";

        case Semicolon:
            return "Semicolon";

        case Comma:
            return "Comma";
        case Equals:
            return "Equals";
        case Operator:
            return "Operator";

        default:
            return "Un Printable Token";

    }

}


#endif
