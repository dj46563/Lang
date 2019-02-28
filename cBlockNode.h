#pragma once
//**************************************
// cBlockNode.h
//
// Defines AST node for a block of code (stuff inside {})
//
// Since blocks can take the place of statements, this class inherits from 
// cStmtNode
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclsNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

class cBlockNode : public cStmtNode
{
    public:
        // params are the decls and statements contained in the block
        cBlockNode(cDeclsNode *decls, cStmtsNode *statements)
            : cStmtNode()
        {
            m_blockSize = -1;

            AddChild(decls);
            AddChild(statements);
        }

        virtual string NodeType() { return string("block"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString() {
            if (m_blockSize == 0) {
                return "";
            }
            else {
                char retStr[100];
                std::sprintf(retStr, " size=\"%d\"", m_blockSize);
                return string(retStr);
            }
        }

        cDeclsNode *GetDecls()
        {
            return static_cast<cDeclsNode*>(GetChild(0));
        }
        cStmtsNode *GetStmts()
        {
            return static_cast<cStmtsNode*>(GetChild(1));
        }

        int GetBlockSize()          { return m_blockSize; }
        void SetBlockSize(int size) { m_blockSize = size; }
    private:
        int m_blockSize;
};
