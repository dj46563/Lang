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
        cDeclNode() : cAstNode() {
            m_declSize = -1;
            m_declOffset = -1;
        }
        virtual bool IsVar() { return false; }
        virtual bool IsFloat() { return false;}
        virtual int GetSize() { return 0; }
        virtual bool IsFunc() { return false; }
        virtual bool IsStruct() { return false; }
        virtual cDeclNode *GetType() = 0;
        virtual std::string GetName() = 0;

        virtual string AttributesToString() {
            if (m_declSize == 0 && m_declOffset == 0) {
                return "";
            }
            else {
                char retStr[100];
                std::sprintf(retStr, " size=\"%d\" offset=\"%d\"", 
                    m_declSize, m_declOffset);
                return string(retStr);
            }
        }

        int GetDeclSize()   { return m_declSize; }
        int GetDeclOffset() { return  m_declOffset; }
        void SetDeclSize(int size) { m_declSize = size; }
        void SetDeclOffset(int offset) { m_declOffset = offset; }
    private:
        int m_declSize;
        int m_declOffset;
};
