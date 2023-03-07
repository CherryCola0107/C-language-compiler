#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdio>
#include "item.h"
#include "prodection_rule.h"
#include "state.h"
#include "analysis_table_cell.h"
#include "word.h"
#include "symbol.h"
#include "collection.h"
#include "intermediate_code.h"
#include "symbol_line.h"

int tempNum = 0;  // ��ʱ���������

int lineNum = 100;  // �м�������

// �м����
IntermediateCodeLine lines[1000];  // �м����������
int lineTop = 0;  // ����β

// ���ű�
SymbolLine symbolTable[1000];  // ���ű�
int tableTop = 0;  // ���ű�β

// �ʷ�������ȡ�ķ��ű�
SymbolLine *symbolTableFromL;  // ���ű�
int tableTopFromL = 0;  // ���ű�β

// ѭ��ջ
// ջ����¼�������ڲ��ѭ����ʼʱ���м�����������е��±�
int loopStack[100];  // ѭ��ջ
int loopStackTop = 0;  // ѭ����Ӧ���м�����±�

// ���ôʷ�������ȡ�ķ��ű�
void setSymbolTable(SymbolLine *temp, int top){
    symbolTableFromL = temp;
    tableTopFromL = top;
}

// ��ȡһ����ʱ����
string getTempV(){
    return "sys_temp" + to_string(tempNum++);
}

// ��ȡһ�������ڷ��ű��е��±�
int getSymbolIdx(string sl){
    for(int i = 0; i < tableTop; i++){
        if(symbolTable[i].addr.compare(sl) == 0){
            return i;
        }
    }

    return -1;
}

// ������ͼ����ԣ������ظ��߼�������
string checkType(string addr1, string addr2){
    // Ĭ����int����
    string type1 = "int";
    string type2 = "int";
    // ���ݱ�����addr1��addr2�ӷ��ű���Ӧ����������
    // ������ڷ��ű��У��Ǿ��������ˣ�Ĭ���������ʼ����int
    int id1 = getSymbolIdx(addr1);
    if(id1 != -1){
        type1 = symbolTable[id1].type;
    }
    int id2 = getSymbolIdx(addr2);
    if(id2 != -1){
        type2 = symbolTable[id2].type;
    }

    // �����һ����bool�����޷����㣨��Ϊ������ֻ������int��double��boolean�������ͣ�
    if(type1.compare("boolean") == 0 || type2.compare("boolean") == 0){
        cout << "throw error for " << addr1 << "(" << type1 << ") cant compute with " << addr2 << "(" << type2 << ")..." << endl;
        exit(0);
    }

    // һ��double��int���м��㣬����ת����double����
    if(type1.compare("double") == 0 || type2.compare("double") == 0){
        return "double";
    } else {
        return "int";
    }
}

// ����ʽ18��Ӧ�������ӳ���
void SemanticSubroutine_18(WORD target){
    //symbolTable[tableTop].addr = target.addr;
    //symbolTable[tableTop].type = "variable";
    //symbolTable[tableTop].value = "0";
    //tableTop++;
}

// ����ʽ13��Ӧ�������ӳ���
WORD SemanticSubroutine_13(WORD v1, WORD op, WORD v2, string leftPart){
    // ���ͼ��
    string type = checkType(v1.addr, v2.addr);

    WORD result;
    // ��ȡ��ʱ����
    result.addr = getTempV();
    result.key = leftPart;
    // ����������
    // �������������
    int v1_d = -1;
    int v2_d = -1;
    // �ж�v1�Ƿ�Ϊ���ű��еı������ǵĻ��ӷ��ű���ȡֵ
    int id = getSymbolIdx(v1.addr);
    if(id == -1){
        v1_d = atoi(v1.addr.c_str());
    } else {
        v1_d = atoi(symbolTable[id].value.c_str());
    }
    // �ж�v2�Ƿ�Ϊ���ű��еı������ǵĻ��ӷ��ű���ȡֵ
    id = getSymbolIdx(v2.addr);
    if(id == -1){
        v2_d = atoi(v2.addr.c_str());
    } else {
        v2_d = atoi(symbolTable[id].value.c_str());
    }

    // ���з������㣨��extra�б�����������ţ�
    if(op.extra.compare("+") == 0){
        lines[lineTop].code = result.addr + " = " + v1.addr + " + " + v2.addr;
        lines[lineTop].lineNum = lineNum;
        lineTop++;
        lineNum++;
        result.variable = true;
        // ��ʱ����������ű�
        symbolTable[tableTop].addr = result.addr;
        symbolTable[tableTop].type = type;
        symbolTable[tableTop].value = v1_d + v2_d;
        tableTop++;
    }

    if(op.extra.compare("-") == 0){
        lines[lineTop].code = result.addr + " = " + v1.addr + " - " + v2.addr;
        lines[lineTop].lineNum = lineNum;
        lineTop++;
        lineNum++;
        result.variable = true;
        // ��ʱ����������ű�
        symbolTable[tableTop].addr = result.addr;
        symbolTable[tableTop].type = type;
        symbolTable[tableTop].value = v1_d - v2_d;
        tableTop++;
    }

    if(op.extra.compare("*") == 0){
        lines[lineTop].code = result.addr + " = " + v1.addr + " * " + v2.addr;
        lines[lineTop].lineNum = lineNum;
        lineTop++;
        lineNum++;
        result.variable = true;
        // ��ʱ����������ű�
        symbolTable[tableTop].addr = result.addr;
        symbolTable[tableTop].type = type;
        symbolTable[tableTop].value = v1_d * v2_d;
        tableTop++;
    }

    if(op.extra.compare("/") == 0){
        lines[lineTop].code = result.addr + " = " + v1.addr + " / " + v2.addr;
        lines[lineTop].lineNum = lineNum;
        lineTop++;
        lineNum++;
        result.variable = true;
        // ��ʱ����������ű�
        symbolTable[tableTop].addr = result.addr;
        symbolTable[tableTop].type = type;
        symbolTable[tableTop].value = v1_d / v2_d;
        tableTop++;
    }

    return result;
}

