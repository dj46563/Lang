#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode()
        {
            m_declsSize = -1;

            AddChild(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString() {
            if (m_declsSize == 0) {
                return "";
            }
            else {
                char retStr[100];
                std::sprintf(retStr, " size=\"%d\"", m_declsSize);
                return string(retStr);
            }
        }

        int GetDeclsSize()          { return m_declsSize; }
        void SetDeclsSize(int size) { m_declsSize = size; }
    private:
        int m_declsSize;
};
