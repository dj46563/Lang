//******************************
// cParamListNode.h
// 
// The parameters used when calling a function
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cExprNode.h"

class cParamListNode : public cAstNode
{
public:
    cParamListNode(cExprNode* param) : cAstNode()
    {
        AddChild(param);
    }

    // Used to add another parameter to the node
    void Insert(cExprNode* param)
    {
        AddChild(param);
    }

    int GetNumParams()
    {
        return NumChildren();
    }

    virtual string NodeType() { return string("params"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
