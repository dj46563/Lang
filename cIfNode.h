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

    cExprNode *GetCondition() {
        return dynamic_cast<cExprNode*>(GetChild(0));
    }
    cStmtsNode *GetStmts() {
        return dynamic_cast<cStmtsNode*>(GetChild(1));
    }
    cStmtsNode *GetElseStmts() {
        return dynamic_cast<cStmtsNode*>(GetChild(2));
    }

    virtual string NodeType() { return string("if"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
