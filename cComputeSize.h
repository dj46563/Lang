#include "cVisitor.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor() {
            m_offset = 0;
            m_highWater = 0;
            m_isParam = false;
        }

        virtual void VisitAllNodes(cAstNode *node) {
            VisitAllChildren(node);
        }

        virtual void Visit(cVarDeclNode *node) {
            // If the node's size isn't 1 then start offset off at a
            // multiple of 4, if these are params then round
            if (node->GetDeclSize() != 1 || m_isParam)
                m_offset = roundNumber(m_offset, 4);

            node->SetDeclOffset(m_offset);

            int size = node->GetType()->GetDeclSize();
            node->SetDeclSize(size);
            m_offset += size;
            
            // Assign high water if this is higher
            if (m_offset > m_highWater) {
                m_highWater = m_offset;
            }
        }
        virtual void Visit(cVarExprNode *node) {
            // Add up all the offsets of the children in var expr
            int offset = 0;
            for (int i = 0; i < node->GetExprChildCount(); i++) {
                offset += node->GetExprChild(i)->GetDecl()->GetDeclOffset();
            }

            node->SetExprSize(node->GetDecl()->GetDeclSize());
            node->SetExprOffset(offset);
            VisitAllChildren(node);
        }
        virtual void Visit(cStructDeclNode *node) {
            node->SetDeclOffset(0);
            int oldOffset = m_offset;
            int oldHighWater = m_highWater;
            // Have its children start at offset 0
            m_offset = 0;
            m_highWater = 0;

            VisitAllChildren(node);
            node->SetDeclSize(m_highWater);
            // Put offset back to where it was
            m_offset = oldOffset;
            m_highWater = oldHighWater;
        }
        virtual void Visit(cFuncDeclNode *node) {
            int oldOffset = m_offset;
            int oldHighWater = m_highWater;
            // Have its children start at offset 0 and highwater 0
            m_offset = 0;
            m_highWater = 0;

            node->SetDeclOffset(0);
            VisitAllChildren(node);

            // Round the high water, anything after this func decl
            // will not need to store the empty space
            m_highWater = roundNumber(m_highWater, 4);
            node->SetDeclSize(m_highWater);
            // Put offset back to where it was
            m_offset = oldOffset;
            m_highWater = oldHighWater;
        }
        virtual void Visit(cParamsNode *node) {
            int oldOffset = m_offset;

            // Enable params so that all args become word aligned
            m_isParam = true;
            VisitAllChildren(node);
            m_isParam = false;

            // Round the offset to the nearest 4
            // The params node will store the empty space at the end
            m_offset = roundNumber(m_offset, 4);
            node->SetParamsSize(m_offset - oldOffset);
        }
        virtual void Visit(cDeclsNode *node) {
            int oldOffset = m_offset;
            VisitAllChildren(node);
            node->SetDeclsSize(m_offset - oldOffset);
        }
        virtual void Visit(cBlockNode *node) {
            int oldOffset = m_offset;
            // Remmember the starting high water because I am going to reset it
            int oldHighWater = m_highWater;
            // Set the high water to my offset (reset) so it can be used to
            // calc my local size
            m_highWater = m_offset; 
            VisitAllChildren(node);

            node->SetBlockSize(m_highWater - oldOffset);
            // When the block is complete then put the offset back to
            // where it started
            m_offset = oldOffset;
            
            // Set high water back to the starting high water if it was greater
            if (oldHighWater > m_highWater)
                m_highWater = oldHighWater;
        }
    private:
        int m_offset;
        int m_highWater;
        bool m_isParam;

        int roundNumber(int number, int mod) {
            // Round the function size to 4
            int size = number;
            int extra = 0;
            if (size % mod != 0)
                extra = mod - size % mod;
            size = size + extra;
            return size;
        }
};
