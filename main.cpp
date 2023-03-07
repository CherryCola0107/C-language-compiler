#include <iostream>
#include "LexicalAnalysis.h"
#include "GrammaticalAnalysis.h"
#include "fstream"
#include <iomanip>
#include <sstream>
#include <map>
#include <algorithm>
#include<vector>
using namespace std;
int top_lexicalData;

using namespace std;

class LexicalAnalyzer
{

public:
    LexicalAnalyzer();
    ~LexicalAnalyzer();
    void GetFileName(ifstream& filename);
    //逐行读入文件
    void InputFile(ifstream& filename);
    //细致分析，生成二元组并输出
    void AnalyzeToken(  vector <char>);
    //用于输出符号表
    void print();

    //判断函数，用于判断是否是该类型

	bool IsSymbol(char);
	bool IsWei(string);
	bool IsInclude(string);
	bool IsLeftBrace(string);
	bool IsRightBrace(string);
	bool IsSemicolon(string);
	bool IsPrintf(string);
	bool IsLeftBrackets(string);
	bool IsRightBrackets(string);
	bool IsOperator(char);
	bool IsComma(string);
	bool IsAddOperator(string);
	bool IsReduceOperator(string th);
	bool IsWhiteSpace(char);
	bool IsString(char);
	bool IsNotes(char ch);
	bool IsID(string th);
	bool IsReturn(string th);
	bool IsSolution(string th);
	bool IsKeywords(string);
    bool IsFor(string);
	bool IsWhile(string);
	bool IsIf(string);
	bool IsElse(string);
    bool IsMain(string);

private:
    //进行词法分析时进行暂存字符或字符串
    vector<char> token;
    //词法分析向量，用于存储词法分析成功后的结果
    vector<string> lexical_vector;
    //分析成功后的类型
    vector<string> finish_token;


};

LexicalAnalyzer::LexicalAnalyzer()
{

}

LexicalAnalyzer::~LexicalAnalyzer()
{

}

void LexicalAnalyzer::GetFileName(ifstream& filename)
{
	string file;
	file = "test.txt";
	filename.open(file);
	if (!filename)
	{
		cout << "文件名有误，请检查目录下是否有名为test.cpp的文件!";
	}
}

