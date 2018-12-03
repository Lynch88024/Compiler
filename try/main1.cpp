#include "lexical_analyzer.cpp"

int main()
{
    FILE *fp1 = fopen(file_in, "r");  //��Դ�����ļ�
    FILE *fp2 = fopen(file_out, "w"); //�ʷ�����������ļ�
    if(fp1 == NULL)
    {
        cout << "open the file_in failed!" << endl;
        exit(0);
    }
    if(fp2 == NULL)
    {
        cout << "open the file_out failed!" << endl;
        exit(0);
    }

    cout << "Դ����" << endl;
    while((ch = fgetc(fp1)) != EOF) //��ʾԴ��������
        cout << ch;

    cout << endl << endl;
    cout << "�ʷ����������" << endl;
    fseek(fp1, 0L, SEEK_SET); //�������Դ�����ļ���ͷ
    
    scan(fp1);
    while(syn != 0)
    {
        switch(syn)
        {
            case 22: cout << syn << " " << sum_int <<endl; //����
                     fprintf(fp2, "%d %d\n", syn, sum_int);
                     break;
            case 23: cout <<syn << " " << sum_float <<endl; //������
                     fprintf(fp2, "%d %f\n", syn, sum_float);
                     break;
            case -1: cout << "Error in row " << row << "!" << endl; //����
                     fprintf(fp2, "Error in row %d!\n", row);
                     break;
            case -2: row++; //��������
                     break;
            case -3: break; //ע�Ͳ���
            case 0:  break; //�ļ���ȡ����
            default: cout << syn << " " << token << endl; //��ʶ�� or ������
                     fprintf(fp2, "%d %s\n", syn, token);
                     break;
        }
        scan(fp1);
    }
   
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}