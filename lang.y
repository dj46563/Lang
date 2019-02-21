%{
//**************************************
// lang.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#define CHECK_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; } }
#define PROP_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; YYERROR; } }

#include <iostream>
#include "lex.h"
#include "astnodes.h"

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    float           float_val;
    cAstNode*       ast_node;
    cProgramNode*   program_node;
    cBlockNode*     block_node;
    cDeclsNode*     decls_node;
    cDeclNode*      decl_node;
    cVarDeclNode*   varDecl_node;
    cStmtsNode*     stmts_node;
    cStmtNode*     stmt_node;
    cExprNode*      expr_node;
    cIntExprNode*   int_node;
    cFloatExprNode* float_node;
    cVarExprNode*   varExpr_node;
    cParamsNode*  params_node;
    cParamListNode* paramList_node;
    cFuncDeclNode* funcDecl_node;
    cSymbol*        symbol;
    symbolTable_t*   symbolTable;
    }

%{
    int yyerror(const char *msg);

    static bool g_semanticErrorHappened = false;
    
    cAstNode *yyast_root;
%}

%start  program

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   CHAR_VAL
%token <int_val>   INT_VAL
%token <float_val> FLOAT_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   EQUALS
%token <int_val>   NOT_EQUALS

%token  PROGRAM
%token  PRINT
%token  WHILE IF ELSE ENDIF
%token  STRUCT ARRAY
%token  RETURN
%token  JUNK_TOKEN

%type <program_node> program
%type <block_node> block
%type <symbolTable> open
%type <symbolTable> close
%type <decls_node> decls
%type <decl_node> decl
%type <varDecl_node> var_decl
%type <decl_node> struct_decl
%type <decl_node> array_decl
%type <funcDecl_node> func_decl
%type <funcDecl_node> func_header
%type <funcDecl_node> func_prefix
%type <expr_node> func_call
%type <params_node> paramsspec
%type <varDecl_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <varExpr_node> lval
%type <paramList_node> params
%type <expr_node> param
%type <expr_node> expr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <varExpr_node> varref
%type <symbol> varpart

%%

program: PROGRAM block          { $$ = new cProgramNode($2);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
block:  open decls stmts close  { $$ = new cBlockNode($2, $3); }
    |   open stmts close        { $$ = new cBlockNode(nullptr, $2); }

open:   '{'                     { $$ = g_SymbolTable.IncreaseScope(); }

close:  '}'                     { $$ = g_SymbolTable.DecreaseScope(); }

decls:      decls decl          { $$->Insert($2); }
        |   decl                { $$ = new cDeclsNode($1); }
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     { $$ = $1; }
        |   array_decl ';'      { $$ = $1; }
        |   func_decl           { $$ = $1; }
        |   error ';'           {  }

var_decl:   TYPE_ID IDENTIFIER  { $$ = new cVarDeclNode($1, $2); PROP_ERROR();}
struct_decl:  STRUCT open decls close IDENTIFIER    
                                { $$ = new cStructDeclNode($3, $5); }
array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                { $$ = new cArrayDeclNode($4, $2, $6); }

func_decl:  func_header ';'
                                { $$ = $1;
                                  g_SymbolTable.DecreaseScope(); }
        |   func_header  '{' decls stmts '}'
                                { $$ = $1;
                                  $$->InsertLocals($3);
                                  $$->InsertStmts($4);
                                  g_SymbolTable.DecreaseScope(); }
        |   func_header  '{' stmts '}'
                                { $$ = $1;
                                  $$->InsertStmts($3);
                                  g_SymbolTable.DecreaseScope(); }
func_header: func_prefix paramsspec ')'
                                { $$ = $1;
                                  $$->InsertParams($2); }
        |    func_prefix ')'    { $$ = $1; }
func_prefix: TYPE_ID IDENTIFIER '('
                                { $$ = new cFuncDeclNode($1, $2);
                                  g_SymbolTable.IncreaseScope(); }
paramsspec: paramsspec',' paramspec 
                                { $$->Insert($3); }
        |   paramspec           { $$ = new cParamsNode($1); }

paramspec:  var_decl            { $$ = $1; }

stmts:      stmts stmt          { $$->Insert($2); }
        |   stmt                { $$ = new cStmtsNode($1); }

stmt:       IF '(' expr ')' stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5, nullptr); }
        |   IF '(' expr ')' stmts ELSE stmts ENDIF ';'
                                { $$ = new cIfNode($3, $5, $7); }
        |   WHILE '(' expr ')' stmt 
                                { $$ = new cWhileNode($3, $5); }
        |   PRINT '(' expr ')' ';'
                                { $$ = new cPrintNode($3); }
        |   lval '=' expr ';'   { $$ = new cAssignNode($1, $3); CHECK_ERROR();}
        |   lval '=' func_call ';'   { $$ = new cAssignNode($1, $3); CHECK_ERROR();}
        |   func_call ';'       { $$ = $1; }
        |   block               { $$ = $1; }
        |   RETURN expr ';'     { $$ = new cReturnNode($2); }
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' { $$ = new cFuncExprNode($1, $3); PROP_ERROR();}
        |   IDENTIFIER '(' ')'  { $$ = new cFuncExprNode($1, nullptr); }

varref:   varref '.' varpart    { $$->Insert($3); }
        | varref '[' expr ']'   { $$->Insert($3); }
        | varpart               { $$ = new cVarExprNode($1); PROP_ERROR();}

varpart:  IDENTIFIER            { $$ = $1; }

lval:     varref                { $$ = $1; }

params:     params',' param     { $$->Insert($3); }
        |   param               { $$ = new cParamListNode($1); }

param:      expr                { $$ = $1; }

expr:       expr EQUALS addit   { $$ = new cBinaryExprNode($1, EQUALS, $3); PROP_ERROR();}
        |   addit               { $$ = $1; }


addit:      addit '+' term      { $$ = new cBinaryExprNode($1, '+', $3); }
        |   addit '-' term      { $$ = new cBinaryExprNode($1, '-', $3); }
        |   term                {  }

term:       term '*' fact       { $$ = new cBinaryExprNode($1, '*', $3); }
        |   term '/' fact       { $$ = new cBinaryExprNode($1, '/', $3); }
        |   term '%' fact       { $$ = new cBinaryExprNode($1, '%', $3); }
        |   fact                {  }

fact:        '(' expr ')'       { $$ = $2; }
        |   INT_VAL             { $$ = new cIntExprNode($1); }
        |   FLOAT_VAL           { $$ = new cFloatExprNode($1); }
        |   varref              {  }

%%
// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}

// Function that gets called when a semantic error happens
void SemanticError(std::string error)
{
    std::cout << "ERROR: " << error << " on line "
        << yylineno << "\n";
    g_semanticErrorHappened = true;
    yynerrs++;
}