bool LexicalAnalyzer::IsSymbol(char ch)
{
	if (ch == '#' || ch == '(' || ch == ')' || ch == ',' || ch == '{' || ch == '}' || ch == '+' ||
		ch == '-' || ch == '*' || ch == '/' || ch == '&' || ch == '!' || ch == '|' || ch == ';')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsWei(string th)
{
	if (th == "#")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsInclude(string currentToken)
{
	if (currentToken =="include")
	{
		return true;
	}
	else
	{
		return false;
	}
}




bool LexicalAnalyzer::IsKeywords(string currentToken)
{
    if(currentToken=="main"||
       currentToken=="int"||
       currentToken=="\tint"||
       currentToken=="float"||
       currentToken=="\tfloat"||
       currentToken=="char"||
       currentToken=="printf"||
       currentToken=="return"||
       currentToken=="\treturn"||
       currentToken=="\tinclude"||
       currentToken=="include"||
       currentToken=="\tstdio,h"||
       currentToken=="stdio.h"||
       currentToken=="for"||
       currentToken=="\tfor"||
       currentToken=="while"||
       currentToken=="\twhile"||
       currentToken=="if"||
       currentToken=="\tif"||
       currentToken=="else"||
       currentToken=="\telse"
       )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::IsMain(string th)
{
	if (th == "main")
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool LexicalAnalyzer::IsLeftBrace(string th)
{
	if (th == "{")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsRightBrace(string th)
{
	if (th == "}")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsSemicolon(string st)
{
	if (st == ";")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsPrintf(string currentToken)
{
	if (currentToken == "printf")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsLeftBrackets(string th)
{
	if (th == "(")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsRightBrackets(string th)
{
	if (th == ")")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsOperator(char ch)
{
	if (ch == '=' || ch == '<' || ch == '>')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsComma(string th)
{
	if (th==",")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsAddOperator(string th)
{
	if (th=="+")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsReduceOperator(string th)
{
	if (th == "-")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsWhiteSpace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsString(char ch)
{
	if (ch == '"') {
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsNotes(char ch)
{
	if (ch=='/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsID(string th)
{
	if (isalpha(th[0]) && th != "if" && th != "function" &&th != "else" && th != "return" && th!= "var" &&th != "while")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsReturn(string th)
{
	if (th == "return")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsSolution(string th)
{
	if (th == "'a'")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LexicalAnalyzer::IsFor(string th)
{
	if (th == "for")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LexicalAnalyzer::IsWhile(string th)
{
	if (th == "while")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LexicalAnalyzer::IsIf(string th)
{
	if (th == "if")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool LexicalAnalyzer::IsElse(string th)
{
	if (th == "else")
	{
		return true;
	}
	else
	{
		return false;
	}
}
void LexicalAnalyzer::InputFile(ifstream& filename)
{
    //临时变量
	string currentToken;
	//暂时存储读取的每一行文件
	string readLine;
	char lookahead;

	//遇倒数值和字符时进行分析
	string myNumber = "";
	string myString = "";
	//遇倒空格时候的分析
	int temp;
	//逐行输入
	while (getline(filename,readLine))
	{

	    //逐字符遍历
		for (size_t i = 0; i < readLine.length(); i++)
		{


			temp = i;
			//赋值给临时字符
			lookahead = readLine[i];
			//将临时字符压入临时字符串token
			token.push_back(readLine[i]);
			//是否是空格、换行、制表符
			if (IsWhiteSpace(lookahead))
			{
			    //舍去空格，进行退栈
				token.pop_back();
				//token赋值给临时变量
				vector<char> temp = token;
				//进行细致分析
				AnalyzeToken(temp);
				token.clear();
			}
			//处理注释
			else if(IsNotes(lookahead))
			{
				token.pop_back();
				if (IsNotes(readLine[i+1]))
                    break;

			}
			//是否为各种符号，如果是用AnalyzeToken进行精细分析
			else if(IsSymbol(lookahead))
			{
			    //退栈
				token.pop_back();
				//分析
				AnalyzeToken(token);
				//清空
				token.clear();
				//此次读入的压入
				token.push_back(lookahead);
				//分析
				AnalyzeToken(token);
				//清空
				token.clear();
			}
			//检测是否为数字
			//如果标识符错误的如3bac，那么错误处理方式为分别读入
			else if (isdigit(lookahead)&&!isalpha(lookahead))
			{
			    //将这行的数字都读入
				while (isdigit(readLine[i+1]))
				{
					token.push_back(readLine[i + 1]);
					i++;
				}
				//将这些数字转成myNumber
				for (size_t i = 0; i < token.size(); i++)
				{
					myNumber += token[i];
				}
				//
				vector<string>::iterator it = find(lexical_vector.begin(), lexical_vector.end(), myNumber);
				//如果不是end得话说明里面有
				if (it == lexical_vector.end())
				{
					lexical_vector.push_back(myNumber);
					finish_token.push_back(myNumber);
				}
				cout << "<常数,  " <<"2,  "<< myNumber <<">"<< endl;
				myNumber = "";
				token.clear();
			}
			else if(IsString(lookahead))
			{
				token.pop_back();
				while (readLine[i+1]!='"')
				{
					token.push_back(readLine[i + 1]);
					i++;
				}
				for (size_t i = 0; i < token.size(); i++)
				{
					myString += token[i];
				}
				i++;
				cout << "<string," << myString << ">" << endl;
				myString = "";
				token.clear();
			}
			//判断是否是比较运算符
			else if (IsOperator(lookahead))
			{
				token.pop_back();
				//>=等运算符
				if (IsOperator(readLine[i+1]))
				{
					token.push_back(lookahead);
					token.push_back(readLine[i + 1]);
					i += 2;
					AnalyzeToken(token);
					token.clear();
				}

				else if (IsOperator(lookahead))
				{
					///*token.pop_back();*/
					//if (lookahead == '<' || '>')
					//{
					//	token.push_back(lookahead);
					//	AnalyzeToken(token);
					//	i++;
					//	token.clear();
					//}
					//else
					//{
						AnalyzeToken(token);
						if(lookahead=='=')
                        {
						cout << "<运算符,  "<<"12,  "<<lookahead << ">" << endl;
                        }
                        else if(lookahead=='>')
                        {
						cout << "<运算符,  "<<"13,  "<<lookahead << ">" << endl;
                        }
						else if(lookahead=='<')
                        {
						cout << "<运算符,  "<<"14,  "<<lookahead << ">" << endl;
                        }
						token.clear();
					//}
				}
			}
		}
	}
}
void LexicalAnalyzer::AnalyzeToken(vector<char> token)
{

    //临时变量
	string currenttoken;
	//每次找到置为0
	int FLAG = 1;
	//将token中所有字符组合成字符串存在currentToken里面
	for (size_t i = 0; i < token.size(); i++)
	{

		if (token[i] != '/t')
		{
			currenttoken += token[i];
		}
	}
	//临时迭代器用于便利currenttoken
	vector<string>::iterator it = find(lexical_vector.begin(), lexical_vector.end(), currenttoken);
	if (it != lexical_vector.end())
	{

	}
	//it=end说明lexical_vector里没有，要把它加进去
	else
	{
		lexical_vector.push_back(currenttoken);
		FLAG = 0;
	}
	if (IsKeywords(currenttoken))
    {
        if(currenttoken=="int")
        {
        cout<<"<关键字,  "<<"3,  "<<currenttoken<<">"<<endl;
        }
        else if(currenttoken=="char")
        {
        cout<<"<关键字,  "<<"4,  "<<currenttoken<<">"<<endl;
        }
        else if(currenttoken=="float")
        {
        cout<<"<关键字,  "<<"5,  "<<currenttoken<<">"<<endl;
        }
        else if(IsFor(currenttoken))
        {
        cout<<"<关键字,  "<<"7,  "<<currenttoken<<">"<<endl;
        }
        else if(IsWhile(currenttoken))
        {
        cout<<"<关键字,  "<<"8,  "<<currenttoken<<">"<<endl;
        }
        else if(IsIf(currenttoken))
        {
        cout<<"<关键字,  "<<"9,  "<<currenttoken<<">"<<endl;
        }
        else if(IsElse(currenttoken))
        {
        cout<<"<关键字,  "<<"10,  "<<currenttoken<<">"<<endl;
        }
        else if(IsMain(currenttoken))
        {
        cout<<"<关键字,  "<<"11,  "<<currenttoken<<">"<<endl;
        }
        else{
      cout<<"<关键字,"<<currenttoken<<">"<<endl;

        }
        if (FLAG==0)
		{
			finish_token.push_back("关键字");
		}
    }


	else if(IsSemicolon(currenttoken))
	{
		cout << "<分界符,  " <<"24,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("semicolon");
		}
	}
	else if(IsLeftBrackets(currenttoken))
	{
		cout << "<分界符,  " <<"20,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("leftbrackets");
		}
	}
	else if (IsRightBrackets(currenttoken))
	{
		cout << "<分界符,  " <<"21,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("rightbrackets");
		}
	}
	else if (IsLeftBrace(currenttoken))
	{
		cout << "<分界符,  " <<"22,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("leftbrace");
		}
	}
	else if (IsRightBrace(currenttoken))
	{
		cout << "<分界符,  " <<"23,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("rightbrace");
		}
	}
	else if(IsComma(currenttoken))
	{
		cout << "<comma," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("comma");
		}
	}
	else if(IsAddOperator(currenttoken))
	{
		cout << "<运算符,  " <<"15,  " <<currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("addoperator");
		}
	}
	else if (IsReduceOperator(currenttoken))
	{
		cout << "<运算符,  " <<"16,  "<< currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("reduceoperator");
		}
	}

	else if(IsID(currenttoken))
	{
		cout << "<标识符,  " <<"1,  " << currenttoken<<">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back(currenttoken);
		}
	}
	else if (IsWei(currenttoken))
	{
		cout << "<宏定义符号," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("specialsign");
		}
	}
	else if (IsSolution(currenttoken))
	{
		cout << "<words," << currenttoken << ">" << endl;
		if (FLAG==0)
		{
			finish_token.push_back(currenttoken);
		}
	}
	}

void LexicalAnalyzer::print()
{
	int count = 0;
	cout << "--------------------------符号表--------------------------" << endl;
	vector<string>::iterator tmp = lexical_vector.begin();
	vector<string>::iterator tmp2 = finish_token.begin();
	tmp += 1;
	for (;tmp != lexical_vector.end(); tmp++,tmp2++)
	{
		count++;
		cout << setw(3) << count << " " << setw(10) << *tmp  << setw(15)<<*tmp2<<endl;
	}
}
int main()
{
    cout << "-------------------- 词法分析----------------------------" << endl;
    char test[] = "while a<3 a=a+1#";
    scan(test);
    printToken();
    cout << "-------------------- 语法分析----------------------------" << endl;
    WORD A[100];
    A[0].key="while";
    //A[0].code=4;
    A[1].key ="id";
    //A[1].code=300;
    A[2].key="<";
    //A[2].code=32;
    A[3].key="num";
    //A[3].code=100;
    A[4].key="id";
    //A[4].code=300;
    A[5].key="=";
    //A[5].code=26;
    A[6].key="id";
    //A[6].code=300;
    A[7].key="+";
    //A[7].code=21;
    A[8].key="num";
    //A[8].code=100;
    cout<<A[1].code<<endl;
    cout<<A[1].key<<endl;
    cout<<getTop()<<endl;




   // grammaticalAnalysis(getToken(), getTop());
   // grammaticalAnalysis_test2(getToken(),getTop());
    grammaticalAnalysis_test3(A,getTop());

    return 0;
}
