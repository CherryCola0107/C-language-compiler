
#ifndef __ANALYSIS_TABLE_CELL_H__
#define __ANALYSIS_TABLE_CELL_H__

#include <string.h>
using namespace std;
//������ĵ�Ԫ
typedef struct AnalysisCell{
    //op�ǲ���
    //s����ת r���õڼ�������ʽ��Լ
    //acc����,*����gt(goto)�Ƿ��ս���ŵ�ת��
    string op;
    //����s��gt����ת��״̬,r���õڼ�������ʽ��Լ
    int direct;
} AnalysisCell;

#endif
