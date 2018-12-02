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

struct val  // 变量结构体   符号表结构
{
    string name; // 变量名
    int type;  // 值类型的种别码 
    string value; // code_str数组中存储的字符串(来自词法分析)
} V[1000];
int i = 0; // 之后存储声明的变量
int j = 999; // 之前存储中间变量

string num_str(int num)//整型转字符串
{
    stringstream ss;
    ss << num;
    return ss.str();
}
int str_int(string s)//字符串转整型
{
    int num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
string num_str(double num)//浮点转字符串
{
    stringstream ss;
    ss << num;
    return ss.str();
}
double str_double(string s)//字符串转浮点
{
    double num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
char str_char(string s)//字符串转字符
{
    char c;
    stringstream ss;
    ss << s;
    ss >> c;
    return c;
}
int getsym()//读下一个词
{
    return code_num[x++];
}
int get_num()//查表，返回变量的序号，没有则返回-1
{
    for(int i=0;(V[i].name).size();i++)
        if(V[i].name==code_str[x-1])
            return i;
    return -1;
}

void A();void B();void C();void D();void E();void F();void G();void H();void I();void J();int K();int L();void O();int P();void Q();void R();void S();int T();int U();int W();int X();
void A1();void B1();void C1();void D1();void E1();void F1();void G1();void H1();void I1();void J1();void K1();void K1_();void L1();void L1_();void O1();void P1();void Q1();void R1();void S1();

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
                    cout << "语法错误 未找到')'" << endl;
            }
            else
                cout << "语法错误 未找到'('" << endl;
        }
        else
            cout << "语法错误 未找到'main'" << endl;
    }
    else
        cout << "语法错误 未找到'int'" << endl;
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
            cout << "语法错误 未找到')'" << endl;
    }
    else
        cout << "语法错误 未找到'('" << endl;
}

void D() // -> 3|4|5|6|7
{
    switch(sym)
    {
        case 3: cout << "'void' succeed " << endl;
                sym = getsym();
                break;
        case 4: cout << "'int' succeed " << endl;
                sym = getsym();
                break;
        case 5: cout << "'double' succeed " << endl;
                sym = getsym();
                break;
        case 6: cout << "'char' succeed " << endl;
                sym = getsym();
                break;
        case 7: cout << "'bool' succeed " << endl;
                sym = getsym();
                break;
        default: cout << "语法错误 未找到<type>" << endl;
                 break;
    }
}

void S() // -> 3|4|5|6
{
    switch(sym)
    {
        case 3: cout << "'void' succeed " << endl;
                sym = getsym();
                break;
        case 4: cout << "'int' succeed " << endl;
                sym = getsym();
                break;
        case 5: cout << "'double' succeed " << endl;
                sym = getsym();
                break;
        case 6: cout << "'char' succeed " << endl;
                sym = getsym();
                break;
        default: cout << "语法错误 未找到<type>" << endl;
                 break;
    }
}

void E() // -> 21    
{
    if(sym == 21) 
    {
        cout << "<变量名> succeed " << endl;
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
        while(sym==46||(sym>=3&&sym<=7)||sym==21||sym==8||(sym==10||sym==11))
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
            cout << "语法错误 未找到'}'" << endl;
    }
    else
        cout << "语法错误 未找到'{'" << endl;
}