// ����ʽ19��Ӧ�������ӳ���
void SemanticSubroutine_19(WORD v1, WORD v2, WORD type){
    //cout << v2.key << "--" << v1.key << endl;
    // �жϱ����Ƿ��ظ�
    if(-1 != getSymbolIdx(v1.addr)){
        cout << "throw error for multi declare of variable [" << v1.addr << "]..." << endl;
        exit(0);
    }
    // ��������ӵ����ű�
    symbolTable[tableTop].addr = v1.addr;
    // �������ͣ�int��double��boolean��������extra��
    symbolTable[tableTop].type = type.extra;
    // ������ֵ
    string value;
    int id = getSymbolIdx(v2.addr);
    if(id == -1){
        value = v2.addr;
    } else {
        value = symbolTable[id].value;
    }
    symbolTable[tableTop].value = value;
    tableTop++;


    // ����ʷ����������ķ��ű�
    for(int i = 0; i < tableTopFromL; i++){
        if(symbolTableFromL[i].value.compare(v1.addr) == 0){
            symbolTableFromL[i].vType = type.extra;
        }
    }



    // �м����
    lines[lineTop].code = v1.addr + " = " + v2.addr;
    lines[lineTop].lineNum = lineNum;
    lineTop++;
    lineNum++;
}

// ����ʽ6��Ӧ�������ӳ���
void SemanticSubroutine_6(){
    // �ճ�һ��������ѭ���������Լ��ʱ����
    lines[lineTop].code = "blank";
    lines[lineTop].lineNum = lineNum;

    // ��¼���ڲ�ѭ����ʼ������
    loopStack[loopStackTop] = lineTop;
    loopStackTop++;
    lineNum++;
    lineTop++;
}

// ����ʽ1��Ӧ�������ӳ���
void SemanticSubroutine_1(WORD t){
    // �ҵ����ڲ�ѭ����ʼ������
    int startLine = loopStack[--loopStackTop];
    // ���ϵ����ճ���������������ת���
    lines[startLine].code = "if not " + t.extra + " then goto " + to_string(lineNum + 1);

    // �������ص�while�ж��������м����
    lines[lineTop].code = "goto " + to_string(lines[startLine].lineNum);
    lines[lineTop].lineNum = lineNum;
    lineTop++;
    lineNum++;
}

// ����ʽ9��Ӧ�������ӳ���
WORD SemanticSubroutine_9(WORD v1, WORD op, WORD v2, string leftPart){
    // ���ͼ��
    checkType(v1.addr, v2.addr);

    WORD result;
    result.key = leftPart;
    // ��¼�ж����������ϵ����ճ���������������ת����ʱ��Ҫ�õ�
    result.extra = v1.addr + " " + op.extra + " " + v2.addr;
    return result;
}

// ��������������м����
WORD createCode(int productionId, string leftPart, WORD* wordsInStack, int top){
    // ��װ���ص��ַ�
    WORD result;
    result.key = leftPart;
    result.addr = wordsInStack[top - 1].addr;
    result.extra = wordsInStack[top - 1].extra;

    // ִ�������ӳ���
    if(productionId == 18){
        SemanticSubroutine_18(wordsInStack[top - 1]);
    }

    if(productionId == 13){
        result = SemanticSubroutine_13(wordsInStack[top - 3], wordsInStack[top - 2], wordsInStack[top - 1], leftPart);
    }

    if(productionId == 19){
        SemanticSubroutine_19(wordsInStack[top - 4], wordsInStack[top - 2], wordsInStack[top - 5]);
    }

    if(productionId == 6){
        SemanticSubroutine_6();
    }

    if(productionId == 1){
        SemanticSubroutine_1(wordsInStack[top - 5]);
    }

    if(productionId == 9){
        result = SemanticSubroutine_9(wordsInStack[top - 3], wordsInStack[top - 2], wordsInStack[top - 1], leftPart);
    }

    return result;

}

// ��ӡ�м����
void printIntermediateCodeLine(){
    cout << "------------------�м����--------------------" << endl;
    for(int i = 0; i < lineTop; i++){
        cout << lines[i].lineNum << " : " << lines[i].code << endl;
    }
}

// ��ӡ���ű�
void printSymbolTable(){
    cout << "-----------------------���ű�--------------------------" << endl;
    cout << "id    " << "name     " << "addr     " << "type" << endl;
    for(int i = 0; i < tableTopFromL; i++){
        cout << i << "     " << symbolTableFromL[i].value << "        " << symbolTableFromL[i].addr << "        " << symbolTableFromL[i].vType << endl;
    }
}



