#include "cVisitor.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(string filename) : cVisitor() {

        }

        virtual void VisitAllNodes(cAstNode *node) {
            VisitAllChildren(node);
        }
};
