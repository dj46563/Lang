#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Phil Howard and Tyler Page 
// phil.howard@oit.edu
//
//

#include "cSymbol.h"
#include <unordered_map>
#include <list>
#include "cBaseTypeNode.h"

using namespace std;

typedef unordered_map<string, cSymbol *> symbolTable_t;

class cSymbolTable
{
    private:
        list<symbolTable_t*> m_stack;
    public:
        // Create a symbol table
        cSymbolTable() { 
            IncreaseScope();

            // Insert keywords char, int, and float into symbol table
            cSymbol *charSym = new cSymbol("char");
            charSym->SetType(true);
            // Assign base node to symbol
            cBaseTypeNode *baseChar = new cBaseTypeNode("char", 1, false);
            charSym->SetDecl(baseChar);

            cSymbol *intSym = new cSymbol("int");
            intSym->SetType(true);
            // Assign base node to symbol
            cBaseTypeNode *baseInt = new cBaseTypeNode("int", 4, false);
            intSym->SetDecl(baseInt);  

            cSymbol *floatSym = new cSymbol("float");
            floatSym->SetType(true);
            // Assign base node to symbol
            cBaseTypeNode *baseFloat = new cBaseTypeNode("float", 8, true);
            floatSym->SetDecl(baseFloat);


            Insert(charSym);
            Insert(intSym);
            Insert(floatSym);
        }

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t *IncreaseScope() {
            symbolTable_t* newTable = new symbolTable_t;
            m_stack.push_back(newTable);
            return newTable;
        }

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t *DecreaseScope() {
            m_stack.pop_back();
            return m_stack.back();
        }

        // insert a symbol into the table
        // Assumes the symbol is not already in the table
        cSymbol* Insert(cSymbol *sym) {
            (*m_stack.back())[sym->GetName()] = sym;
            return sym;
        }

        // Do a lookup in the nested table. 
        // Return the symbol for the outer-most match. 
        // Returns nullptr if no match is found.
        cSymbol *Find(string name) {
           for (list<symbolTable_t*>::reverse_iterator it = m_stack.rbegin(); it != m_stack.rend(); ++it) {
                symbolTable_t scope = **it;
                if (scope.find(name) != scope.end()) {
                    return scope[name];
                }
           }
           return nullptr;
        }

        // Find a symbol in the outer-most scope.
        // NOTE: does not search nested scopes, only the outermost scope.
        // Return the symbol if found.
        // Returns nullptr if the symbol is not found.
        cSymbol *FindLocal(string name) {
            symbolTable_t scope = *(m_stack.back());
            if (scope.find(name) == scope.end()) {
                return nullptr;
            }
            else {
                return scope[name];
            }
        }
};

// Declaration for the global symbol table.
// Definition is in main.cpp
extern cSymbolTable g_SymbolTable;
