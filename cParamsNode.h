//******************************
// cParamsNode.h
// 
// The parameters in a function declaration
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cAstNode.h"
#include "cVarDeclNode.h"

class cParamsNode : public cAstNode
{
public:
    cParamsNode(cVarDeclNode* decl) : cAstNode()
    {
        AddChild(decl);
    }

    // Allows for multiple children (var decls) to be added to the function parameters
    void Insert(cVarDeclNode* decl)
    {
        AddChild(decl);
    }

    virtual string NodeType() { return string("args"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
