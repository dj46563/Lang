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
            // Put the main label after the decls and before stmts
            if (node->GetBlock()->GetDecls() != nullptr)
                node->GetBlock()->GetDecls()->Visit(this);
            EmitString("main:\n");
            
            // Block size needs to be word aligned
            int size = node->GetBlock()->GetBlockSize();
            if (size % 4 != 0) {
                size += 4 - (size % 4);
            }

            EmitString("ADJSP ");
            EmitInt(size);
            EmitString("\n");

            node->GetBlock()->GetStmts()->Visit(this);
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

        virtual void Visit(cBlockNode *node) {
            VisitAllChildren(node);
        }

        virtual void Visit(cAssignNode *node) {
            int varOffset = node->GetLeft()->GetDecl()->GetDeclOffset();
            int varSize = node->GetLeft()->GetDecl()->GetDeclSize();
            node->GetRight()->Visit(this);
            if (varSize == 1) {
                EmitString("POPCVAR ");
            }
            else {
                EmitString("POPVAR ");
            }
            EmitInt(varOffset);
            EmitString("\n");
        }

        virtual void Visit(cVarExprNode *node) {
            int varOffset = node->GetExprOffset();
            // Use PUSHCVAR if size is 1, otherwise PUSHVAR
            if (node->GetExprSize() == 1) {
                EmitString("PUSHCVAR ");
            }
            else {
                EmitString("PUSHVAR ");
            }
            EmitInt(varOffset);
            EmitString("\n");
        }

        virtual void Visit(cIntExprNode *node) {
            // Push the expr to the top of the stack
            EmitString("PUSH ");
            EmitInt(node->GetValue());
            EmitString("\n");
        }

        virtual void Visit(cFuncDeclNode *node) {
            // Dont do anythng if this is a just a function header
            if (node->GetStmts() == nullptr)
                return;

            // Print the label
            EmitString(node->GetName() + ":\n");

            // Pop args off stack
            cParamsNode *params = node->GetParams();
            if (params != nullptr) {
                int count = params->GetNumParams();
                for (int i = 0; i < count; i++) {
                    EmitString("POPVAR ");
                    EmitInt(params->GetParam(i)->GetDeclOffset());
                    EmitString("\n");
                }
            }

            // Adjust stack for locals
            int size = node->GetDeclSize();
            if (size % 4 != 0) {
                size += size % 4;
            }

            EmitString("ADJSP ");
            EmitInt(size);
            EmitString("\n");
            
            // Generate code for decls and stmts
            if (node->GetDecls() != nullptr)
                node->GetDecls()->Visit(this);
            if (node->GetStmts() != nullptr)
                node->GetStmts()->Visit(this);
        }

        virtual void Visit(cReturnNode *node) {
            VisitAllChildren(node);
            EmitString("RETURNV\n");
        }

        virtual void Visit(cFuncExprNode *node) {
            // Push arguments onto stack right to left
            cParamListNode *params = node->GetParamList();
            if (params != nullptr) {
                for (int i = params->GetNumParams() - 1; i >= 0; i--) {
                    params->GetParam(i)->Visit(this);
                }
            }

            // Call the function
            EmitString("CALL @");
            EmitString(node->GetName() + "\n");

            // Pop args off
            int paramSize = 0;
            if (node->GetDecl()->GetParams() != nullptr)
                paramSize = node->GetDecl()->GetParams()->GetParamsSize();
            EmitString("POPARGS ");
            EmitInt(paramSize);
            EmitString("\n");
        }

        virtual void Visit(cWhileNode *node) {
            string startLabel = GenerateLabel();
            string endLabel = GenerateLabel();

            EmitString(startLabel + ":\n");
            // Push the condition
            node->GetCondition()->Visit(this);
            // If condition is false goto end
            EmitString("JUMPE @" + endLabel + "\n");

            // Otherwise go on to statements then jump to start
            node->GetStmt()->Visit(this);
            EmitString("JUMP @");
            EmitString(startLabel + "\n");

            EmitString(endLabel + ":\n");
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
                    break;
                case AND:
                    EmitString("AND\n");
                    break;
                case OR:
                    EmitString("OR\n");
                    break;
            }
        }
};
