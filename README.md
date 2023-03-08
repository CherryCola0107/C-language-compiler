# C-language-compiler
C language compiler
完成了词法分析和slr1语法分析
# C编译器

**自顶向下** 通过试探来构造输入串

LL(1)

**自底向上** 将输入串还原成最初状态

算符优先分析法： 根据运算符的优先关系进行规约

LR(0)分析法：

​		action表：遇到终结符移进/归约后到什么状态

​		goto表：遇到非终结符goto到什么状态

会产生移进归约冲突，因为它不会根据后面的符号来决定动作



### analysis_table_cell.h

op是操作（s是状态跳转；r是用第几个产生式进行归约；acc是接收；*是出错；gt是非终结符的状态转换），direct是方向（s和gt时是跳转到的状态，r时是归约用第几个产生式）

![image](https://user-images.githubusercontent.com/60459025/223599184-329fdc07-6ef0-4876-895b-738939e85a6c.png)

### collection.h

follow集和first集都是用的这个结构体，vts是集合对应的终结符id（下标），top是vts的数组尾

![image](https://user-images.githubusercontent.com/60459025/223599390-8fe273fd-0887-465c-a0ea-ec9714f87397.png)

### prodection_rule.h

production是产生式，leftPart是产生式左部，rightPart是产生式右部的符号数组，rightPartLength是对应符号数组的数组尾。如S->AB，leftPart是S，rightPart[0]是A，rightPart[1]是B，rightPartLength是1（尾部下标）。	

![image](https://user-images.githubusercontent.com/60459025/223599439-99f15bca-5230-4483-b45b-5adcf7ca12b1.png)

### item.h

item是项目，简单来说就是 E->A.B 这样的，pId是对应产生式的id（下标），idx是 . 的前一个符号的下标，也就是在分析栈中最后一个元素的下标，假设 E->AB 是第3号产生式，那 E->A.B 对应的 item 是 pId=3，idx=0。需要注意的是 E->.AB 对应的idx是-1。

![image](https://user-images.githubusercontent.com/60459025/223600335-aea97c5d-173e-414d-93bf-62c2957afe9e.png)

### state.h

就是状态机的每个状态。id暂时没有用到，是状态的序号。item是s状态对应的项目集，top是items的尾部下标

![image](https://user-images.githubusercontent.com/60459025/223600417-40d1221c-8e6d-4de7-9f7e-06a01874abc3.png)

### 项目集闭包 CLOSURE()

A->B和B->b（大写是非终结符，小写是终结符），则A->.B的闭包是A->.B和B->.b 。

用栈来实现：压最初项目，出栈判断是否能拓展，能把右边第一个是终结符的加入闭包，把右边是非终结符能拓展的压入栈 循环，直到栈空

```c++
State CLOSURE(State target){
    //newState是最后返回的状态情况
    State newState;
    newState.items = copyItems(target);
    newState.top = target.top;
    //newState.id = target.id + 1;

    // itemStack是作为一个栈来用，一直找有没有新的项目是在这个状态里的 判断是否停止
    //把状态里的item全都拷贝到itemStack里
    Item *itemStack = copyItems(target);  // 待处理item栈
    int stackTop = target.top;  // 栈顶

    while(stackTop != 0){
        // 出栈
        stackTop--;
        //一个项目.前面一个符号的下标
        int idx =  itemStack[stackTop].idx;
        //这个项目对应的产生式是tempPro
        Production tempPro = productions[itemStack[stackTop].pId];
        // 判断该item是否还能扩展
        if(idx < tempPro.rightPartLength){
            string tempVT = tempPro.rightPart[idx + 1];  // 点右边的第一个字符
            if(isNonTerminal(tempVT)){  // 如果是非终结符
                //得到.右边第一个字符是非终结符 其作为产生式左部的产生式的id
                int* pId = existLeftPro(tempVT);
                for(int i = 0; i < productionTop; i++){
                    //得到一个产生式的id
                    int id = *(pId + i);

                    //id是有效的 并且 不在此状态现有的产生式里面
                    //-1的意思是看是不是E->.AB 因为新的项目.需要是从头开始的
                    if(id != -1 && !itemRepeat(newState, id, -1)){
                        // 添加新的item，点标在最左边
                        newState.items[newState.top].pId = id;
                        newState.items[newState.top].idx = -1;
                        // 入栈
                        itemStack[stackTop++] = newState.items[newState.top];
                        newState.top++;
                    }
                }
            }
        }
    }

    return newState;
}

```

### GOTO()

就是给定一个状态和下一个要识别的符号，移动 . 并计算新的闭包。举个简单的例子，一个状态s的项目集是S->.B与S->A.CD，如果GOTO(s, C),得到的结果就是 S->AC.D 的闭包。

```c++
State GOTO(State state, string x){
    State j;
    j.top = 0;
    //cout << "q" << endl;
    for(int i = 0; i < state.top; i++){
        int pId = state.items[i].pId;
        int idx = state.items[i].idx;
        if(productions[pId].rightPart[idx + 1].compare(x) == 0){  // 如果下一个符号是目标符号
            j.items[j.top].idx = idx + 1;
            j.items[j.top].pId = pId;
            j.top++;
        }
    }
    //cout << "w" << endl;

    return CLOSURE(j);
}
```

### 项目集规范族getCanonicalCollection()

将最初的项目的闭包作为起始状态

出栈，遍历终结符和非终结符获取下一状态，获取了之后入栈，循环这个过程，直到栈空

```c++
// 获取项目集规范族
void getCanonicalCollection(){
    // 获取拓广文法新加产生式的项目（如：S'->.S）
    firstState.items[0].pId = 0;
    firstState.items[0].idx = -1;
    firstState.top = 1;
    // 获取该项目的闭包作为初始状态
    CC[CCTop++] = CLOSURE(firstState);

    State stateStack[MAX];
    //初始状态
    stateStack[0] = CC[CCTop - 1];
    int stackTop = 1;

    while(stackTop != 0){
        // 出栈
        stackTop--;
        //取得栈顶状态
        State topState = stateStack[stackTop];
        // 对非终结符
        for(int i = 0; i < vtnTop; i++){
            State temp = GOTO(topState, vtn[i]);
            //状态不为空并且不在现有的状态中
            if(temp.top !=0 && !checkItemInCC(temp)){  // 一个状态不能为空，如当GOTO(i, "#")时
                stateStack[stackTop++] = temp;
                //状态增加
                CC[CCTop++] = temp;
            }
        }
        // 对终结符
        for(int i = 0; i < terminalTop; i++){
            State temp = GOTO(topState, terminal[i]);
            if(temp.top !=0 && !checkItemInCC(temp)){
                stateStack[stackTop++] = temp;
                CC[CCTop++] = temp;
            }
        }
    }
}
```

### FIRST

遍历产生式，如果产生式右部是终结符，就将该终结符加入First集，如果是非终结符，就将该非终结符的First集加入该First集；

注：如果产生式右部是自己的话就跳过 不然会死循环

```c++
// 获取并产生某一非终结符的FIRST集
Collection getFIRST(int vId){
    // 如果该first集已经有了，就直接返回
    if(FIRST[vId].top != 0){
        return FIRST[vId];
    }
    // 计算其first集
    for(int i = 0; i < productionTop; i++){
        // 如果产生式的左部是v
        if(productions[i].leftPart.compare(vtn[vId]) == 0){
            // 如果产生式右部的第一个符号是自己，要跳过不然就是将FIRST[X]放到FIRST[X]中，会死循环
            if(productions[i].rightPart[0].compare(vtn[vId]) == 0){
                continue;
            }
            // 如果产生式右部第一个符号是终结符，就把该终结符加进去
            int id = getTerminalId(productions[i].rightPart[0]);
            if(id != -1){
                if(!checkCollection(FIRST[vId], id)){
                    FIRST[vId].vts[FIRST[vId].top++] = id;
                }
            } else {
                id = getVtnId(productions[i].rightPart[0]);
                if(id == -1){
                    cout << "cant find symbol [" << productions[i].rightPart[0] << "]" << endl;
                    return FIRST[vId];
                }
                // 产生式右部第一个符号是非终结符，将它的first集加入
                addCollection(vId, getFIRST(id), false);
            }
        }
    }

    return FIRST[vId];
}
```

### FOLLOW

- **FOLLOW**（A）：紧跟在非终结符A后边的终结符α的集合

  遍历每个产生式，如果右侧有非终结符是待求的A且在产生式最后就把左侧的follow集加入到A的follow集中

  ​							如果右侧有非终结符是待求的A且下一个符号是终结符，就把该终结符加入A的follow集中

  ​							如果右侧有非终结符是待求的A且下一个符号是非终结符，就把该非终结符的first集加入A的follow集中

  注：如果产生式最右部是自己的话就跳过 不然会死循环

```c++
// 获取follow集
Collection getFOLLOW(int vId){
    // 如果该follow集已经有了，就直接返回
    if(FOLLOW[vId].top != 0){
        return FOLLOW[vId];
    }
    if(vId == 0){
        // 扩广文法新加的产生式的右部自带 #，如 S' -> S 中的 S
        FOLLOW[0].vts[FOLLOW[0].top++] = getTerminalId("#");
    }
    // 构建follow集
    for(int i = 1; i < productionTop; i++){
        for(int j = 0; j <= productions[i].rightPartLength; j++){
            if(vtn[vId].compare(productions[i].rightPart[j]) == 0){
                int id = -1;
                // 如果该非终结符在产生式右部最后
                if(j == productions[i].rightPartLength){
                    // 右部最后一个符号不能是自己，不然会死循环
                    if(vtn[vId].compare(productions[i].leftPart) == 0){
                        continue;
                    }
                    id = getVtnId(productions[i].leftPart);
                    if(id == -1){
                        cout << "unknown non-terminal v: [" << productions[i].leftPart << "]" << endl;
                        return FOLLOW[vId];
                    }
                    // 把产生式左部非终结符的follow集加入
                    addCollection(vId, getFOLLOW(id), true);
                } else if((id = getTerminalId(productions[i].rightPart[j + 1])) != -1) {
                    // 如果该非终结符的下一个符号是终结符，直接加到follow集中
                    if(!checkCollection(FOLLOW[vId], id)){
                        FOLLOW[vId].vts[FOLLOW[vId].top++] = id;
                    }
                } else if((id = getVtnId(productions[i].rightPart[j + 1])) != -1){
                    // 如果该非终结符下一个符号是另一个非终结符，就把该非终结符的follow集加入
                    addCollection(vId, getFIRST(id), true);
                }
            }
        }
    }

    return FOLLOW[vId];
}
```

### 构建分析表

遍历状态中的每个项目，如果下一个符号是非终结符且项目到尾部，获取goto到的下一个状态id并填goto表

​										如果下一个符号是终结符且项目到尾部，获取下一个状态id，添action表，并且动作是“s”

​										如果项目到尾部，且是第一个项目那action表“acc”

​										如果项目到尾部，且不是第一个项目，如果下一个非终结符是follow(A),action对应位置"r"

```c++
// 构造分析表
void developAnalysisTable(){
    // 遍历状态
    for(int i = 0; i < CCTop; i++){
        // 当前状态
        State tempState = CC[i];
        // 遍历状态中的项目
        for(int j = 0; j < tempState.top; j++){
            // 当前项目
            Item tempItem = tempState.items[j];
            // action 与 goto
            if(tempItem.idx < productions[tempItem.pId].rightPartLength){
                string tempEle = productions[tempItem.pId].rightPart[tempItem.idx + 1];
                // 终结符
                int eleId = getTerminalId(tempEle);
                // 如果不是终结符，填goto表
                if(eleId == -1){
                    eleId = getVtnId(tempEle);
                    if(eleId == -1){
                        cout << "cant recognize the symbol [" << tempEle << "]" << endl;
                        return;
                    }
                    // 获取下一个状态
                    State nextState = GOTO(tempState, tempEle);
                    // 获取状态id
                    int nextStateId = getStateId(nextState);
                    if(nextStateId == -1){
                        printf("cant get state id!!!!!!!!!!!\n");
                        return;
                    }
                    // 填表
                    gotoTable[i][eleId].direct = nextStateId;
                    gotoTable[i][eleId].op = "gt";
                } else {
                    // action 表
                    // 获取下一个状态
                    State nextState = GOTO(tempState, tempEle);
                    // 获取状态id
                    int nextStateId = getStateId(nextState);
                    if(nextStateId == -1){
                        printf("cant get state id!!!!!!!!!!!\n");
                        return;
                    }
                    // 填表
                    actionTable[i][eleId].direct = nextStateId;
                    actionTable[i][eleId].op = "s";
                }
            } else {
                // acc
                if(tempItem.pId == 0 && tempItem.idx == 0){
                    actionTable[i][getTerminalId("#")].op = "acc";
                } else {
                    // 归约
                    for(int m = 0; m < terminalTop; m++){
                        //
                        // 这里是是否是SLR的关键，SLR需要判断下一个非终结符是否在该变量的follow集中，LR就不需要，直接true就行
                        //
                        if(inFOLLOW(productions[tempItem.pId].leftPart, m)){
                        //if(true){
                            actionTable[i][getTerminalId(terminal[m])].op = "r";
                            actionTable[i][getTerminalId(terminal[m])].direct = tempItem.pId;
                        }
                    }
                }
            }
        }
    }
}
```

### 构建分析表

根据分析表决定何时移入，何时规约
