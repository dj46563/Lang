#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for an float constant (literals).
//
// Inherits from cExprNode so that float constants can be used anywhere 
// expressions are used.
//
// Author: Tyler Page (but mostly phil)
//

#include "cAstNode.h"
#include "cExprNode.h"

class cFloatExprNode : public cExprNode
{
    public:
        // param is the value of the float constant
        cFloatExprNode(float value) : cExprNode()
        {
            m_value = value;
        }

        virtual cDeclNode *GetType()
        {
            return g_SymbolTable.Find("float")->GetDecl();
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("float"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of float constant (literal)
};
