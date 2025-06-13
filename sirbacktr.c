#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 21
#define DIC_LENGTH 10
char s[WORD_SIZE];
char dictionar[DIC_LENGTH][WORD_SIZE];
char cuv[DIC_LENGTH][WORD_SIZE];
int nr_cuv=0;
int cuv_len=0;

bool isvalid(char *cuv)
{
    for(int i=0 ; i<DIC_LENGTH ; i++)
    {
        if(strcmp(cuv,dictionar[i])==0)
        {
            return true;
        }
    }
    return false;
}

bool backtracking(int n , int k)
{
    if(k==n)
    {
        for(int i=0 ; i<cuv_len ; i++)
        {
            printf(" %s" ,cuv[i]);
        }
        return true;
    }
    else
    {
        for(int i=k ; i<n ; i++)
        {
            int length=i-k+1;
            if(length>=WORD_SIZE)
            {
                continue;
            }
            char word[WORD_SIZE];
            strncpy(word,s+k,length);
            word[length]='\0';
            if(isvalid(word))
            {
                strcpy(cuv[cuv_len],word);
                cuv_len++;
            if(backtracking(n,i+1))
            {
                return true;
            }
            cuv_len--;
                
            }
        
        }
    }
    return false;
}


int main()
{   

    strcpy(s,"applepenthisisia");
    strcpy(dictionar[0], "this");
    strcpy(dictionar[1], "is");
    strcpy(dictionar[2], "a");
    strcpy(dictionar[3], "test");
    strcpy(dictionar[4], "program");
    strcpy(dictionar[5], "apple");
    strcpy(dictionar[6], "pen");
    int n=strlen(s);
    bool verificare=backtracking(n,0);
    if(!verificare)
    {
        printf("Nu exista solutie");
    }

    
    return 0;
}