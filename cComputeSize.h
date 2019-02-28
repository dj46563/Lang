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
            // If the node's size isn't 1 then start offset off at a
            // multiple of 4
            if (node->GetDeclSize() != 1)
                if (m_offset % 4 != 0)
                    m_offset += 4 - (m_offset % 4);

            node->SetDeclOffset(m_offset);

            m_offset += node->GetDeclSize();
            
            // Assign high water if this is higher
            if (m_offset > m_highWater) {
                m_highWater = m_offset;
            }
        }
        virtual void Visit(cDeclsNode *node) {
            int oldOffset = m_offset;
            VisitAllChildren(node);
            node->SetDeclsSize(m_offset - oldOffset);
        }
        virtual void Visit(cBlockNode *node) {
            int oldOffset = m_offset;
            int oldHighWater = m_highWater;
            VisitAllChildren(node);
            node->SetBlockSize(m_highWater - oldOffset);
            if (oldHighWater > m_highWater)
                m_highWater = oldHighWater;
            m_offset = oldOffset;
        }
    private:
        int m_offset;
        int m_highWater;
};
