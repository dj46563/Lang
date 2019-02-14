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
        // Check that the types match
        if (left->GetType() != right->GetType())
        {
            SemanticError("Cannot assign " + left->GetType()->GetName() +
                    " to " + right->GetType()->GetName());
        }

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
