#pragma once

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"

class cVarDeclNode : public cDeclNode
{
public:
    cVarDeclNode(cSymbol* type, cSymbol* iden) : cDeclNode()
    {
        AddChild(type);
        AddChild(iden);
    }

    virtual string NodeType() { return string("var_decl"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
