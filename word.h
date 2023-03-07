
#ifndef __WORD_H__
#define __WORD_H__
#include <string.h>
using namespace std;

typedef struct WORD{
    int code;
    string key;
    string addr = "#";
    string position;
    int lineNum;
    string extra;
    bool variable;
} WORD;

#endif

