#include "interpretive_analyzer.cpp"

int main()
{
    transform TRA; // ����ת����
    lexical LEX; // �ʷ���
    interpreter INT; // ���ͳ�����
    output OUT; // ��������
    
    FILE* fp;
    if((fp=fopen(file_in, "r")) == NULL)
    {
        cout << "Open the file failed!" << endl;
        exit(0);
    }
    LEX.save(fp);  
    fclose(fp);

    INT.sym = LEX.getsym(); // ��ȡһ�����ʣ��õ����ֱ���
    cout << "�﷨������" << endl;
    INT.A();

    fp = fopen(file_out, "w");
    OUT.define(fp); // ����������
    OUT.middle(fp); // ����м����
    OUT.answer(fp); // ������н��
    fclose(fp);

    return 0;
}