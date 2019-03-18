//******************************
// cFuncDeclNode.h
// 
// Function declaration node
//
// Author: Tyler Page
//
// Date: 2/7/2019
// ******************************

#pragma once

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cParamsNode.h"
#include "cDeclsNode.h"
#include "cStmtsNode.h"

class cFuncDeclNode : public cDeclNode
{
public:
    cFuncDeclNode(cSymbol* type, cSymbol* name) : cDeclNode()
    {  
        m_params = nullptr;
        m_otherDecl = nullptr;
        m_defined = false;

        // Check if there is another func decl with this name
        // and if their return types match
        cSymbol* otherSym = g_SymbolTable.Find(name->GetName());
        if (otherSym != nullptr && otherSym->GetDecl()->IsFunc())
        {
            // Assign the pointer which tracks  the other function decl
            m_otherDecl = dynamic_cast<cFuncDeclNode*>(otherSym->GetDecl());
            // Check if redeclared with different type
            if (otherSym->GetDecl()->GetType() != type->GetDecl()->GetType())
            {
                SemanticError(name->GetName() + " previously " + 
                        "defined with different return type");
                return;
            }
        }

        // Add the function name to the symbol table and set it as a type
        // Set the name symbol's decl
        name->SetDecl(this);
        g_SymbolTable.Insert(name);

        AddChild(type);
        AddChild(name);
    }

    // Inserts the functions parameters into the node
    void InsertParams(cParamsNode* params)
    {
        m_params = params;

        // if redeclaration check if the number of params match with the
        cSymbol* mySym = g_SymbolTable.Find(
                dynamic_cast<cSymbol*>(GetChild(1))->GetName());
        if (m_otherDecl)
        {
            if (m_otherDecl->GetParams()->GetNumParams() !=
                    params->GetNumParams()) {
                SemanticError(mySym->GetName() + " redeclared with a different " +
                    "number of parameters"); 
                return;
            }

            // Check if the parameters match up by iterating through the params
            for (int i = 0; i < m_otherDecl->GetParams()->GetNumParams(); i++)
            {
                // Get parameter
                if (m_otherDecl->GetParams()->GetParam(i)->GetType() != 
                        params->GetParam(i)->GetType())
                {
                    SemanticError(mySym->GetName() + " previously defined " +
                            "with different parameters");
                    return;
                }
            }

        } 

        AddChild(params);
    }

    cParamsNode* GetParams()
    {
        return m_params;
    }

    // Inserts the function's declarations into the node
    void InsertLocals(cDeclsNode* locals)
    {
        AddChild(locals);
        m_decls = locals;
    }

    bool GetDefined()
    {
        return m_defined;
    }

    // Inserts the statements inside of the function into the node
    void InsertStmts(cStmtsNode* stmts)
    {
        // If there are already statements this is a redefinition error
        if (m_otherDecl && m_otherDecl->GetDefined())
        {
            SemanticError(dynamic_cast<cSymbol*>(GetChild(1))->GetName() +
                    " already has a definition");
        }
        else
        {
            m_defined = true;
            m_stmts = stmts;
            AddChild(stmts);
        }
    }

    cStmtsNode* GetStmts() {
        return m_stmts;
    }
    cDeclsNode* GetDecls() {
        return m_decls;
    }

    virtual cDeclNode *GetType() {
        return dynamic_cast<cSymbol*>(GetChild(0))->GetDecl();
    }
    virtual std::string GetName() {
        return dynamic_cast<cSymbol*>(GetChild(1))->GetName();
    }

    virtual bool IsFunc()
    {
        return true;
    }

    virtual string NodeType() { return string("func"); }
    virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
private:
    cStmtsNode* m_stmts;
    cDeclsNode* m_decls;
    // pointers to the params node so I know which child is the params
    cParamsNode* m_params;
    // Keeps track of the original decl that I am redeclaring
    cFuncDeclNode* m_otherDecl;
    // whether or not statements have been added to this function or not
    bool m_defined;
};
