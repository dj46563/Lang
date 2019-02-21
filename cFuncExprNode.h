//******************************
// cFuncExprNode.h
// 
// A function call statement
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cStmtNode.h"

class cFuncExprNode : public cExprNode
{
public:
    cFuncExprNode(cSymbol* name, cParamListNode* params) : cExprNode()
    {
        // Check to see if the name is a delcaration
        if (name->GetDecl() == nullptr) {
            SemanticError(name->GetName() + " is not declared");
        }
        // Check to see if the name is a delclaration of a function
        else if (!name->GetDecl()->IsFunc())
        {
            SemanticError(name->GetName() + " is not a function");
        }
        // Check if the function is defined before calling it
        else if (!dynamic_cast<cFuncDeclNode*>(name->GetDecl())->GetDefined())
        {
            SemanticError(name->GetName() + " is not fully defined");
        }
        else 
        {
            AddChild(name);
            AddChild(params);
        }
    }

    virtual cDeclNode *GetType()
    {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl()->GetType();
    }

    virtual string NodeType() { return string("funcCall"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