void F() // -> G G*
{
    G();
    while((sym>=3&&sym<=7)||sym==21||sym==8||(sym==10||sym==11)||sym==2)
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
            cout << "'<变量名>' succeed " << endl;
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
                V[i++].value = V[t].value; // 没必要？？？
                if(sym == 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "语法错误 未找到';'" << endl;
            }       
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                i++;
                sym = getsym();
            }   
            else
                cout << "语法错误 未找到'='或';'" << endl;
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
                V[i++].value = V[t].value; // 没必要？？？
                if(sym == 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "语法错误 未找到';'" << endl;
            }
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                i++;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到'='或';'" << endl;
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
                cout << "语义错误 变量类型不匹配" << endl;
                exit(0);
            }
            else
                V[num].value = V[t].value;
        }
        else
            cout << "语法错误 未找到'='" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void H() // -> R 44
{
    if(sym == 21)
    {
        cout << "<token> succeed " << endl;
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
                cout << "语义错误 变量类型不匹配" << endl;
                exit(0);
            }
            else
                V[num].value = V[t].value;
            if(sym == 44)
            {
                cout << "';' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到';'" << endl;
        }
        else
            cout << "语法错误 未找到'='" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void I() // -> 8 48 L 49 (G|B) (( 9 (G|B) ) | 空 )
{
    if(sym == 8)
    {
        cout << "'if' succeed " << endl;
        sym = getsym();
        if(sym == 48)
        {
            cout << "'(' succed " << endl;
            sym = getsym();
            int t1 = L(); // 条件语句的结果变量
            if(sym == 49)
            {
                cout << "')' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到')'" << endl;
            if(sym==21||(sym>=3&&sym<=6)||sym==8||(sym==10||sym==11)||sym==2)
            {
                if(V[t1].value[0] == 't') // true
                    G();
                else
                    G1(); // 仅语法分析
            }
            else if(sym == 46)
            {
                if(V[t1].value[0] == 't') // true
                    B();
                else
                    B1(); // 仅语法分析
            }
            if(sym == 9) // else
            {
                if(sym==21||(sym>=3&&sym<=6)||sym==8||(sym==10||sym==11)||sym==2)
                {
                    if(V[t1].value[0] == 't') // true
                        G1();
                    else
                        G(); // 仅语法分析
                }
                else if(sym == 46)
                {
                    if(V[t1].value[0] == 't') // true
                        B1();
                    else
                        B(); // 仅语法分析
                }
            }
            else if(sym==1||sym==22||sym==23||(sym>=31&&sym<=45)||(sym>=50&&sym<=57))
            {
                printf("语法错误 未找到Follow集\n");
            }
        }
        else    
            cout << "语法错误 未找到'('" << endl;
    }
    else
        cout << "语法错误 未找到'if'" << endl; 
}

int X() // -> (48 L 49) | (K relop K) | K
{
    int t1; 
    if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        t1 = L();
        if(sym == 49)
        {
            cout << "')' succeed "<< endl;
            sym = getsym();
        }
        else
            cout << "ERROR! ')' missing" << endl;
        return t1;
    }
    else if((sym>=21 && sym<=23)||sym==14||sym==15)
    {
        if(sym==14 || sym==15)
            t1 = P();
        else
            t1 = K();
        if(sym>=37 && sym<=42)
        {
            cout << "<relop> succeed " << endl;
            int op = sym;
            sym = getsym();
            int t2; 
            if(sym==14 || sym==15)
                t2 = P(); // !!!!??
            else
                t2 = K();
            V[j].name = "tmp" + num_str(1000-j);
            V[j].type = V[t1].type;
            V[j].value = V[t1].value;
            int t3 = j--; // 中间变量
            switch(V[t2].type)
            {
                case 3:
                {
                    cout << "语义错误 变量类型不匹配" << endl;
                    exit(0);
                }
                case 4:
                {
                    if(V[t3].type != V[t2].type)
                    {
                        cout << "语义错误 变量类型不匹配" << endl;
                        exit(0);
                    }
                    switch(op)
                    {
                        case 37: V[t3].value=str_int(V[t3].value)<str_int(V[t2].value)?"true":"false";break;
                        case 38: V[t3].value=str_int(V[t3].value)!=str_int(V[t2].value)?"true":"false";break;
                        case 39: V[t3].value=str_int(V[t3].value)<=str_int(V[t2].value)?"true":"false";break;
                        case 40: V[t3].value=str_int(V[t3].value)>str_int(V[t2].value)?"true":"false";break;
                        case 41: V[t3].value=str_int(V[t3].value)>=str_int(V[t2].value)?"true":"false";break;
                        case 42: V[t3].value=str_int(V[t3].value)==str_int(V[t2].value)?"true":"false";break;
                    }
                    V[t3].type = 7; // bool型
                    break;
                }
                case 5:
                {
                    if(V[t3].type != V[t2].type)
                    {
                        cout << "语义错误 变量类型不匹配" << endl;
                        exit(0);
                    }
                    switch(op)
                    {
                        case 37: V[t3].value=str_double(V[t3].value)<str_double(V[t2].value)?"true":"false";break;
                        case 38: V[t3].value=str_double(V[t3].value)!=str_double(V[t2].value)?"true":"false";break;
                        case 39: V[t3].value=str_double(V[t3].value)<=str_double(V[t2].value)?"true":"false";break;
                        case 40: V[t3].value=str_double(V[t3].value)>str_double(V[t2].value)?"true":"false";break;
                        case 41: V[t3].value=str_double(V[t3].value)<=str_double(V[t2].value)?"true":"false";break;
                        case 42: V[t3].value=str_double(V[t3].value)==str_double(V[t2].value)?"true":"false";break;
                    }
                    V[t3].type=6;
                    break;
                }
                case 6:
                {
                    if(V[t3].type != V[t2].type)
                    {
                        cout << "语义错误 变量类型不匹配" << endl;
                        exit(0);
                    }
                    switch(op)
                    {
                        case 37: V[t3].value=str_char(V[t3].value)<str_char(V[t2].value)?"true":"false";break;
                        case 38: V[t3].value=str_char(V[t3].value)!=str_char(V[t2].value)?"true":"false";break;
                        case 39: V[t3].value=str_char(V[t3].value)<=str_char(V[t2].value)?"true":"false";break;
                        case 40: V[t3].value=str_char(V[t3].value)>str_char(V[t2].value)?"true":"false";break;
                        case 41: V[t3].value=str_char(V[t3].value)<=str_char(V[t2].value)?"true":"false";break;
                        case 42: V[t3].value=str_char(V[t3].value)==str_char(V[t2].value)?"true":"false";break;
                    }
                    V[t3].type=6;
                    break;
                }
            }
            return t3;
        }
        else if(sym!=38&&sym!=42&&sym!=44&&sym!=49&&sym!=56&&sym!=57)
        {
            printf("语法错误 未找到Follow集\n");
            exit(0);
        }
        else
            return t1;
    }
    else
    {
        cout << "语法错误 未找到<布尔因子>" << endl;
        exit(0);
    }
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
        V[j].value = V[t].value;
        t = j--; // 更新中间变量
        if(V[t].type != V[t2].type) // 判断参与运算的和生成的数值是否为同一类型
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
        }
        if(V[t].type==4) // int
        {
            switch(op)
            {
                case 31: V[t].value=num_str(str_int(V[t].value)*str_int(V[t2].value));break;
                case 32: V[t].value=num_str(str_int(V[t].value)/str_int(V[t2].value));break;
            }
        }
        else if(V[t].type==5) // double
        {
            switch(op)
            {
                case 31: V[t].value=num_str(str_double(V[t].value)*str_double(V[t2].value));break;
                case 32: V[t].value=num_str(str_double(V[t].value)/str_double(V[t2].value));break;
            }
        }
        else
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
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
        V[j].value = V[t].value;
        t = j--; // 更新中间变量
        if(V[t].type != V[t2].type) // 判断参与运算的和生成的数值是否为同一类型
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
        }
        if(V[t].type==4) // int
        {
            switch(op)
            {
                case 33: V[t].value=num_str(str_int(V[t].value)*str_int(V[t2].value));break;
                case 34: V[t].value=num_str(str_int(V[t].value)/str_int(V[t2].value));break;
            }
        }
        else if(V[t].type==5) // double
        {
            switch(op)
            {
                case 33: V[t].value=num_str(str_double(V[t].value)*str_double(V[t2].value));break;
                case 34: V[t].value=num_str(str_double(V[t].value)/str_double(V[t2].value));break;
            }
        }
        else
        {
            cout << "语义错误 变量类型不匹配" << endl;
            exit(0);
        }
    }
    return t;
}

