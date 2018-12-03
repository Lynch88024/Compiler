#include "lexical_analyzer.cpp"

int main()
{
    FILE *fp1 = fopen(file_in, "r");  //打开源代码文件
    FILE *fp2 = fopen(file_out, "w"); //词法分析器输出文件
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

    cout << "源程序" << endl;
    while((ch = fgetc(fp1)) != EOF) //显示源程序内容
        cout << ch;

    cout << endl << endl;
    cout << "词法分析器输出" << endl;
    fseek(fp1, 0L, SEEK_SET); //光标移至源代码文件开头
    
    scan(fp1);
    while(syn != 0)
    {
        switch(syn)
        {
            case 22: cout << syn << " " << sum_int <<endl; //整型
                     fprintf(fp2, "%d %d\n", syn, sum_int);
                     break;
            case 23: cout <<syn << " " << sum_float <<endl; //浮点型
                     fprintf(fp2, "%d %f\n", syn, sum_float);
                     break;
            case -1: cout << "Error in row " << row << "!" << endl; //报错
                     fprintf(fp2, "Error in row %d!\n", row);
                     break;
            case -2: row++; //增加行数
                     break;
            case -3: break; //注释部分
            case 0:  break; //文件读取结束
            default: cout << syn << " " << token << endl; //标识符 or 保留字
                     fprintf(fp2, "%d %s\n", syn, token);
                     break;
        }
        scan(fp1);
    }
   
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}