#pragma once
//**************************************
// astnodes.h
//
// Single place that includes all the ast nodes.
// Useful for lang.y and lang.l
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cAstNode.h"
#include "cSymbol.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cBlockNode.h"
#include "cProgramNode.h"
#include "cPrintNode.h"
#include "cExprNode.h"
#include "cIntExprNode.h"
#include "cFloatExprNode.h"
#include "cSymbolTable.h"
#include "cVarDeclNode.h"
#include "cVarExprNode.h"
#include "cReturnNode.h"
#include "cAssignNode.h"
#include "cStructDeclNode.h"
#include "cIfNode.h"
#include "cWhileNode.h"
#include "cParamsNode.h"
#include "cFuncDeclNode.h"
#include "cParamListNode.h"
#include "cFuncExprNode.h"
#include "cOpNode.h"
#include "cBinaryExprNode.h"
