#include "syntactic_analyzer.cpp"

int main()
{
    lexical LEX; // �ʷ���
    syntactic SYN; // �﷨��
    quaternary QUA; // ��Ԫʽ��
    FILE* fp;
    if((fp=fopen(file_in, "r")) == NULL)
    {
        cout << "Open the file failed!" << endl;
        exit(0);
    }
    LEX.save(fp);  
    fclose(fp);

    SYN.sym = LEX.getsym(); //��ȡһ�����ʣ��õ����ֱ���
    cout << "�﷨������" << endl;
    SYN.A();

    fp = fopen(file_out, "w");
    cout << endl << "�����Ԫʽ��" << endl;
    QUA.disp(fp);
    fclose(fp);

    return 0;
}