//******************************
// cStructDeclNode.h
// 
// A node for the struct declaration
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cDeclNode.h"
#include "cDeclsNode.h"

class cStructDeclNode : public cDeclNode
{
public:
    cStructDeclNode(cDeclsNode* decls, cSymbol* name, symbolTable_t* scope) : cDeclNode()
    {
        // Assign the scope so that we can search it for decls
        m_scope = scope;

        // A struct was declared so add the name into the symbol table
        // and set it as a type
        name->SetType(true);
        name->SetDecl(this);
        g_SymbolTable.Insert(name);

        AddChild(decls);
        AddChild(name);
    }

    // Perform a symbol table search in this scope
    cSymbol* FindInStruct(string name)
    {
        if (m_scope->find(name) == m_scope->end()) {
            return nullptr;
        }
        else {
            return (*m_scope)[name];
        }
    }

    virtual cDeclNode *GetType() {
        return dynamic_cast<cSymbol*>(GetChild(1))->GetDecl();
    }
    virtual std::string GetName() {
        return dynamic_cast<cSymbol*>(GetChild(1))->GetName();
    }
    virtual bool IsStruct() { return true; }

    virtual string NodeType() { return string("struct_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
private:
    symbolTable_t* m_scope;
};
