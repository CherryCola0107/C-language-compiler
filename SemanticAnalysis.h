#ifndef __SEMANTICALANALYSIS_H__
#define __SEMANTICALANALYSIS_H__

#include "item.h"
#include "prodection_rule.h"
#include "state.h"
#include "analysis_table_cell.h"
#include "word.h"
#include "symbol.h"
#include "symbol_line.h"

// 获取一个临时变量
string getTempV();

// 产生中间代码
WORD createCode(int productionId, string leftPart, WORD* wordsInStack, int top);

// 打印中间代码
void printIntermediateCodeLine();

// 打印符号表（现在符号表有问题，所以暂时不用）
void printSymbolTable();

void setSymbolTable(SymbolLine* temp, int top);

#endif

