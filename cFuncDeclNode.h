//******************************
// cFuncDeclNode.h
// 
// Function declaration node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cParamsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"

class cFuncDeclNode : public cDeclNode
{
public:
    cFuncDeclNode(cSymbol* type, cSymbol* name) : cDeclNode()
    {   
        // Add the function name to the symbol table and set it as a type
        g_SymbolTable.Insert(name);

        AddChild(type);
        AddChild(name);
    }

    void InsertParams(cParamsNode* params)
    {
        AddChild(params);
    }

    void InsertLocals(cDeclsNode* locals)
    {
        AddChild(locals);
    }

    void InsertStmts(cStmtsNode* stmts)
    {
        AddChild(stmts);
    }

    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
