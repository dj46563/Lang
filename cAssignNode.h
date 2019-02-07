//******************************
// cAssignNode.h
// 
// Assign Node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"
#include "cVarExprNode.h"
#include "cExprNode.h"

class cAssignNode : public cStmtNode
{
public:
    cAssignNode(cVarExprNode* left, cExprNode* right) : cStmtNode()
    {
        AddChild(left);
        AddChild(right);
    }

    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
