#include "cVisitor.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor() {
            m_offset = 0;
            m_highWater = 0;
        }

        virtual void VisitAllNodes(cAstNode *node) {
            VisitAllChildren(node);
        }

        virtual void Visit(cVarDeclNode *node) {
            node->SetDeclSize(5);
        }
    private:
        int m_offset;
        int m_highWater;
};
