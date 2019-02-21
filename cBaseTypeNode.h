#pragma once
//**************************************
// cBaseTypeNode
//
// 
//
// Author: Tyler Page
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        cBaseTypeNode(std::string name, int size, bool isFloat) : cDeclNode() {
            m_name = name;
            m_size = size;
            m_isFloat = isFloat;
        }

        virtual cDeclNode *GetType() {
            return this;
        }

        virtual std::string GetName() {
            return m_name;
        }

        virtual string NodeType() {
            return string("baseType_node");
        }
        virtual int GetSize()
        {
            return m_size;
        }
        virtual bool IsFloat()
        {
            return m_isFloat;
        }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    private:
        std::string m_name;
        int m_size;
        bool m_isFloat;
};
