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
            // Do not throw an error if you are assigning char to int,
            // char to float, or int to float
            std::string leftName = left->GetType()->GetName();
            std::string rightName = right->GetType()->GetName();
            if (!((leftName == "int" && rightName == "char") ||
                    (leftName == "float" && rightName == "char") ||
                    (leftName == "float" && rightName == "int")))
                SemanticError("Cannot assign " + rightName +
                    " to " + leftName);
        }

        AddChild(left);
        AddChild(right);

        rightStr = "test";
    }

    // The constructor for assigning expressions to function (stmt)
    cAssignNode(cVarExprNode* left, cStmtNode* right) : cStmtNode()
    {
        AddChild(left);
        AddChild(right);
    }

    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
    std::string rightStr;
};
