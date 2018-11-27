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
string code_str[1000];
/*һЩȫ�ֱ���*/
int x = 0; // x�ǵ��������еļ�����
int sym = 52; // sym�Ǹõ��ʵ��ֱ���
/*��Ԫʽ*/
string Quadruples[500][4]; 
int row = 0;

/*----�ķ���������----*/   
void A(); // <������> -> int main()<����> 
void C(); // <����> -> <��������> <������>()<����>
void D(); // <��������> -> void|int|double|char|bool
void S(); // <��������> -> void|int|double|char
void E(); // <������> -> ID
void B(); // <����> -> {(<����>|<��䴮>)*}
void F(); // <��䴮> -> <���>(<���>)*
void G(); // <���> -> <�������>|<��ֵ���>|<�������>|<ѭ�����>|<�������>
void O(); // <�������>
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

void O()
{

}

void H() // -> R 44
{

}

void I() // -> 8 48 L 49 (G|B) (( 9 (G|B) ) | �� )
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
        fscanf(fp, "%d %s", &n, str); //��ȡ��Ԫʽ
        code_num[k] = n; //�洢�ֱ���
        code_str[k] = str; //�洢����
        k++;
    }
    fclose(fp);

    sym = getsym(); //��ȡһ�����ʣ��õ����ֱ���
    cout << "�﷨������" << endl;
    A();

    return 0;
}
