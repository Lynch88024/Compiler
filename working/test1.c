/*��С�ڵ���n�������Ľ׳˵ĺ�*/
int main() 
{
    int n=5;
    int sum=0;
    int factorial=1;
    for(int i=1;i<=n;i=i+1)
    {
        factorial=factorial*i;
        sum=sum+factorial;
    }
    return sum;
}
