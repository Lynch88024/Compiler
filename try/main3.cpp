#include "interpretive_analyzer.cpp"

int main()
{
    transform TRA; // 类型转换类
    lexical LEX; // 词法类
    interpreter INT; // 解释程序类
    output OUT; // 输出结果类
    
    FILE* fp;
    if((fp=fopen(file_in, "r")) == NULL)
    {
        cout << "Open the file failed!" << endl;
        exit(0);
    }
    LEX.save(fp);  
    fclose(fp);

    INT.sym = LEX.getsym(); // 读取一个单词，得到其种别码
    cout << "语法分析：" << endl;
    INT.A();

    fp = fopen(file_out, "w");
    OUT.define(fp); // 输出定义变量
    OUT.middle(fp); // 输出中间变量
    OUT.answer(fp); // 输出运行结果
    fclose(fp);

    return 0;
}