#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;  

/*??????????*/
char file_in[] = "./test1.c"; 
char file_out[] = "./test1_Analysis.txt"; 
/*?????????????????????????*/
char ch; 
char token[10]; 
int syn = 52; 
/*??????*/
int n = 0;
int m = 0;
int sum_int = 0;
float sum_float = 0.0;
int row = 1; //????????
/*??????*/
const int reserve_num = 17; //?????????
char reserve[reserve_num][10] = 
{
    "main", "return",
    "void", "int", "double", "char", "bool",
    "if", "else", "while", "for", "break", "continue",
    "true", "false",
    "read", "write"
};

void scan(FILE *fp)
{
    /*1.????? or ?????? 2.???? 3.???? 4.????*/
    for(n=0; n<10; n++)
        token[n] = '\0'; //?????????????????
    ch = fgetc(fp); //?????????????
    while(ch==' '||ch=='\t')
        ch = fgetc(fp); //??????????
 
    /*1.????? or ??????*/
    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
    {
        m = 0;
        do
        {
            token[m++] = ch;
            ch = fgetc(fp);
        }while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch=='_'));
        fseek(fp, -1, SEEK_CUR); //?????????????????????????????????
        token[m] = '\0'; //??????????
        syn = 21; //????? ?????
        for(n=0; n<reserve_num; n++)
            if(strcmp(token, reserve[n])==0) //??????????????
            {
                syn = n+1; //?????? ?????
                break;
            }
    }
    /*2.????*/
    else if(ch>='0' && ch<='9')
    {
        sum_int = 0;
        sum_float = 0.0;
        while(ch>='0' && ch<='9')
        {
            sum_int = sum_int * 10 + ch - '0';
            ch = fgetc(fp);
        }
        if(sum_int > 2147483647) //???????????????????
            syn = -1; //????
        else 
        {
            if(ch == '.') //?????????
            {
                int cnt = 0; //??????????????
                sum_float = float(sum_int);
                ch = fgetc(fp);
                while(ch>='0' && ch<='9')
                {
                    sum_float += (ch-'0') / pow(10, ++cnt);
                    ch = fgetc(fp);
                }
                syn = 23; //?????????
            }
            else
                syn = 22; //???????   
        }
        fseek(fp, -1, SEEK_CUR);
    }
    /*3.????*/
    else if(ch == '-')
    {
        fseek(fp, -2, SEEK_CUR); 
        ch = fgetc(fp); //???'-'????
        if(ch>='0' && ch<='9') //'-'?????????????????????????
        {
            ch = fgetc(fp);
            token[0] = ch; //??'-'??????????
            syn = 32; //'-'???????
        }
        else
        {
            fseek(fp, 1, SEEK_CUR); //????'-'???
            ch = fgetc(fp); //'-'?????
            if(ch>='0' && ch<='9')
            {
                sum_int = 0;
                sum_float = 0.0;
                while(ch>='0' && ch<='9')
                {
                    sum_int = sum_int * 10 + ch - '0';
                    ch = fgetc(fp);
                }
                if(sum_int > 2147483647) //???????????????????
                    syn = -1; //????
                else 
                {
                    if(ch == '.') //?????????
                    {
                        int cnt = 0; //??????????????
                        sum_float = float(sum_int);
                        ch = fgetc(fp);
                        while(ch>='0' && ch<='9')
                        {
                            sum_float += (ch-'0') / pow(10, ++cnt);
                            ch = fgetc(fp);
                        }
                        sum_float = -sum_float; //???????
                        syn = 23; //?????????
                    }
                    else
                    {
                        sum_int = -sum_int; //???????
                        syn = 22; //???????
                    }  
                }
                fseek(fp, -1, SEEK_CUR);
            }
        }
    }
    /*4.????*/
    else switch(ch)
    {
        case'/': token[0] = ch;
                 ch = fgetc(fp);
                 if(ch == '/') //"//"????
                 {
                     while(fgetc(fp) != '\n');
                     syn = -3; // ??? ???????
                 }
                 else if(ch == '*') // "/**/"????
                 {
                     while(1)
                     {
                         while(fgetc(fp) != '*');
                         if(fgetc(fp) == '/')
                            break;
                     }   
                     syn = -3; // ??? ???????               
                 }
                 else
                 {
                     syn = 34; // '/' ???????
                     fseek(fp, -1, SEEK_CUR);
                 }
                 break;
        case'<': token[0] = ch;
                 ch = fgetc(fp);
                 if(ch == '=')
                 {
                     token[1] = ch;
                     syn = 39; // <= ???????
                 }
                 else
                 {
                     syn = 37; // < ???????
                     fseek(fp, -1, SEEK_CUR);
                 }
                 break;
        case'>': token[0] = ch;
                 ch = fgetc(fp);
                 if(ch == '=')
                 {
                     token[1] = ch;
                     syn = 41; // >= ???????
                 }
                 else
                 {
                     syn = 40; // > ???????
                     fseek(fp, -1, SEEK_CUR);
                 }
                 break;
        case'=': token[0] = ch;
                 ch = fgetc(fp);
                 if(ch == '=')
                 {
                     token[1] = ch;
                     syn = 42; // == ???????
                 }
                 else
                 {
                     syn = 36; // = ???????
                     fseek(fp, -1, SEEK_CUR);
                 }
                 break;
        case'!': token[0] = ch;
                 ch = fgetc(fp);
                 if(ch == '=')
                 {
                     token[1] = ch;
                     syn = 38; // != ???????
                 }
                 else
                 {
                     syn = 43; // ! ???????
                     fseek(fp, -1, SEEK_CUR);
                 }
                 break;
        case'*': syn=33;
                 token[0]=ch;
                 break;
        case'+': syn=31;
                 token[0]=ch;
                 break;
        case':': syn=35;
                 token[0]=ch;
                 break;
        case';': syn=44;
                 token[0]=ch;
                 break;
        case',': syn=45;
                 token[0]=ch;
                 break;
        case'{': syn=46;
                 token[0]=ch;
                 break;
        case'}': syn=47;
                 token[0]=ch;
                 break;
        case'[': syn=50;
                 token[0]=ch;
                 break;
        case']': syn=51;
                 token[0]=ch;
                 break;
        case'(': syn=48;
                 token[0]=ch;
                 break;
        case')': syn=49;
                 token[0]=ch;
                 break;
        case'#': syn=52;
                 token[0]=ch;
                 break;
        case'"': syn=53;
                 token[0]=ch;
                 break;
        case'.': syn=54;
                 token[0]=ch;
                 break;
        case'%': syn=55;
                 token[0]=ch;
                 break;
        case'&': syn=56;
                 token[0]=ch;
                 break;
        case'|': syn=57;
                 token[0]=ch;
                 break;
        case'\n': syn=-2; //??????????????
                  break;
        case EOF: syn=0; //??????????
                  break; 
        default:  syn=-1; //?????
                  break; 
    }
}

int main()
{
    FILE *fp1 = fopen(file_in, "r");  //??????????
    FILE *fp2 = fopen(file_out, "w"); //???????????????
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

    cout << "?????" << endl;
    while((ch = fgetc(fp1)) != EOF) //????????????
        cout << ch;

    cout << endl << endl;
    cout << "????????????" << endl;
    fseek(fp1, 0L, SEEK_SET); //??????????????????
    
    scan(fp1);
    while(syn != 0)
    {
        switch(syn)
        {
            case 22: cout << syn << " " << sum_int <<endl; //????
                     fprintf(fp2, "%d %d\n", syn, sum_int);
                     break;
            case 23: cout <<syn << " " << sum_float <<endl; //??????
                     fprintf(fp2, "%d %f\n", syn, sum_float);
                     break;
            case -1: cout << "Error in row " << row << "!" << endl; //????
                     fprintf(fp2, "Error in row %d!\n", row);
                     break;
            case -2: row++; //????????
                     break;
            case -3: break; //??????
            case 0:  break; //??????????
            default: cout << syn << " " << token << endl; //????? or ??????
                     fprintf(fp2, "%d %s\n", syn, token);
                     break;
        }
        scan(fp1);
    }
   
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}