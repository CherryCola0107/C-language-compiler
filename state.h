
#ifndef __STATE_H__
#define __STATE_H__

#include "item.h"

#define MAX 10000

using namespace std;
//状态机的状态
typedef struct State{
    //状态的序号
    int id;
    //状态对应的项目集
    Item *items = (Item*)malloc(100 * sizeof(Item));
    int top = 0;
} State;

#endif
