%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Tyler Page >>>>
//

#include "lex.h"
#include "langparse.h"
#include "cSymbolTable.h"

// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
#define DO_RETURN(a) { return (a); }
//#define DO_RETURN(a) { return Return(a); }

int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
    /* NOTE: You do not need to use definitions */
period          [.]
DIGIT           [0-9]
NONDIGIT        [_a-zA-Z]
identifier      {NONDIGIT}+({DIGIT}|{NONDIGIT})* 
%%


"{"                         {
                                return yytext[0];
                            }
"}"                         {
                                return yytext[0];
                            }

"program"                   DO_RETURN(PROGRAM);
{period}                    DO_RETURN('.');
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"]"                         DO_RETURN(']');
"["                         DO_RETURN('[');
";"                         DO_RETURN(';');
","                         DO_RETURN(',');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');
"%"                         DO_RETURN('%');
"="                         DO_RETURN('=');

"!="                        DO_RETURN(NOT_EQUALS);
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);

"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"endif"                     DO_RETURN(ENDIF);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       //DO_RETURN(INT_VAL);
"float"                     //DO_RETURN(FLOAT_VAL);
"char"                      //DO_RETURN(CHAR_VAL);
"array"                     DO_RETURN(ARRAY);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);

[ \t\n]                             {}
{DIGIT}+                            DO_RETURN(INT_VAL);
"//".*"\n"                          {}                        
{DIGIT}+"."{DIGIT}+                 DO_RETURN(FLOAT_VAL);

{identifier}                {
                                cSymbol* symbol = g_symbolTable.FindLocal(yytext);
                                if (symbol == nullptr) {
                                    cSymbol* symbol = new cSymbol(yytext);
                                    yylval.symbol = g_symbolTable.Insert(symbol);
                                }
                                else {
                                    yylval.symbol = symbol;
                                }
                                return IDENTIFIER;
                            }
.                           DO_RETURN(JUNK_TOKEN);


%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
