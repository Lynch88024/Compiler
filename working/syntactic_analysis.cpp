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
/*四元式*/
string Quadruples[500][4]; 
int row = 0;

/*----文法函数声明----*/   
void A(); // <主函数> -> int main()<语句块> 
void C(); // <函数> -> <所有类型> <函数名>()<语句块>
void D(); // <所有类型> -> void|int|double|char|bool
void S(); // <其他类型> -> void|int|double|char
void E(); // <函数名> -> ID
void B(); // <语句块> -> {(<语句块>|<语句串>)*}
void F(); // <语句串> -> <语句>(<语句>)*
void G(); // <语句> -> <声明语句>|<赋值语句>|<条件语句>|<循环语句>|<返回语句>
void O(); // <声明语句>
void R(); // <赋值表达式> -> ID = (<算术表达式>|<布尔表达式>) 
void H(); // <赋值语句> -> <赋值表达式>; 
void I(); // <条件语句> -> if(<布尔表达式>) (<语句块>|<语句>) (else(<语句块>|<语句>) | 空)
void J(); // <循环语句> 
void Q(); // <返回语句> -> return (<算术表达式>|<布尔表达式>);
int  L(); // <布尔表达式> -> <布尔项>(||<布尔项>)*
int  W(); // <布尔项> -> <布尔因子>(&&<布尔因子>)*
int  X(); // <布尔因子> -> (<布尔表达式>)
          //             | <算术表达式> relop <算术表达式>
          //             | <ID|NUM>
int  K(); // <算术表达式> -> <项>(+<项>)* | <项>(-<项>)*
int  T(); // <项> -> <因子>(*<因子>)* | <因子>(/<因子>)*
int  U(); // <因子> -> (<算术表达式>) | <ID|NUM> 
int  P(); // <ID|NUM> -> ID|NUM|true|false

int getsym()
{
    return code_num[x++]; //读取下一个单词
}

void emit(string s1, string s2, string s3, string s4) // 四元式生成函数
{
    Quadruples[row][0] = s1;
    Quadruples[row][1] = s2;
    Quadruples[row][2] = s3; 
    Quadruples[row][3] = s4;
    row++;
}

void A() // -> 4 1 48 49 B
{
    if(sym == 4)
    {
        cout << "'int' succeed " << endl;
        sym = getsym(); 
        if(sym == 1)
        {
            cout << "'main' succeed " << endl;
            sym = getsym();
            if(sym == 48)
            {
                cout << "'(' succeed " << endl;
                sym = getsym();
                if(sym == 49)
                {
                    cout << "')' succeed " << endl;
                    sym = getsym();
                    B();
                }
                else
                    cout << "ERROR!  ')' missing" << endl;
            }
            else
                cout << "ERROR!  '(' missing" << endl;
        }
        else
            cout << "ERROR!  'main' missing" << endl;
    }
    else
        cout << "ERROR!  ')' missing" << endl;
}

void C() // -> D E 48 49 B
{
    D();
    E();
    if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
            B();
        }
        else    
            cout << "ERROR!  ')' missing" << endl;
    }
    else
        cout << "ERROR!  '(' missing" << endl;
}

void D() // -> 3|4|5|6|7        可以改为case语句
{
    if(sym == 3)
    {
        cout << "'void' succeed " << endl;
        sym = getsym();
    }
    else if(sym == 4)
    {
        cout << "'int' succeed " << endl;
        sym = getsym();
    }
    else if(sym == 5)
    {
        cout << "'double' succeed " << endl;
        sym = getsym();
    }
    else if(sym == 6)
    {
        cout << "'char' succeed " << endl;
        sym = getsym();
    }
    else if(sym == 7)
    {
        cout << "'bool' succeed " << endl;
        sym = getsym();
    }
    else
        cout << "语法错误 未找到<type>" << endl;
}

void E() // -> 21    
{
    if(sym == 21) 
    {
        cout << "" << endl;
        sym = getsym();
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void B() // -> 46 (B|F)* 47
{
    if(sym == 46)
    {
        cout << "'{' succeed " << endl;
        sym = getsym();
        while((sym>=3&&sym<=7)||sym==21||sym==7||(sym==10||sym==11)||sym==2)
        {
            if(sym == 46) // 语句块
                B();
            else
                F(); // 语句串
        }
        if(sym == 47)
        {
            cout << "'}' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "ERROR!  '}' missing" << endl;
    }
    else
        cout << "ERROR!  '{' missing" << endl;
}

void F() // -> G G*
{
    G();
    while((sym>=3&&sym<=7)||sym==21||sym==7||(sym==10||sym==11)||sym==2)
        G();
}

void G() // -> O|H|I|J|Q
{
    if(sym>=3 && sym<=7) // 声明语句
        O();
    else if(sym == 21) // 赋值语句
        H();
    else if(sym == 8) // 条件语句
        I();
    else if(sym==10 || sym==11) // 循环语句
        J();
    else if(sym == 2) // 返回语句
        Q();
    else
        cout << "语法错误 未找到<语句>" << endl;
}

void O()
{

}

void H() // -> R 44
{

}

void I() // -> 8 48 L 49 (G|B) (( 9 (G|B) ) | 空 )
{

}

void J() 
{

}

void Q() // -> 2 (L|K) 44
{

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
    A();

    return 0;
}
