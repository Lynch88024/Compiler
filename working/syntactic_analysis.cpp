#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

/*��������ļ�*/
char file_in[] = "./test1_Analysis.txt";
char file_out[] = "./test1_Analysis_aft.txt";
/*���ļ��ж�ȡ�����ֱ��롢����*/
int n = 0;
char str[100];
/*�洢�ֱ��뼰����Ӧ����*/
int code_num[1000] = {0};
string code_str[1000]; //�洢�ֱ����Ӧ���ַ���
/*һЩȫ�ֱ���*/
int x = 0; // x�ǵ��������еļ�����
int sym = 52; // sym�Ǹõ��ʵ��ֱ���
/*��Ԫʽ*/
string Quadruples[500][4]; 
int row = 0;

struct val  // �����ṹ��   ���ű�ṹ
{
    string name; // ������
    int type;  // ֵ���͵��ֱ��� 
    string value; // code_str�����д洢���ַ���(���Դʷ�����)
} V[1500];
int i = 0; // ֮��洢�����ı���
int j = 1000; // ֮ǰ�洢�м����
int reg = 0; // �洢����

/*��ֵ����ת������*/
string num_str(int num) // ���� -> �ַ���
{
    stringstream ss;
    ss << num;
    return ss.str();
}
string num_str(double num) // ������ -> �ַ���
{
    stringstream ss;
    ss << i;
    return ss.str();
}
int str_int(string s) // �ַ��� -> ����
{
    int num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
double str_double(string s) // �ַ��� -> ������
{
    double num;
    stringstream ss;
    ss << s;
    ss >> num;
    return num;
}
char str_char(string s) // �ַ��� -> �ַ�
{
    double c; // !!!!!!!!!!?
    stringstream ss;
    ss << s;
    ss >> c;
    return c;
}


/*----�ķ���������----*/   
void A(); // <������> -> int main() <����> 
void C(); // <����> -> <��������> <������>() <����>
void D(); // <��������> -> void|int|double|char|bool
void S(); // <��������> -> void|int|double|char
void E(); // <������> -> ID
void B(); // <����> -> {(<����>|<��䴮>)*}
void F(); // <��䴮> -> <���>(<���>)*
void G(); // <���> -> <�������>|<��ֵ���>|<�������>|<ѭ�����>|<�������>
void O(); // <�������> -> (<��������> ID ((=<�������ʽ>;)|;))
          //             | (<Bool> ID ((=<�������ʽ>;)|;))
void R(); // <��ֵ���ʽ> -> ID = (<�������ʽ>|<�������ʽ>) 
void H(); // <��ֵ���> -> <��ֵ���ʽ>; 
void I(); // <�������> -> if(<�������ʽ>) (<����>|<���>) (else(<����>|<���>) | ��)
void J(); // <ѭ�����> 
void Q(); // <�������> -> return (<�������ʽ>|<�������ʽ>);
int  L(); // <�������ʽ> -> <������>(||<������>)*
int  W(); // <������> -> <��������>(&&<��������>)*
int  X(); // <��������> -> (<�������ʽ>)
          //             | <�������ʽ> relop <�������ʽ>
          //             | <ID|NUM>
int  K(); // <�������ʽ> -> <��>(+<��>)* | <��>(-<��>)*
int  T(); // <��> -> <����>(*<����>)* | <����>(/<����>)*
int  U(); // <����> -> (<�������ʽ>) | <ID|NUM> 
int  P(); // <ID|NUM> -> ID|NUM|true|false

int getsym()
{
    return code_num[x++]; //��ȡ��һ������
}

int get_num() // �������������ַ���ƥ�䣬�����ڷ��ر�������ţ������ڷ���-1,�����±�ʶ���������
{
    for(int i=0; (V[i].name).size(); i++) // �����������ʱ�ǿ�ʱ��ѭ��
        if(V[i].name == code_str[x-1])
            return i;
    return -1;
}

void emit(string s1, string s2, string s3, string s4) // ��Ԫʽ���ɺ���
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

void D() // -> 3|4|5|6|7        ���Ը�Ϊcase���
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
        cout << "�﷨���� δ�ҵ�<type>" << endl;
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
        cout << "�﷨���� δ�ҵ�<type>" << endl;
}

void E() // -> 21    
{
    if(sym == 21) 
    {
        cout << "" << endl;
        sym = getsym();
    }
    else
        cout << "�﷨���� δ�ҵ�<������>" << endl;
}

