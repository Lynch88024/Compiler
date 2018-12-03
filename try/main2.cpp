#include "syntactic_analyzer.cpp"

int main()
{
    lexical LEX; // 词法类
    syntactic SYN; // 语法类
    quaternary QUA; // 四元式类
    FILE* fp;
    if((fp=fopen(file_in, "r")) == NULL)
    {
        cout << "Open the file failed!" << endl;
        exit(0);
    }
    LEX.save(fp);  
    fclose(fp);

    SYN.sym = LEX.getsym(); //读取一个单词，得到其种别码
    cout << "语法分析：" << endl;
    SYN.A();

    fp = fopen(file_out, "w");
    cout << endl << "输出四元式：" << endl;
    QUA.disp(fp);
    fclose(fp);

    return 0;
}