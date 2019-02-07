//******************************
// cReturnNode.h
// 
// A node that is created for return statements
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
public:
    cReturnNode(cExprNode* ret) : cStmtNode()
    {
        AddChild(ret);
    }

    virtual string NodeType() { return string("return"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
