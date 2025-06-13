#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define numar_cuvinte 3


char cuvinte[3][10];
bool used_digit[10];
int map_letter[256];
char frecventa[256]={0};
char litere[256];
bool prima_litera[256];
int nr_sol=0;
int numar_litere=0;

int valoare_cuvant(char *cuvant)
{
    int valoare=0;
    int lungime=strlen(cuvant);
    for(int i=0 ; i<lungime ; i++)
    {
        valoare=valoare*10+map_letter[(int)cuvant[i]];
    } 
    return valoare;
}

void print_solutie()
{
    nr_sol=1;
    printf("Solutie gasita:\n");
   
    for(int i = 0 ; i < numar_litere ; i++) 
    {
        printf("%c = %d", litere[i], map_letter[(int)litere[i]]);
        if(i < numar_litere - 1)
        {
            printf(", ");
        }
    }
    printf("\n");

    
    for(int i = 0 ; i < numar_cuvinte - 1 ; i++) 
    {
        long long val = valoare_cuvant(cuvinte[i]);
        printf("%lld", val);
        if(i < numar_cuvinte - 2) 
        {
            printf(" + ");
        }
        printf("\n"); 
    }
    printf("----------\n"); 
    long long val_rezultat = valoare_cuvant(cuvinte[numar_cuvinte - 1]); 
    printf("%lld\n\n", val_rezultat);
}

bool encriptie(int k)
{
    if(k==numar_litere)
    {
        
        int suma=0;
        for(int i=0 ; i<numar_cuvinte-1 ; i++)
        {
            suma=suma+valoare_cuvant(cuvinte[i]);
        }
        int val_cuvant_rezultat=valoare_cuvant(cuvinte[numar_cuvinte-1]);
        if(suma==val_cuvant_rezultat)
        {
            print_solutie(); 
            return true;
        }
        return false;
        
    }
    else
    {
        char litera_curenta=litere[k];
        for(int i=0 ; i<10 ; i++)
        {
            if(used_digit[i])
            {
                continue;
            }
            if(i==0 && prima_litera[(int)litera_curenta])
            {
                continue;
            }
            map_letter[(int)litera_curenta]=i;
            used_digit[i]=true;
            if(encriptie(k+1))
            {
                return true;
            }
            map_letter[(int)litera_curenta]=-1;
            used_digit[i]=false;
            
        }
        
        
    }
    return false;
}

int main()
{

    for(int i = 0 ; i < 256 ; i++)
    {
        map_letter[i] = -1; 
        prima_litera[i] = false; 
    }
  
    strcpy(cuvinte[0],"CROSS");
    strcpy(cuvinte[1],"ROADS");
    strcpy(cuvinte[2],"DANGER");

    for(int i=0 ; i<3 ; i++)
    {
        int lungime_cuvant=strlen(cuvinte[i]);
        for(int j=0 ; j<lungime_cuvant ; j++)
        {
            if(j==0)
            {
                prima_litera[(int)cuvinte[i][0]]=true;
            }
            if(frecventa[(int)cuvinte[i][j]]==0)
            {
                litere[numar_litere]=cuvinte[i][j];
                numar_litere++;
            }
            frecventa[(int)cuvinte[i][j]]++;
        }

    }
    litere[numar_litere]='\0';

    for(int i=0 ; i<10 ; i++)
    {
        used_digit[i]=false;
    }
    printf("Cautare solutii pentru: ");
    for(int i = 0; i < numar_cuvinte - 1; i++) {
        printf("%s", cuvinte[i]);
        if (i < numar_cuvinte - 2) printf(" + ");
    }
    printf(" = %s\n\n", cuvinte[numar_cuvinte - 1]);


    printf("Litere distincte: %s\n", litere);
    printf("Numar de litere distincte: %d\n\n", numar_litere);
    encriptie(0);
    if(nr_sol==0)
    {
        printf("\nNu s-a gasit nicio solutie\n");
    }
    return 0;
}