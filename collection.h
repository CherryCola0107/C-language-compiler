
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

using namespace std;
//first����follow��ʹ�øýṹ��
//vts�Ǽ��϶�Ӧ���ս���±�
//top��vts������β
typedef struct Collection{
    int* vts = (int*)malloc(100 * sizeof(int));
    int top = 0;
} Collection;

#endif
