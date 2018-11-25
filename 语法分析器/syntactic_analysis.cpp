#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

/*输入输出文件*/
char file_in[] = "./test1_Analysis.txt";
char file_out[] = "./test1_Analysis_aft.txt";
/*从文件中读取到的种别码、单词*/
int n = 0;
char str[100];
/*存储种别码及其相应单词*/
int code_num[1000] = {0};
string code_str[1000];
/*一些全局变量*/
int x = 0; // x是单词数组中的计数器
int sym = 52; // sym是该单词的种别码

/*----文法函数声明----*/   
void A(); // <主函数> -> int main()<语句块> 
void C(); // <函数> -> <所有类型> <函数名>()<语句块>
void D(); // <所有类型> -> void|int|double|char|bool
void S(); // <其他类型> -> void|int|double|char
void E(); // <函数名> -> ID
void B(); // <语句块> -> {(<语句块>|<语句串>)*}
void F(); // <语句串> -> <语句>(<语句>)*
void G(); // <语句> -> <声明语句>|<赋值语句>|<条件语句>|<循环语句>|<返回语句>
void O();
void R(); // <赋值表达式> -> ID = (<算术表达式>|<布尔表达式>) 
void H(); // <赋值语句> -> <赋值表达式>; 
void I(); // <条件语句> -> if(<布尔表达式>) (<语句块>|<语句>) else(<语句块>|<语句>)
          //             | if(<布尔表达式>) (<语句块>|<语句>) 
void J();  
void Q(); // <返回语句> -> return (<算术表达式>|<布尔表达式>);
void L(); // <布尔表达式> -> <布尔项>(||<布尔项>)*
void W(); // <布尔项> -> <布尔因子>(&&<布尔因子>)*
void X(); // <布尔因子> -> (<布尔表达式>)
          //             | <算术表达式> relop <算术表达式>
          //             | <ID|NUM>
void K(); // <算术表达式> -> <项>(+<项>)* | <项>(-<项>)*
void T(); // <项> -> <因子>(*<因子>)* | <因子>(/<因子>)*
void U(); // <因子> -> (<算术表达式>) | <ID|NUM> 
void P(); // <ID|NUM> -> ID|NUM|true|false

int getsym()
{
    return code_num[x++]; //读取下一个单词
}

int main()
{
    FILE* fp;
    if((fp=fopen(file_in, "r")) == NULL)
    {
        cout << "Open the file failed!" << endl;
        exit(0);
    }
    int k = 0;
    while(!feof(fp))
    {
        fscanf(fp, "%d %s", &n, str); //读取二元式
        code_num[k] = n; //存储种别码
        code_str[k] = str; //存储单词
        k++;
    }
    fclose(fp);

    sym = getsym(); //读取一个单词，得到其种别码
    cout << "语法分析：" << endl;
    cout << sym <<  endl;
   // A();

    return 0;
}
