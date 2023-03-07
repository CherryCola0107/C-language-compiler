#ifndef __SEMANTICALANALYSIS_H__
#define __SEMANTICALANALYSIS_H__

#include "item.h"
#include "prodection_rule.h"
#include "state.h"
#include "analysis_table_cell.h"
#include "word.h"
#include "symbol.h"
#include "symbol_line.h"

// ��ȡһ����ʱ����
string getTempV();

// �����м����
WORD createCode(int productionId, string leftPart, WORD* wordsInStack, int top);

// ��ӡ�м����
void printIntermediateCodeLine();

// ��ӡ���ű����ڷ��ű������⣬������ʱ���ã�
void printSymbolTable();

void setSymbolTable(SymbolLine* temp, int top);

#endif

