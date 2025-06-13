#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSIZE 100
char pattern[MAXSIZE];
char rezultat[MAXSIZE];

void print_rezultat(int n)
{
    for(int i=0 ; i<n ; i++)
    {
        printf("%c",rezultat[i]);
    }
    printf("\n");
}

bool valid(char *rezultat , int pas)
{
    if(strchr("L",pattern[pas])!=0 && isalpha(rezultat[pas]))
    {
        return true;
    }

    if(strchr("C",pattern[pas])!=0 && isdigit(rezultat[pas]))
    {
        return true;
    }
    return false;
}

void backtracking(int n , int pas)
{
    if(pas==n)
    {
        print_rezultat(n);
    }
    else
    {
        for(int i='A' ; i<='Z' ; i++)
        {
            rezultat[pas]=i;
            if(valid(rezultat,pas))
            {
                backtracking(n,pas+1);
            }
        }
        for(int i='a' ; i<='z' ; i++)
        {
            rezultat[pas]=i;
            if(valid(rezultat,pas))
            {
                backtracking(n,pas+1);
            }
        }
        for(int i=0 ; i<=9 ; i++)
        {
            rezultat[pas]=i;
            if(valid(rezultat,pas))
            {
                backtracking(n,pas+1);
            }
        }
    }
}
int main()
{
    strcpy(pattern, "LLC");
    int n=strlen(pattern);
    backtracking(n,0);
    return 0;
}