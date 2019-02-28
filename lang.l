%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Tyler Page >>>>
//

#include <iostream>
#include "lex.h"
#include "cSymbolTable.h"
#include "astnodes.h"
#include "langparse.h"

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

"!="                        { yylval.int_val = NEQUALS; DO_RETURN(NEQUALS); }
"=="                        { yylval.int_val = EQUALS; DO_RETURN(EQUALS); }
"&&"                        { yylval.int_val = AND; DO_RETURN(AND); }
"||"                        { yylval.int_val = OR; DO_RETURN(OR); }

"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"endif"                     DO_RETURN(ENDIF);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"array"                     DO_RETURN(ARRAY);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);

[ \t\n]                             {}
{DIGIT}+                    {
                                yylval.int_val = atoi(yytext);
                                DO_RETURN(INT_VAL);
                            }
"//".*"\n"                          {}                        
{DIGIT}+"."{DIGIT}+         {
                                yylval.float_val = atof(yytext);    
                                DO_RETURN(FLOAT_VAL);
                            }

{identifier}                {
                                cSymbol* symbol = g_SymbolTable.Find(yytext);
                                if (symbol == nullptr) {
                                    symbol = new cSymbol(yytext);
                                }
                                yylval.symbol = symbol;
                                if (yylval.symbol->IsType())
                                    return TYPE_ID;
                                else
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
