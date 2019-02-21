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
        // Check if there is another func decl with this name
        // and if their return types match
        cSymbol* otherSym = g_SymbolTable.Find(name->GetName());
        if (otherSym != nullptr)
        {
            if (otherSym->GetDecl()->GetType() != type->GetDecl()->GetType())
            {
                SemanticError(name->GetName() + " previously " + 
                        "defined with a different return type");
            }
        }

        // Add the function name to the symbol table and set it as a type
        // Set the name symbol's decl
        name->SetDecl(this);
        g_SymbolTable.Insert(name);

        AddChild(type);
        AddChild(name);
    }

    // Inserts the functions parameters into the node
    void InsertParams(cParamsNode* params)
    {
        AddChild(params);
    }

    // Inserts the function's declarations into the node
    void InsertLocals(cDeclsNode* locals)
    {
        AddChild(locals);
    }

    // Inserts the statements inside of the function into the node
    void InsertStmts(cStmtsNode* stmts)
    {
        AddChild(stmts);
    }

    virtual cDeclNode *GetType() {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
    }
    virtual std::string GetName() {
        return dynamic_cast<cSymbol*>(GetChild(1))->GetName();
    }

    virtual bool IsFunc()
    {
        return true;
    }

    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
