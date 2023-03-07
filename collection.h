
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

using namespace std;
//first集和follow集使用该结构体
//vts是集合对应的终结符下标
//top是vts的数组尾
typedef struct Collection{
    int* vts = (int*)malloc(100 * sizeof(int));
    int top = 0;
} Collection;

#endif
