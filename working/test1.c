/*求小于等于n的整数的阶乘的和*/
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
