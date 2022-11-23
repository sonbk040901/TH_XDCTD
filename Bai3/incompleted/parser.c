/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
Token *currentToken;
Token *lookAhead;

void scan(void)
{
  Token *tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType)
{
  if (lookAhead->tokenType == tokenType)
  {
    printToken(lookAhead);
    scan();
  }
  else
    missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void)
{
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void)
{
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST)
  {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  }
  else
    compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void)
{
  if (lookAhead->tokenType == KW_TYPE)
  {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  }
  else
    compileBlock3();
}

void compileBlock3(void)
{
  if (lookAhead->tokenType == KW_VAR)
  {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  }
  else
    compileBlock4();
}

void compileBlock4(void)
{
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void)
{
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecls(void)
{
  // TODO 10, 11
  if (lookAhead->tokenType == TK_IDENT)
  {
    compileConstDecl();
    compileConstDecls();
  }
}

void compileConstDecl(void)
{
  // TODO 12,
  eat(TK_IDENT);
  eat(SB_EQ);
  compileConstant();
  eat(SB_SEMICOLON);
}

void compileTypeDecls(void)
{
  // TODO  13, 14
  if (lookAhead->tokenType == TK_IDENT)
  {
    compileTypeDecl();
    compileTypeDecls();
  }
}

void compileTypeDecl(void)
{
  // TODO 15,
  eat(TK_IDENT);
  eat(SB_EQ);
  compileType();
  eat(SB_SEMICOLON);
}

void compileVarDecls(void)
{
  // TODO 16, 17
  if (lookAhead->tokenType == TK_IDENT)
  {
    compileVarDecl();
    compileVarDecls();
  }
}

void compileVarDecl(void)
{
  // TODO 18
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
}

void compileSubDecls(void)
{
  assert("Parsing subtoutines ....");
  // TODO 19, 20, 21
  switch (lookAhead->tokenType)
  {
  case KW_FUNCTION:
    compileFuncDecl();
    compileSubDecls();
    break;
  case KW_PROCEDURE:
    compileProcDecl();
    compileSubDecls();
    break;
  default:
    break;
  }
  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void)
{
  assert("Parsing a function ....");
  // TODO 22
  eat(KW_FUNCTION);
  eat(TK_IDENT);
  compileParams();
  eat(SB_COLON);
  compileBasicType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);

  assert("Function parsed ....");
}

