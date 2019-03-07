#include "cVisitor.h"
#include "emit.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(string filename) : cVisitor() {
            InitOutput(filename);
        }

        ~cCodeGen() {
            FinalizeOutput();
        }

        virtual void VisitAllNodes(cAstNode *node) {
            node->Visit(this);
        }

        virtual void Visit(cProgramNode *node) {
            EmitString("main:\n");
            VisitAllChildren(node);
        }

        virtual void Visit(cPrintNode *node) {
            // Visit the print node's expr
            node->GetExpr()->Visit(this);
            // Call the print function on the expr which is now on the top
            // of the stack
            EmitString("CALL @print\n");
            EmitString("POP\n");
            EmitString("POP\n");
        }

        virtual void Visit(cIntExprNode *node) {
            // Push the expr to the top of the stack
            EmitString("PUSH ");
            EmitInt(node->GetValue());
            EmitString("\n");
        }

        virtual void Visit(cWhileNode *node) {
            node->GetCondition()->Visit(this);
            
            string startLabel = GenerateLabel();
            string endLabel = GenerateLabel();

            EmitString(startLabel + ":\n");
            EmitString("JUMPE @" + endLabel + "\n");
            node->GetStmt()->Visit(this);
            EmitString("JUMP");  // TODO: finish this 
        }

        virtual void Visit(cIfNode *node) {
            // Pushes the condition to be checked by jumpe
            node->GetCondition()->Visit(this);

            // Generate my labels
            string elseLabel = GenerateLabel();
            string endLabel = GenerateLabel();

            // If condition is 0 goto the else label
            EmitString("JUMPE @" + elseLabel + "\n");
            // Otherwise run the stmts and jump to the end
            node->GetStmts()->Visit(this);
            EmitString("JUMP @" + endLabel + "\n");
            // Create else label and stmts
            EmitString(elseLabel + ": " + "\n");
            node->GetElseStmts()->Visit(this);
            // End label
            EmitString(endLabel + ": " + "\n");
        }

        virtual void Visit(cBinaryExprNode *node) {
            node->GetLeft()->Visit(this);
            node->GetRight()->Visit(this);
            // do operator
            int op = node->GetOp()->GetOp();
            switch (op) {
                case '+':
                    EmitString("PLUS\n");
                    break;
                case '-':
                    EmitString("MINUS\n");
                    break;
                case '*':
                    EmitString("TIMES\n");
                    break;
                case '/':
                    EmitString("DIVIDE\n");
                    break;
                case '%':
                    EmitString("MOD\n");
                    break;
                case EQUALS:
                    EmitString("EQ\n");
                    break;
                case NEQUALS:
                    EmitString("NE\n");
                case AND:
                    EmitString("AND\n");
                    break;
                case OR:
                    EmitString("OR\n");
                    break;
            }
        }
};
