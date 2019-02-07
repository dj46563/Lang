#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"
#include <iostream>

class cVarDeclNode : public cDeclNode
{
public:
    cVarDeclNode(cSymbol* type, cSymbol* iden) : cDeclNode()
    {
        // If the given identity already exists in any scope then create a new
        // symbol to add as a child
        if (g_SymbolTable.Find(iden->GetName())) {
            iden = new cSymbol(iden->GetName());
        }

        // Otherwise we will just use the identity symbol the scanner created for us
        
        // Insert the symbol into the symbol table, at this point
        // iden is garunteed to not already be in the symbol table
        g_SymbolTable.Insert(iden);

        AddChild(type);
        AddChild(iden);
    }

    virtual string NodeType() { return string("var_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
