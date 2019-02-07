//******************************
// cIfNode.h
// 
// If Node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"
#include "cExprNode.h"
#include "cStmtsNode.h"

class cIfNode : public cStmtNode
{
public:
    cIfNode(cExprNode* condition, cStmtsNode* stmts, cStmtsNode* elseStmts) : cStmtNode()
    {
        AddChild(condition);
        AddChild(stmts);
        AddChild(elseStmts);
    }

    virtual string NodeType() { return string("if"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
