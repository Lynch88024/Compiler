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

/*----�ķ���������----*/   
void A(); // <������> -> int main()<����> 
void C(); // <����> -> <��������> <������>()<����>
void D(); // <��������> -> void|int|double|char|bool
void S(); // <��������> -> void|int|double|char
void E(); // <������> -> ID
void B(); // <����> -> {(<����>|<��䴮>)*}
void F(); // <��䴮> -> <���>(<���>)*
void G(); // <���> -> <�������>|<��ֵ���>|<�������>|<ѭ�����>|<�������>
void O();
void R(); // <��ֵ���ʽ> -> ID = (<�������ʽ>|<�������ʽ>) 
void H(); // <��ֵ���> -> <��ֵ���ʽ>; 
void I(); // <�������> -> if(<�������ʽ>) (<����>|<���>) else(<����>|<���>)
          //             | if(<�������ʽ>) (<����>|<���>) 
void J();  
void Q(); // <�������> -> return (<�������ʽ>|<�������ʽ>);
void L(); // <�������ʽ> -> <������>(||<������>)*
void W(); // <������> -> <��������>(&&<��������>)*
void X(); // <��������> -> (<�������ʽ>)
          //             | <�������ʽ> relop <�������ʽ>
          //             | <ID|NUM>
void K(); // <�������ʽ> -> <��>(+<��>)* | <��>(-<��>)*
void T(); // <��> -> <����>(*<����>)* | <����>(/<����>)*
void U(); // <����> -> (<�������ʽ>) | <ID|NUM> 
void P(); // <ID|NUM> -> ID|NUM|true|false

int getsym()
{
    return code_num[x++]; //��ȡ��һ������
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
    cout << sym <<  endl;
   // A();

    return 0;
}
