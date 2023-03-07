
#ifndef __ANALYSIS_TABLE_CELL_H__
#define __ANALYSIS_TABLE_CELL_H__

#include <string.h>
using namespace std;
//分析表的单元
typedef struct AnalysisCell{
    //op是操作
    //s是跳转 r是用第几个产生式归约
    //acc接收,*出错，gt(goto)是非终结符号的转换
    string op;
    //方向，s和gt是跳转的状态,r是用第几个产生式归约
    int direct;
} AnalysisCell;

#endif
