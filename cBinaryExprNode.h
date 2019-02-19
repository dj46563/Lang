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

        // Determine type
        // float -> int -> char
        std::string expr1Name = expr1->GetType()->GetName();
        std::string expr2Name = expr2->GetType()->GetName();
        m_type = expr1->GetType();
        if (expr1Name == "float")
            m_type = expr1->GetType();
        else if (expr1Name == "int")
            m_type = expr1->GetType();
        if (expr2Name == "float")
            m_type = expr2->GetType();
        else if (expr2Name == "int");
            m_type = expr2->GetType();
    }

    // TODO
    virtual cDeclNode *GetType()
    {
        return m_type;
    }

    virtual string NodeType() { return string("expr"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
private:
    cDeclNode *m_type;
};
