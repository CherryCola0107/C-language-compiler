#ifndef __ITEM_H__
#define __ITEM_H__
#include <string.h>
using namespace std;
//项目

typedef struct Item{
    //产生式的下标，代表是第几个产生式
    int pId;
    //产生式中.的前一个符号的下标
    //比如E->C.D那么idx=0
    int idx;
} Item;

#endif
