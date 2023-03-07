
#ifndef __PRODUCTION_RULE_H__
#define __PRODUCTION_RULE_H__
#include <string.h>
using namespace std;
//用来存储产生式
typedef struct Production{
    //int id;
    //用来存储产生式左部
    string leftPart;
    //用来存储产生式右部
    string rightPart[10];
    //产生式右部尾元素的下标
    int rightPartLength;
} Production;

#endif