int U() // -> (48 K 49) | (21|22|23) 
{
    int t;
    if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        t = K();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到')'" << endl;
    }
    else if(sym>=21 || sym<=23)
        t = P();
    else
        cout << "语法错误 未找到<因子>" << endl;
    return t;
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
            V[j].name = "tmp" + num_str(1000-j);
            V[j].value = code_str[x-1];
            V[j].type = sym - 18; // 22-18=4 -> int  23-18=5 -> double
            num = j--;
        }
        sym = getsym();
        return num;
    }
    else if(sym==14 || sym==15) // true or false
    {
        cout << "'true' or 'false' succeed " << endl;
        V[j].name = "tmp" + num_str(1000-j);
        V[j].value = code_str[x-1];
        V[j].type = 7; // bool类型
        num = j--;
        sym = getsym();
        return num;
    } 
    else
    {
        cout << "语法错误 未找到<ID|NUM>" << endl;
        return -1;
    }
}

void S1() // -> <其他类型>
{
    switch(sym)
    {
        case 3: cout << "'void' succeed " << endl;
                sym = getsym();
                break;
        case 4: cout << "'int' succeed " << endl;
                sym = getsym();
                break;
        case 5: cout << "'double' succeed " << endl;
                sym = getsym();
                break;
        case 6: cout << "'char' succeed " << endl;
                sym = getsym();
                break;
        default: cout << "语法错误 未找到<type>" << endl;
                 break;
    }
}

