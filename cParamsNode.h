//******************************
// cParamsNode.h
// 
// The parameters in a function declaration
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cAstNode.h"
#include "cVarDeclNode.h"

class cParamsNode : public cAstNode
{
public:
    cParamsNode(cVarDeclNode* decl) : cAstNode()
    {
        AddChild(decl);

        m_paramsSize = -1;
    }

    int GetNumParams()
    {
        if (HasChildren())
            return NumChildren();
        else
            return 0;
    }

    cVarDeclNode* GetParam(int i )
    {
        return dynamic_cast<cVarDeclNode*>(GetChild(i));
    }

    // Allows for multiple children (var decls) to be added to the function parameters
    void Insert(cVarDeclNode* decl)
    {
        AddChild(decl);
    }

    void SetParamsSize(int size) {
        m_paramsSize = size;
    }
    int GetParamsSize() {
        return m_paramsSize;
    }

    virtual string AttributesToString() {
        if (m_paramsSize == 0) {
            return "";
        }
        else {
            string result( " size=\"");
            result += std::to_string(m_paramsSize);
            result += "\"";
            return result;
        }
    }
    virtual string NodeType() { return string("args"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
private:
    int m_paramsSize;
};
