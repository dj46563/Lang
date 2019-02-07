#pragma once

#include "cAstNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol* sym) : cExprNode()
        {
            AddChild(sym);
        }

        // So that you can insert more symbols into the varref
        void Insert(cSymbol* sym)
        {
            AddChild(sym);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