void B1() // <语句块>
{
    if(sym==46)
    {
        cout << "'{' succeed " << endl;
        sym=getsym();
        while(sym==46||(sym>=3&&sym<=7)||sym==21||sym==8||sym==10||sym==11)
        {
            if(sym==46)
                B1();
            else
                F1();
        }
        if(sym==47)
        {
            cout << "'}' succeed " << endl;
            sym=getsym();
        }
        else
            cout << "语法错误 未找到'}'" << endl;
    }
    else
        cout << "语法错误 未找到'{'" << endl;
}

void F1() // <语句串>
{
    G1();
    while(sym==21||(sym>=3&&sym<=7)||sym==8||sym==10||sym==11||sym==2)
        G1();
}

void G1() // -> <语句>
{
    if(sym>=3 && sym<=7) // 声明语句
        O1();
    else if(sym == 21) // 赋值语句
        H1();
    else if(sym == 8) // 条件语句
        I1();
    else if(sym==10 || sym==11) // 循环语句
        J1();
    else if(sym == 2) // 返回语句
        Q1();
    else
        cout << "语法错误 未找到<语句>" << endl;
}

void G1() // <语句>
{
    if(sym>=3 && sym<=7) // 声明语句
        O1();
    else if(sym == 21) // 赋值语句
        H1();
    else if(sym == 8) // 条件语句
        I1();
    else if(sym==10 || sym==11) // 循环语句
        J1();
    else if(sym == 2) // 返回语句
        Q1();
    else
        cout << "语法错误 未找到<语句>" << endl;
}

