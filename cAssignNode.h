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
#include "cFuncExprNode.h"

class cAssignNode : public cStmtNode
{
public:
    cAssignNode(cVarExprNode* left, cExprNode* right) : cStmtNode()
    {
        AddChild(left);
        AddChild(right);
    }

    // The constructor for assigning expressions to function (stmt)
    cAssignNode(cVarExprNode* left, cStmtNode* right) : cStmtNode()
    {
        AddChild(left);
        AddChild(right);
    }

    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
