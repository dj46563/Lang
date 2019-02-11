//******************************
// cArrayDeclNode.h
// 
// Array Declaration Node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cDeclNode.h"
#include "cSymbol.h"

class cArrayDeclNode : public cDeclNode
{
public:
    cArrayDeclNode(int size, cSymbol* type, cSymbol* name) : cDeclNode()
    {
        m_size = size;

        // Add the name into the symbol table as a type
        name->SetType(true);
        g_SymbolTable.Insert(name);

        AddChild(type);
        AddChild(name);
    }

    virtual string AttributesToString()
    {
        return " count=\"" + std::to_string(m_size) + "\"";
    }
    virtual string NodeType() { return string("array_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }

protected:
    int m_size;
};
