
/*
Se cere o valoare reala cu maxim 2 zecimale, care reprezinta o suma de lei. Sa se afiseze cum poate fi aceasta suma platita cu bancnotele si monedele aflate in circulatie, 
astfel incat numarul total de bancnote si de monede sa fie minim:
*/



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float suma;
    printf("Dati o suma de bani:");
    scanf("%f",&suma);
    float v[10]={500,200,100,50,10,5,1,0.5,0.1,0.01};
    int i=0;
    int nr=0;
    while(suma)
    {
        while(suma>=v[i])
        {
            suma=suma-v[i];
            nr++;
        }

    printf("\n%d bancnote/monede de %f" , nr , v[i]);
    i++;
    nr=0;

    }
    return 0;
}