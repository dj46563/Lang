#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}
        virtual bool IsVar() { return false; }
        virtual bool isFloat() { return false;}
        virtual int Size() { return 0; }
        virtual bool IsFunc() { return false; }
        virtual bool IsStruct() { return false; }
        virtual cDeclNode *GetType() = 0;
        virtual std::string GetName() = 0;
};
