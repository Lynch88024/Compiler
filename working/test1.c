int main()
{
    int a=2;
    if(a>0)
    {
        a=a-1;
    }
    else
        a=a+1;
    double b=3.0;
    if(b>1.0+1.0)
        b=b/2.0;
    
    b=5.0;
    while(b>0.0&b<10.0)
    {
        b=b-1.0;
    }

    b=5.0;
    for(a=2;a>0;a=a-1)
    {
        b=b+1.0;
    }

    b=5.0;
    a=0;
    int c=0;
    while(b>0.0)
    {
        for(a=2;a>0;a=a-1)
        {
            c=c+1;
        }
        b=b-2.0;
    }

    int x=3;
    x=(3+2*2-(3+-6))/5;
    x=x-2;
    double y=5.0;
    bool z=false|x&y;

    a=10;
    return a-5*3;
}