void O1() // -> <声明语句>
{
    if(sym == 7) // bool型声明
    {
        cout << "'bool' succeed " << endl;
        sym = getsym();
        if(sym == 21)
        {
            cout << "'<变量名>' succeed " << endl;
            if(get_num() != -1) // 自定义变量表中已经存在该变量
            {
                cout << "语义错误 变量重复定义" << endl;
                exit(0);
            }
            sym = getsym();
            if(sym == 36)
            {
                cout << "'=' succeed " << endl;
                sym = getsym();
                L1();
                if(sym == 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "语法错误 未找到';'" << endl;
            }       
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                sym = getsym();
            }   
            else
                cout << "语法错误 未找到'='或';'" << endl;
        }
        else
        {
            cout << "语法错误 未找到<变量名>" << endl; 
            exit(0);
        }
    }
    else // 其它类型定义
    {
        S1();
        if(sym == 21)
        {
            cout << "<变量名> succeed " << endl;
            if(get_num() != -1)
            {
                cout << "语义错误 变量重复定义" << endl;
                exit(0);
            }
            sym = getsym();
            if(sym == 36)
            {
                cout << "'=' succeed " << endl;
                sym = getsym();
                K1();
                if(sym == 44)
                {
                    cout << "';' succeed " << endl;
                    sym = getsym();
                }
                else    
                    cout << "语法错误 未找到';'" << endl;
            }
            else if(sym == 44)
            {
                cout << "';' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到'='或';'" << endl;
        }
        else
        {
            cout << "语法错误 未找到<变量名>" << endl; 
            exit(0);
        }
    }
}

void P1()// <ID|NUM>
{
    if(sym>=21 && sym<=23)
    {
        cout << "<ID or NUM> succeed" << endl;
        if(sym==21)
            int num=get_num();//获得变量的号,没找到返回-1
        sym=getsym();
    }
    else if(sym==14 || sym==15)
    {
        cout << "true or false succeed" << endl;
        sym=getsym();
    }
    else
        cout << "语法错误 未找到<ID|NUM>" << endl;
}

void Q1() // <返回语句>
{
    if(sym == 2)
    {
        cout << "'return' succeed " << endl;
        sym = getsym();
        K1();
        if(sym == 44)
        {
            cout << "';' succeed " << endl;
            sym = getsym();
        }
        else 
            cout << "语法错误 未找到';'" << endl;
    }
    else
        cout << "语法错误 未找到'return'" << endl;
}

void R1() // -> <赋值表达式>
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
            if(V[num].type == 7) // bool
                L1();
            else    
                K1();
        }
        else
            cout << "语法错误 未找到'='" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void H1() // -> <赋值语句>
{
    if(sym == 21)
    {
        cout << "<token> succeed " << endl;
        int num = get_num(); // 返回定义的变量在数组中存储的下标
        sym = getsym();
        if(sym == 36)
        {
            cout << "'=' succeed " << endl;
            sym = getsym();
            if(V[num].type == 7) // bool
                L1();
            else    
                K1();
            if(sym == 44)
            {
                cout << "';' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到';'" << endl;
        }
        else
            cout << "语法错误 未找到'='" << endl;
    }
    else
        cout << "语法错误 未找到<变量名>" << endl;
}

void I1() // -> <条件语句>
{
    if(sym == 8)
    {
        cout << "'if' succeed " << endl;
        sym = getsym();
        if(sym == 48)
        {
            cout << "'(' succed " << endl;
            sym = getsym();
            L1(); // 条件语句的结果变量
            if(sym == 49)
            {
                cout << "')' succeed " << endl;
                sym = getsym();
            }
            else
                cout << "语法错误 未找到')'" << endl;
            if(sym==21||(sym>=3&&sym<=6)||sym==8||(sym==10||sym==11)||sym==2)
                G1();
            else if(sym == 46)
                B1();
            if(sym == 9) // else
            {
                cout << "'else' succeed " << endl;
                sym = getsym();
                if(sym==21||(sym>=3&&sym<=6)||sym==8||(sym==10||sym==11)||sym==2)
                    G1();
                else if(sym == 46)
                    B1();
            }
            else if(sym==1||sym==22||sym==23||(sym>=31&&sym<=45)||(sym>=50&&sym<=57))
            {
                printf("语法错误 未找到Follow集\n");
            }
        }
        else    
            cout << "语法错误 未找到'('" << endl;
    }
    else
        cout << "语法错误 未找到'if'" << endl; 
}

void J1() // -> <循环语句>
{
    if(sym == 10) // while
    {
        cout << "'while' succeed " << endl;
        sym = getsym();
        if(sym == 48)
        {
            cout << "'(' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到'('" << endl;
        L1();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到')'" << endl;
        B1();
    }
    else if(sym == 11) // for
    {
        cout << "'for' succeed " << endl;
        sym = getsym();
        if(sym == 48)
        {
            cout << "'(' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到'('" << endl;
        if(sym == 21)
            H1();
        else
            O1();
        L1();
        if(sym == 44)
        {
            cout << "';' succeed " << endl;
            sym = getsym();
        }
        else    
            cout << "语法错误 未找到';'" << endl;
        R1();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到')'" << endl;
        B1();
    }
    else
        cout << "'while' or 'for' fail" << endl;
}

void L1() // <布尔表达式> 
{
    if((sym>=21&&sym<=23) || sym==14 || sym==15)
    {
        P1();
        if(sym>=37 && sym<=42)
        {
            cout << "<relop> succeed " << endl;
            sym = getsym();
            P1();
            L1_();
        }
        else if(sym!=38&&sym!=42&&sym!=44&&sym!=49&&sym!=56&&sym!=57)
        {
            cout << "语法错误 未找到Follow集" << endl;
            exit(0);
        }
        else
            L1_();
    }
    else if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        L1();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到')'" << endl;
        L1_();
    }
    else
    {
        cout << "语法错误 未找到<布尔表达式>" << endl;
        exit(0);
    }
}

void L1_()
{
    if(sym==56 || sym==57)
    {
        sym == getsym();
        L1();
        L1_();
    }
    else if(sym!=38&&sym!=42&&sym!=44&&sym!=49&&sym!=56&&sym!=57)
    {
        cout << "语法错误 未找到Follow集" << endl;
        exit(0);
    }
}

void K1() // <算术表达式>
{
    if(sym == 48)
    {
        cout << "'(' succeed " << endl;
        sym = getsym();
        K1();
        if(sym == 49)
        {
            cout << "')' succeed " << endl;
            sym = getsym();
        }
        else
            cout << "语法错误 未找到')'" << endl;
    }
    else if(sym>=21 && sym<=23)
        P1();
    else 
        cout << "语法错误 未找到<算术表达式>" << endl;
    K1_();
}

void K1_()
{
    if(sym>=31 && sym<=34)
    {
        cout << "'+-*/' succeed " << endl;
        sym = getsym();
        K1();
        K1_();
    }
    else if((sym<31||sym>34)&&sym!=44&&sym!=49)
    {
        cout << "语法错误 未找到Follow集" << endl;
        exit(0);
    }
}