void compileProcDecl(void)
{
  assert("Parsing a procedure ....");
  // TODO 23
  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void)
{
  // TODO 36, 37, 38
  switch (lookAhead->tokenType)
  {
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  case TK_FLOAT:
    eat(TK_FLOAT);
    break;
  case TK_STRING:
    eat(TK_STRING);
    break;
  default:
    error(ERR_INVALIDCHARCONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileConstant(void)
{
  // TODO 40, 41, 42, 43
  TokenType type = lookAhead->tokenType;
  switch (type)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileConstant2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileConstant2();
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  case TK_STRING:
    eat(TK_STRING);
    break;
  //
  default:
    switch (type)
    {
    case TK_NUMBER:
    case TK_FLOAT:
    case TK_IDENT:
      compileConstant2();
      break;
    default:
      error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
      break;
    }
    break;
  }
}

void compileConstant2(void)
{
  // TODO 44, 45
  switch (lookAhead->tokenType)
  {
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_FLOAT:
    eat(TK_FLOAT);
    break;
  default:
    break;
  }
}

void compileType(void)
{
  // TODO 30, 31, 32, 33
  switch (lookAhead->tokenType)
  {
  case KW_INTEGER:
    eat(KW_INTEGER);
    break;
  case KW_CHAR:
    eat(KW_CHAR);
    break;
  case KW_FLOAT:
    eat(KW_FLOAT);
    break;
  case KW_ARRAY:
    eat(KW_ARRAY);
    eat(SB_LBRACKET);
    eat(TK_NUMBER);
    eat(SB_RBRACKET);
    eat(KW_OF);
    compileType();
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  default:
    error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileBasicType(void)
{
  // TODO 34, 35
  switch (lookAhead->tokenType)
  {
  case KW_INTEGER:
    eat(KW_INTEGER);
    break;
  case KW_CHAR:
    eat(KW_CHAR);
    break;
  case KW_FLOAT:
    eat(KW_FLOAT);
    break;
  default:
    error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileParams(void)
{
  // TODO 24, 25
  if (lookAhead->tokenType == SB_LPAR)
  {
    eat(SB_LPAR);
    compileParam();
    compileParams2();
    eat(SB_RPAR);
  }
}

void compileParams2(void)
{
  // TODO 26, 27
  if (lookAhead->tokenType == SB_SEMICOLON)
  {
    eat(SB_SEMICOLON);
    compileParam();
    compileParams2();
  }
}

void compileParam(void)
{
  // TODO 28, 29
  switch (lookAhead->tokenType)
  {
  case TK_IDENT:
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
    break;
  case KW_VAR:
    eat(KW_VAR);
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
    break;
  default:
    error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileStatements(void)
{
  // TODO 46
  compileStatement();
  compileStatements2();
}

void compileStatements2(void)
{
  // TODO 47, 48
  if (lookAhead->tokenType != KW_END)
  {
    eat(SB_SEMICOLON);
    compileStatement();
    compileStatements2();
  }
}

void compileStatement(void)
{
  switch (lookAhead->tokenType)
  {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
    eat(SB_SEMICOLON);
    break;
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileAssignSt(void)
{
  assert("Parsing an assign statement ....");
  // TODO 56, 57
  eat(TK_IDENT);
  if (lookAhead->tokenType == SB_LBRACKET)
    compileIndexes();
  if (lookAhead->tokenType == SB_ASSIGN)
  {
    eat(SB_ASSIGN);
    if (lookAhead->tokenType == TK_STRING)
      eat(TK_STRING);
    else
      compileExpression();
  }
  else
  {
    compileAssign();
    compileExpression();
  }
  assert("Assign statement parsed ....");
}

void compileAssign(void)
{
  switch (lookAhead->tokenType)
  {
  case SB_ASSIGN_PLUS:
    eat(SB_ASSIGN_PLUS);
    break;
  case SB_ASSIGN_SUBTRACT:
    eat(SB_ASSIGN_SUBTRACT);
    break;
  case SB_ASSIGN_TIMES:
    eat(SB_ASSIGN_TIMES);
    break;
  case SB_ASSIGN_DIVIDE:
    eat(SB_ASSIGN_DIVIDE);
    break;
  default:
    break;
  }
}
void compileCallSt(void)
{
  assert("Parsing a call statement ....");
  // TODO 58
  eat(KW_CALL);
  eat(TK_IDENT);
  compileArguments();
  assert("Call statement parsed ....");
}

void compileGroupSt(void)
{
  assert("Parsing a group statement ....");
  // TODO 59
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
  assert("Group statement parsed ....");
}

void compileIfSt(void)
{
  // TODO 60
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE)
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void)
{
  // TODO 61, 62
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void)
{
  assert("Parsing a while statement ....");
  // TODO 63
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
  assert("While statement pased ....");
}

void compileForSt(void)
{
  assert("Parsing a for statement ....");
  // TODO 64
  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatement();
  assert("For statement parsed ....");
}

void compileArguments(void)
{
  // TODO 65, 66
  if (lookAhead->tokenType == SB_LPAR)
  {
    eat(SB_LPAR);
    compileExpression();
    compileArguments2();
    eat(SB_RPAR);
  }
}

void compileArguments2(void)
{
  // TODO 67, 68`
  if (lookAhead->tokenType == SB_COMMA)
  {
    eat(SB_COMMA);
    compileExpression();
    compileArguments2();
  }
}

void compileCondition(void)
{
  // TODO 68
  compileExpression();
  compileCondition2();
}

void compileCondition2(void)
{
  // TODO 69, 70, 71, 72, 73, 74
  switch (lookAhead->tokenType)
  {
  case SB_EQ:
    eat(SB_EQ);
    compileExpression();
    break;
  case SB_NEQ:
    eat(SB_NEQ);
    compileExpression();
    break;
  case SB_LE:
    eat(SB_LE);
    compileExpression();
    break;
  case SB_LT:
    eat(SB_LT);
    compileExpression();
    break;
  case SB_GE:
    eat(SB_GE);
    compileExpression();
    break;
  case SB_GT:
    eat(SB_GT);
    compileExpression();
    break;
  default:
    break;
  }
}

void compileExpression(void)
{
  assert("Parsing an expression");
  // TODO 75, 76, 77
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    break;
  default:
    break;
  }
  compileExpression2();
  assert("Expression parsed");
}

void compileExpression2(void) 
{
  // TODO 78
  compileTerm();
  compileExpression3();
}

void compileExpression3(void)
{
  // TODO 79, 80, 81
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileTerm();
    compileExpression3();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileTerm();
    compileExpression3();
    break;
  default:
    break;
  }
}

void compileTerm(void)
{
  // TODO 82
  compileFactor();
  compileTerm2();
}

void compileTerm2(void)
{
  // TODO 83, 84, 85
  switch (lookAhead->tokenType)
  {
  case SB_TIMES:
    eat(SB_TIMES);
    compileFactor();
    compileTerm2();
    break;
  case SB_SLASH:
    eat(SB_SLASH);
    compileFactor();
    compileTerm2();
    break;
  default:
    break;
  }
}

void compileFactor(void)
{
  // TODO 86, 87, 88, 89
  switch (lookAhead->tokenType)
  {
  case TK_NUMBER: // unsignalconst
  case TK_CHAR:
  case TK_FLOAT:
  case TK_STRING:
    compileUnsignedConstant();
    break;
  case SB_LPAR:
    eat(SB_LPAR);
    compileExpression();
    eat(SB_RPAR);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    switch (lookAhead->tokenType)
    {
    case SB_LPAR:
      compileArguments();
      break;
    case SB_LBRACKET:
      compileIndexes();
      break;
    default:
      break;
    }
    break;
  default:
    error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileIndexes(void)
{
  // TODO 92, 93
  if (lookAhead->tokenType == SB_LBRACKET)
  {
    eat(SB_LBRACKET);
    compileExpression();
    eat(SB_RBRACKET);
    compileIndexes();
  }
}

int compile(char *fileName)
{
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;
}