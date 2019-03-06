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
        // Check if the identifier already exists in local scope
        if (g_SymbolTable.FindLocal(iden->GetName())) {
            SemanticError("Symbol " + iden->GetName() + 
                    " already defined in current scope");
        }

        // If the given identity already exists in any scope then create a new
        // symbol to add as a child
        if (g_SymbolTable.Find(iden->GetName())) {
            iden = new cSymbol(iden->GetName());
        }

        // Otherwise we will just use the identity symbol the scanner 
        // created for us
        
        // Insert the symbol into the symbol table, at this point
        // iden is garunteed to not already be in the symbol table
        //iden->SetDecl(type->GetDecl()); // Setting the identifier's decl to this
        iden->SetDecl(this);
        g_SymbolTable.Insert(iden);

        // Set the size member to the type's size
        SetDeclSize(type->GetDecl()->GetDeclSize());

        AddChild(type);
        AddChild(iden);
    }

    virtual cDeclNode *GetType() {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
    }
    virtual std::string GetName() {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetName();
    }

    virtual string NodeType() { return string("var_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
