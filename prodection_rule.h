
#ifndef __PRODUCTION_RULE_H__
#define __PRODUCTION_RULE_H__
#include <string.h>
using namespace std;
//�����洢����ʽ
typedef struct Production{
    //int id;
    //�����洢����ʽ��
    string leftPart;
    //�����洢����ʽ�Ҳ�
    string rightPart[10];
    //����ʽ�Ҳ�βԪ�ص��±�
    int rightPartLength;
} Production;

#endif
