#pragma once
// cBinaryExprNode.h
//
//  Node which represents any operation with an expression on the left and right.
//  op must be a registered operator in the cOpNode class
//
// Author: Tyler Page
//

#include "cAstNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
public:
    cBinaryExprNode(cExprNode *expr1, int op, cExprNode *expr2) : cExprNode()
    {
        AddChild(expr1);
        AddChild(new cOpNode(op));
        AddChild(expr2);    
    }

    virtual string NodeType() { return string("expr"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
