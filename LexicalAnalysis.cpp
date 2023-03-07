
#include <iostream>
#include <string.h>
#include "word.h"
#include "symbol.h"
#include "symbol_line.h"

using namespace std;

#define KEYWORD_NUM 8

WORD token[100];
int top = 0;
int line = 1;

SymbolLine symbolTableL[100];
int tableTopL = 0;

char keywords[KEYWORD_NUM][20] = {"if", "else", "main", "while", "int", "return", "double", "boolean"};

WORD* getToken(){
    return token;
}

SymbolLine* getLSymbolTable(){
    return symbolTableL;
}

int getLSymbolTableSize(){
    return tableTopL;
}

void printSymbolTableL(){
    cout << "-----------------------符号表--------------------------" << endl;
    cout << "id    " << "name     " << "addr     " << endl;
    for(int i = 0; i < tableTopL; i++){
        cout << i << "     " << symbolTableL[i].value << "        " << symbolTableL[i].addr << endl;
    }
}

int getTop(){
    return top;
}

bool digit(char target){
    if(target >= '0' && target <= '9'){
        return true;
    }
    return false;
}

bool letter(char target){
    if(target >= 'a' && target <= 'z' || target >= 'A' && target <= 'Z' || target == '_'){
        return true;
    }
    return false;
}

int keyword(char target[]){
    for(int i = 0; i < KEYWORD_NUM; i++){
        if(strcmp(target, keywords[i]) == 0){
                //cout << target << endl;
            return i + 1;
        }
    }
    return -1;
}

bool point(char target){
    if(target == '.'){
        return true;
    }
    return false;
}

void deleteBlank(char *target){
    while(*target == ' ' || *target == 10 || *target == '\n'){
        if(*target == '\n'){
            line++;
        }
        target++;
    }
}

void addNewSymbolLine(string target){
    for(int i = 0; i < tableTopL; i++){
        if(symbolTableL[i].value.compare(target) == 0){
            return;
        }
    }

    symbolTableL[tableTopL].addr = to_string(tableTopL);
    symbolTableL[tableTopL].type = "variables";
    symbolTableL[tableTopL].value = target;
    symbolTableL[tableTopL].vType = "unknown";
    tableTopL++;
}

// 记录单词位置
void savePosition(){
    int leftTop = (top > 10) ? 10 : top;
    // 记录所在行数
    token[top - 1].lineNum = line;
    // 最多记录附近单词
    for(int i = 0; i < leftTop - 1; i++){
        if(token[top - leftTop + i].lineNum != token[top - 1].lineNum){
            continue;
        }
        token[top - 1].position = token[top - 1].position + " " + token[top - leftTop + i].extra;
    }
    // 记录当前单词
    token[top - 1].position = token[top - 1].position + " <" + token[top - 1].extra + ">";
}

void addToken(int code, char* word){
    WORD w;
    w.code = code;
    w.key = string(word);
    w.extra = string(word);  // 变量要用到
    w.lineNum = line;
    token[top++] = w;
    // 记录单词位置
    savePosition();
}

void addTokenM(int code, char* word, char* addr, bool v){
    WORD w;
    w.code = code;
    w.addr = addr;
    w.key = string(word);
    w.variable = v;
    w.lineNum = line;

    w.extra = string(addr);

    token[top++] = w;

    savePosition();
}

void addOPToken(int code, char* word){
    WORD w;
    w.code = code;
    w.key = string(word);
    w.extra = string(word);  // 运算符要用到
    w.lineNum = line;
    token[top++] = w;

    savePosition();
}

void printToken(){
    for(int i = 0; i < top; i++){
        cout << "(" << token[i].code << ", " << token[i].key << ", " << token[i].addr << ")" << endl;
    }
}

void scan(char *words){
    while(1){
        // 删除空格和换行符
        deleteBlank(words);
        // # 截止
        if(*words == '#'){
            break;
        }
        // 注释
        if(*words == '/'){
            if(*(words + 1) == '/'){
                words++;
                words++;
                while(*words != '\n'){
                    words++;
                }
                line++;
                addToken(200, "//");
                words++;
            } else if(*(words + 1) == '*'){
                words++;
                words++;
                while(*words != '*' && *(words + 1) != '/'){
                    if(*words == '\n'){
                        line++;
                    }
                    words++;
                }
                addToken(201, "/**/");
                words++;
                words++;
            }
        }
        // 字母
        if(letter(*words)){
            int i = 0;
            char temp[500] = "1";
            while(letter(*words) || digit(*words)){
                temp[i] = *words;
                //cout << temp[i] << " " << endl;
                words++;
                i++;
            }
            // 看是否为关键字
            int code = keyword(temp);
            //cout << temp << " " << code << endl;
            if(code != -1){
               addToken(code, temp);
            } else {
                // 变量
               addTokenM(300, "id", temp, true);
               // 符号表
               addNewSymbolLine(string(temp));
            }
        } else if(digit(*words)){
            int i = 0;
            char temp[500] = "0";
            bool hasPoint = true;
            while(digit(*words) || point(*words)){
                if(point(*words)){
                    if(hasPoint){
                        hasPoint = false;
                    } else {
                        temp[i] = *words;
                        words++;
                        i++;
                        addTokenM(100, "num", temp, false);
                        cout << "FloatError in line " << token[top - 1].lineNum << ":" << token[top - 1].position << endl;
                        exit(0);
                    }
                }
                temp[i] = *words;
                words++;
                i++;
            }
            if(point(*(words - 1))){
                cout << "This is error in syntax " << string(temp) << endl;
                return;
            }
            addTokenM(100, "num", temp, false);
        } else {
            switch (*words){
                case '+':
                    addOPToken(ADD, "+");
                    break;

                case '-':
                    addOPToken(SUBTRACT, "-");
                    break;

                case '*':
                    addOPToken(MULTIPLY, "*");
                    break;

                case '/':
                    addOPToken(DIVIDE, "/");
                    break;

                case '=':
                    if(*(words + 1) == '='){
                        addOPToken(EQ_TWO, "==");
                        words++;
                    } else {
                        addOPToken(EQ, "=");
                    }
                    break;

                case '{':
                    addOPToken(L_BRACE, "{");
                    break;

                case '}':
                    addOPToken(R_BRACE, "}");
                    break;

                case '>':
                    if(*(words + 1) == '='){
                        addOPToken(BIGGER_EQ, ">=");
                        words++;
                    } else {
                        addOPToken(BIGGER, ">");
                    }
                    break;

                case '<':
                    if(*(words + 1) == '='){
                        addOPToken(SMALLER_EQ, "<=");
                        words++;
                    } else {
                        addOPToken(SMALLER, "<");
                    }
                    break;

                case '(':
                    addOPToken(L_PARENTHESIS, "(");
                    break;

                case ')':
                    addOPToken(R_PARENTHESIS, ")");
                    break;

                case ';':
                    addOPToken(SEMICOLON, ";");
                    break;

                cout << "There is error in symbol " << *words << endl;
            }
            words++;
        }
    }
}

//int main()
//{
//    char test[] = "/* 注释 */ int main() \n // hhh \n { int a = 123.60 + 23; if ( a == 1 ) { return;}#";
//    scan(test);
//    printToken();
//    return 0;
//}



