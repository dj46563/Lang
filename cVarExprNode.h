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
            return dynamic_cast<cSymbol*>(GetChild(NumChildren() - 1))->GetDecl();
        }

        // So that you can insert more symbols into the varref
        void Insert(cAstNode* child)
        {
            cSymbol* symbolChild = dynamic_cast<cSymbol*>(child);
            // If this is the left most thing make sure the reference to 
            // the . is actually a struct
            cSymbol * left = dynamic_cast<cSymbol*>(GetChild(NumChildren() - 1));
            if (!left->GetDecl()->IsStruct())
            {
                string name = "";
                for (int i = 0; i < NumChildren(); i++)
                {
                    name = name + dynamic_cast<cSymbol*>(GetChild(i))->GetName();
                    if (i + 1 < NumChildren())
                        name = name + ".";
                }
                SemanticError(name + " is not a struct");
                return;
            }
            else
            {
                cStructDeclNode* structDecl = dynamic_cast<cStructDeclNode*>
                    (left->GetDecl()->GetType());
                cSymbol * foundSym = structDecl->FindInStruct(
                        symbolChild->GetName());
                if (foundSym == nullptr)
                {
                    SemanticError(symbolChild->GetName() + " is not a field of " +
                            left->GetName());
                }
                else
                    child = foundSym;
            }

            AddChild(child);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
