//******************************
// cFuncExprNode.h
// 
// A function call statement
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"

class cFuncExprNode : public cStmtNode
{
public:
    cFuncExprNode(cSymbol* name, cParamListNode* params) : cStmtNode()
    {
        AddChild(name);
        AddChild(params);
    }

    virtual string NodeType() { return string("funcCall"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
