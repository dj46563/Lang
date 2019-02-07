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
    cStructDeclNode(cDeclsNode* decls, cSymbol* name) : cDeclNode()
    {
        // A struct was declared so add the name into the symbol table
        // and set it as a type
        name->SetType(true);
        g_SymbolTable.Insert(name);

        AddChild(decls);
        AddChild(name);
    }

    virtual string NodeType() { return string("struct_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