void B() // -> 46 (B|F)* 47
{
    if(sym == 46)
    {
        cout << "'{' succeed " << endl;
        sym = getsym();
        while((sym>=3&&sym<=7)||sym==21||sym==7||(sym==10||sym==11)||sym==2)
        {
            if(sym == 46) // ����
                B();
            else
                F(); // ��䴮
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
    if(sym>=3 && sym<=7) // �������
        O();
    else if(sym == 21) // ��ֵ���
        H();
    else if(sym == 8) // �������
        I();
    else if(sym==10 || sym==11) // ѭ�����
        J();
    else if(sym == 2) // �������
        Q();
    else
        cout << "�﷨���� δ�ҵ�<���>" << endl;
}
 
void O() // -> (S 21 ((36 K 44) | 44)) | (7 21 ((36 L 44) | 44))
{
    V[i].type = sym;
    if(sym == 7) // bool������
    {
        cout << "'bool' succeed " << endl;
        sym = getsym();
        if(sym == 21)
        {
            cout << "'<����>' succeed " << endl;
            if(get_num() != -1) // �Զ�����������Ѿ����ڸñ���
            {
                cout << "������� �����ظ�����" << endl;
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
                    cout << "������� �������Ͳ�ƥ��" << endl;
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
            cout << "�﷨���� δ�ҵ�<������>" << endl; 
            exit(0);
        }
    }
    else // �������Ͷ���
    {
        S();
        if(sym == 21)
        {
            cout << "<������> succeed " << endl;
            if(get_num() != -1)
            {
                cout << "������� �����ظ�����" << endl;
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
                    cout << "������� �������Ͳ�ƥ��" << endl;
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
            cout << "�﷨���� δ�ҵ�<������>" << endl; 
            exit(0);
        }
    }
}

void R() // -> 21 36 (K|L)
{
    if(sym == 21)
    {
        cout << "<������> succeed " << endl;
        int num = get_num(); // ���ض���ı����������д洢���±�
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
                cout << "������� �������Ͳ�ƥ��###" << endl;
                exit(0);
            }
            emit("=",V[num].name,(V[t].value.size())?V[t].value:V[t].name,"_");
        }
        else
            cout << "ERROR!  '=' missing" << endl;
    }
    else
        cout << "�﷨���� δ�ҵ�<������>" << endl;
}

void H() // -> R 44
{
    if(sym == 21)
    {
        cout << "<������> succeed " << endl;
        int num = get_num(); // ���ض���ı����������д洢���±�
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
                cout << "������� �������Ͳ�ƥ��!!!" << endl;
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
        cout << "�﷨���� δ�ҵ�<������>" << endl;
}

void I() // -> 8 48 L 49 (G|B) (( 9 (G|B) ) | �� )
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
    int t = t1; // ����һ���м����
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
    int t = t1; // ����һ���м����
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
    int t = t1; // ����һ���м����,�����������
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
        int t2 = T(); // �ڶ���������
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t; // ��һ��������
        t = j--; // �����м����
        if(V[t].type != V[t2].type) // �жϲ�������ĺ����ɵ���ֵ�Ƿ�Ϊͬһ����
        {
            cout << "������� �������Ͳ�ƥ��" << endl;
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
    int t = t1; // ����һ���м����,�����������
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
        int t2 = U(); // �ڶ���������
        V[j].name = "tmp" + num_str(1000-j);
        V[j].type = V[t].type;
        int t3 = t; // ��һ��������
        t = j--; // �����м����
        if(V[t].type != V[t2].type) // �жϲ�������ĺ����ɵ���ֵ�Ƿ�Ϊͬһ����
        {
            cout << "������� �������Ͳ�ƥ��" << endl;
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
        cout << "�﷨���� δ�ҵ�<����>" << endl;
    return t1;
}

int P() // -> 21|22|23|14|15
{
    int num;
    if(sym>=21 && sym<=23)
    {
        cout << "<ID or NUM> succeed " << endl;
        if(sym == 21) // ����ı�����
            num = get_num(); // �õ���������������
        else // ���͡������� ����
        {
            V[1000+reg].value = code_str[x-1];
            V[1000+reg].type = sym - 18; // 22-18=4 -> int  23-18=5 -> double
            num = 1000 + reg; // ���ص��Ǵ洢�������Ԫ�ص��±�
            reg++;
        }
        sym = getsym();
        return num;
    }
    else if(sym==14 || sym==15) // true or false
    {
        cout << "'true' or 'false' succeed " << endl;
        V[1000+reg].value = code_str[x-1];
        V[1000+reg].type = 7; // bool����
        num = 1000 + reg;
        reg++;
        sym = getsym();
        return num;
    } 
    else
    {
        cout << "�﷨���� δ�ҵ�<ID|NUM>" << endl;
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
        fscanf(fp, "%d %s", &n, str); //��ȡ��Ԫʽ
        code_num[k] = n; //�洢�ֱ���
        code_str[k] = str; //�洢����
        k++;
    }
    fclose(fp);

    sym = getsym(); //��ȡһ�����ʣ��õ����ֱ���
    cout << "�﷨������" << endl;
    A();

    fp=fopen(file_out,"w");
    cout << endl << "�����Ԫʽ��" << endl;
    for(int i=0; i<row; i++)
    {
        fprintf(fp,"(%s,%s,%s,%s)\n",Quadruples[i][0].c_str(),Quadruples[i][1].c_str(),Quadruples[i][2].c_str(),Quadruples[i][3].c_str());
        printf("(%s,%s,%s,%s)\n",Quadruples[i][0].c_str(),Quadruples[i][1].c_str(),Quadruples[i][2].c_str(),Quadruples[i][3].c_str());
    }
    fclose(fp);

    return 0;
}
