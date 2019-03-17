//******************************
// cWhileNode.h
// 
// While Node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"
#include "cExprNode.h"
#include "cStmtsNode.h"

class cWhileNode : public cStmtNode
{
public:
    cWhileNode(cExprNode* condition, cStmtNode* stmt) : cStmtNode()
    {
        AddChild(condition);
        AddChild(stmt);
    }

    cExprNode* GetCondition() {
        return dynamic_cast<cExprNode*>(GetChild(0));
    }
    cStmtNode* GetStmt() {
        return dynamic_cast<cStmtNode*>(GetChild(1));
    }

    virtual string NodeType() { return string("while"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
