#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 100

void create_matrix(int A[][MAXSIZE], int line , int col)
{

    srand(time(NULL));
    A=malloc(sizeof(int)*line*col);
    if(A==NULL)
    {
        perror("Nu s-a alocat spatiu");
        exit(-1);
    }
    for(int i=0 ; i<line ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
            A[i][j]=rand()%100;
            if(rand() %2==0)
            {
                A[i][j]=-A[i][j];
            }
        }
    }
    for(int i=0 ; i<line ; i++)
    {
        printf("\n");
        for(int j=0 ; j<col ; j++)
        {
            printf("%d  ", A[i][j]);
        }
    }

    printf("\n");
    printf("\n");
    printf("\n");
   
    

}


void sort_lines(int A[][MAXSIZE], int line , int col)
{
    int s[line];

    
    for(int i=0 ; i<line ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
            s[i]=s[i]+A[i][j];
        }
    }


    for(int i=0 ; i<line-1 ; i++)
    {
        for(int j=i+1 ; j<line ; j++)
        {
            if(s[i]>s[j])
            {
                for(int a=0 ; a<col ; a++)
                {
                    int aux;
                    aux=A[i][a];
                    A[i][a]=A[j][a];
                    A[j][a]=aux;
                }
            }
        }
    }
    for(int i=0 ; i<line ; i++)
    {
        printf("\n");
        for(int j=0 ; j<col ; j++)
        {
            printf("%d  ", A[i][j]);
        }
    }
}


int main()
{
    int line=3,col=3;
    int A[line][col];
    create_matrix(A,line,col);
    sort_lines(A,line,col);
    return 0;
}