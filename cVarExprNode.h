#pragma once

#include "cAstNode.h"
#include "cSymbol.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol* sym) : cExprNode()
        {
            // Check if the symbol exists in any scope
            cSymbol *symbol = g_SymbolTable.Find(sym->GetName());
            if (symbol == nullptr)
                SemanticError("Symbol " + sym->GetName() + " not defined");

            AddChild(sym);
        }

        virtual cDeclNode *GetType()
        {
            return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
        }

        // So that you can insert more symbols into the varref
        void Insert(cAstNode* child)
        {
            AddChild(child);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
