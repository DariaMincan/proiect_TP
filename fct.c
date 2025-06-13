#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define low 2
#define high 10
#define p 4

bool f(int x)
{
    return x>=p;
}

int cautare(int l , int r)
{
    if(l==r)
    {
        if(f(l))
        {
            return l;
        }
        else
        {
            return -1;
        }
    }

    int m=(l+r)/2;
    if(f(m))
    {
        cautare(l,m);

    }
    else
    {
        cautare(m+1,r);
    }
    return -1;
    

}
int main()
{
    int rezultat=cautare(low,high);
    if(rezultat==-1)
    {
        printf("Nu are solutie");
    }
    else
    {
        printf("Rezultatul este %d", rezultat);
    }
    return 0;
}