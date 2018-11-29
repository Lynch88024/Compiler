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
string code_str[1000]; //存储种别码对应的字符串
/*一些全局变量*/
int x = 0; // x是单词数组中的计数器
int sym = 52; // sym是该单词的种别码
/*四元式*/
string Quadruples[500][4]; 
int row = 0;

struct val  // 变量结构体   符号表结构
{
    string name; // 变量名
    int type;  // 值类型的种别码 
    string value; // code_str数组中存储的字符串(来自词法分析)
} V[1500];
int i = 0; // 之后存储声明的变量
int j = 1000; // 之前存储中间变量
int reg = 0; // 存储常量

/*数值类型转换函数*/
string num_str(int num) // 整型 -> 字符串
{
    stringstream ss;
    ss << num;
    return ss.str();
}
string num_str(double num) // 浮点型 -> 字符串
{
    stringstream ss;
    ss << i;
    return ss.str();
}
int str_int(string s) // 字符串 -> 整型
{
    int num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
double str_double(string s) // 字符串 -> 浮点型
{
    double num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
char str_char(string s) // 字符串 -> 字符
{
    double c; // !!!!!!!!!!?
    stringstream ss;
    ss << s;
    ss >> c;
    return c;
}


/*----文法函数声明----*/   
void A(); // <主函数> -> int main() <语句块> 
void C(); // <函数> -> <所有类型> <函数名>() <语句块>
void D(); // <所有类型> -> void|int|double|char|bool
void S(); // <其他类型> -> void|int|double|char
void E(); // <函数名> -> ID
void B(); // <语句块> -> {(<语句块>|<语句串>)*}
void F(); // <语句串> -> <语句>(<语句>)*
void G(); // <语句> -> <声明语句>|<赋值语句>|<条件语句>|<循环语句>|<返回语句>
void O(); // <声明语句> -> (<其它类型> ID ((=<算术表达式>;)|;))
          //             | (<Bool> ID ((=<布尔表达式>;)|;))
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

int get_num() // 查表，与表中已有字符串匹配，若存在返回变量的序号，不存在返回-1,并将新标识符插入表中
{
    for(int i=0; (V[i].name).size(); i++) // 声明变量单词表非空时，循环
        if(V[i].name == code_str[x-1])
            return i;
    return -1;
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

void S() // -> 3|4|5|6
{
    if(sym == 3)
    {
        cout << "'void' succeed " << endl;
        V[i].type = sym;
        sym = getsym();
    }
    else if(sym == 4)
    {
        cout << "'int' succeed " << endl;
        V[i].type = sym;
        sym = getsym();
    }
    else if(sym == 5)
    {
        cout << "'double' succeed " << endl;
        V[i].type = sym;
        sym = getsym();
    }
    else if(sym == 6)
    {
        cout << "'char' succeed " << endl;
        V[i].type = sym;
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
 
void O() // -> (S 21 ((36 K 44) | 44)) | (7 21 ((36 L 44) | 44))
{
    V[i].type = sym;
    if(sym == 7) // bool型声明
    {
        cout << "'bool' succeed " << endl;
        sym = getsym();
        if(sym == 21)
        {
            cout << "'<变量>' succeed " << endl;
            if(get_num() != -1) // 自定义变量表中已经存在该变量
            {
                cout << "语义错误 变量重复定义" << endl;
                exit(0);
            }
            V[i].name = code_str[x-1];
            sym = getsym();
            if(sym == 36)
            {
                cout << "'=' succeed " << endl;
                sym = getsym();
                int t = L();
                if(V[i].type != V[t].type)
                {
                    cout << "语义错误 变量类型不匹配" << endl;
                    exit(0);
                }
                emit("=",V[i].name,(V[t].value.size())?V[t].value:V[t].name,"_");
                i++; // chou!!!
                if(sym = 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "ERROR!  ';' missing" << endl;
            }       
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                i++;
                sym = getsym();
            }   
            else
                cout << "ERROR  '=' or ';' missing" << endl;
        }
        else
        {
            cout << "语法错误 未找到<变量名>" << endl; 
            exit(0);
        }
    }
    else // 其它类型定义
    {
        S();
        if(sym == 21)
        {
            cout << "<变量名> succeed " << endl;
            if(get_num() != -1)
            {
                cout << "语义错误 变量重复定义" << endl;
                exit(0);
            }
            V[i].name = code_str[x-1];
            sym = getsym();
            if(sym == 36)
            {
                cout << "'=' succeed " << endl;
                sym = getsym();
                int t = K();
                if(V[i].type != V[t].type)
                {
                    cout << "语义错误 变量类型不匹配" << endl;
                    exit(0);
                }
                emit("=",V[i].name,(V[t].value.size())?V[t].value:V[t].name,"_");
                i++;
                if(sym == 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "ERROR!  ';' missing" << endl;
            }
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                i++;
                sym = getsym();
            }
            else
                cout << "ERROR  '=' or ';' missing" << endl;
        }
        else
        {
            cout << "语法错误 未找到<变量名>" << endl; 
            exit(0);
        }
    }
}

void R() // -> 21 36 (K|L)
{
    if(sym == 21)
    {
        cout << "<变量名> succeed " << endl;
        int num = get_num(); // 返回定义的变量在数组中存储的下标
        sym = getsym();
        if(sym == 36)
        {
            cout << "'=' succeed " << endl;
            sym = getsym();
            int t;
            if(V[num].type == 7) // bool
                t = L();
            else    
                t = K();
            if(V[num].type != V[t].type)
            {
                cout << "语义错误 变量类型不匹配###" << endl;
                exit(0);
            }
            emit("=",V[num].name,(V[t].value.size())?V[t].value:V[t].name,"_");
        }
        else
            cout << "ERROR!  '=' missing" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void H() // -> R 44
{
    if(sym == 21)
    {
        cout << "<变量名> succeed " << endl;
        int num = get_num(); // 返回定义的变量在数组中存储的下标
        sym = getsym();
        if(sym == 36)
        {
            cout << "'=' succeed " << endl;
            sym = getsym();
            int t;
            if(V[num].type == 7) // bool
                t = L();
            else    
                t = K();
            if(V[num].type != V[t].type)
            {
                cout << "语义错误 变量类型不匹配!!!" << endl;
                exit(0);
            }
            if(sym == 44)
            {
                cout << "';' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "ERROR!  ';' missing" << endl;
            emit("=",V[num].name,(V[t].value.size())?V[t].value:V[t].name,"_");
        }
        else
            cout << "ERROR!  '=' missing" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void I() // -> 8 48 L 49 (G|B) (( 9 (G|B) ) | 空 )
{

}

void J() 
{

}

void Q() // -> 2 (L|K) 44
{
    if(sym == 2)
    {
        cout << "'return' succeed " << endl;
        sym = getsym();
        int t = K();
        if(sym == 44)
        {
            cout << "';' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "ERROR!  ';' missing" << endl;
        emit("return",(V[t].value.size())?V[t].value:V[t].name,"_","_");
    }
    else
        cout << "ERROR!  'return' missing" << endl;
}

int L() // -> W (57 W)*
{
    int t1 = W();
    int t = t1; // 生成一个中间变量
    while(sym == 57)
    {
        cout << "'|' succeed " << endl;
        sym = getsym();
        int t2 = W();
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t;
        t = j--;
        emit("|",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);
    }
    return t;
}

int W() // -> X (56 X)*
{
    int t1 = X();
    int t = t1; // 生成一个中间变量
    while(sym == 57)
    {
        cout << "'&' succeed " << endl;
        sym = getsym();
        int t2 = X();
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t;
        t = j--;
        emit("&",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);
    }
    return t;
}

int X()
{

}

int K() // -> T ((32|32) T)*
{
    int t1 = T(); 
    int t = t1; // 生成一个中间变量,在数组中序号
    while(sym==31 || sym==32)
    {
        int op = sym;
        if(sym == 31)
        {
            cout << "'+' succeed " << endl;
            sym = getsym();
        }
        else if(sym == 32)
        {
            cout << "'-' succeed " << endl;
            sym = getsym();
        }
        int t2 = T(); // 第二个运算数
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t; // 第一个运算数
        t = j--; // 更新中间变量
        if(V[t].type != V[t2].type) // 判断参与运算的和生成的数值是否为同一类型
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
        }
        switch(op)
        {    
            case 31:emit("+",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);break;
            case 32:emit("-",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);break;
        }
    }
    return t;
}

int T() // -> U ((33|34) U)*
{
    int t1 = U(); 
    int t = t1; // 生成一个中间变量,在数组中序号
    while(sym==33 || sym==34)
    {
        int op = sym;
        if(sym == 33)
        {
            cout << "'*' succeed " << endl;
            sym = getsym();
        }
        else if(sym == 34)
        {
            cout << "'/' succeed " << endl;
            sym = getsym();
        }
        int t2 = U(); // 第二个运算数
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t; // 第一个运算数
        t = j--; // 更新中间变量
        if(V[t].type != V[t2].type) // 判断参与运算的和生成的数值是否为同一类型
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
        }
        switch(op)
        {
            case 33:emit("*",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);break;
            case 34:emit("/",(V[t3].value.size())?V[t3].value:V[t3].name,(V[t2].value.size())?V[t2].value:V[t2].name,V[t].name);break;
        }
    }
    return t;
}

int U() // -> (48 K 49) | (21|22|23) 
{
    int t1;
    if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        t1 = K();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "ERROR!  ')' missing" << endl;
    }
    else if(sym>=21 || sym<=23)
        t1 = P();
    else
        cout << "语法错误 未找到<因子>" << endl;
    return t1;
}

int P() // -> 21|22|23|14|15
{
    int num;
    if(sym>=21 && sym<=23)
    {
        cout << "<ID or NUM> succeed " << endl;
        if(sym == 21) // 定义的变量名
            num = get_num(); // 得到所定义变量的序号
        else // 整型、浮点型 常数
        {
            V[1000+reg].value = code_str[x-1];
            V[1000+reg].type = sym - 18; // 22-18=4 -> int  23-18=5 -> double
            num = 1000 + reg; // 返回的是存储大数组该元素的下标
            reg++;
        }
        sym = getsym();
        return num;
    }
    else if(sym==14 || sym==15) // true or false
    {
        cout << "'true' or 'false' succeed " << endl;
        V[1000+reg].value = code_str[x-1];
        V[1000+reg].type = 7; // bool类型
        num = 1000 + reg;
        reg++;
        sym = getsym();
        return num;
    } 
    else
    {
        cout << "语法错误 未找到<ID|NUM>" << endl;
        return -1;
    }
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

    fp=fopen(file_out,"w");
    cout << endl << "输出四元式：" << endl;
    for(int i=0; i<row; i++)
    {
        fprintf(fp,"(%s,%s,%s,%s)\n",Quadruples[i][0].c_str(),Quadruples[i][1].c_str(),Quadruples[i][2].c_str(),Quadruples[i][3].c_str());
        printf("(%s,%s,%s,%s)\n",Quadruples[i][0].c_str(),Quadruples[i][1].c_str(),Quadruples[i][2].c_str(),Quadruples[i][3].c_str());
    }
    fclose(fp);

    return 0;
}
