//[Nombre del titular][Numero de cuenta][Numero De Tarjeta][Saldo][Interes][GENERO]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "linker.h"

typedef struct{
    char pnombre[50];
    char apellido[50];
    unsigned long int num_cuenta;
    unsigned long int num_tarjeta;
    double saldo;
    double interes;
    char genero;
}Cuenta;

Cuenta cuentas[TAM-15];
FILE *parchivo;

void llenar_struct(){
    parchivo=fopen("banco.txt", "wt");
    for(int i=0; i<(TAM-15); i++){
        Cuenta *cta_actual = &cuentas[i];//Guardando cuenta actual

        cta_actual->genero=(rand()%2)?'M':'F';

        if(cta_actual->genero==70){//ascii para F
            strcpy(cta_actual->pnombre, NOMBRES_F[rand()%100]);//hay 100 nombres femeninos
        }else{
            strcpy(cta_actual->pnombre, NOMBRES_M[rand()%100]);
        }

        strcpy(cta_actual->apellido, APELLIDOS[rand()%200]);

        cta_actual->num_cuenta=10000000+rand()%99999999;

        cta_actual->num_tarjeta=12345678+rand()%99999999;

        cta_actual->saldo=-10000+rand()%20001;

        cta_actual->interes=1+rand()%11;

        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cta_actual->pnombre, cta_actual->apellido, 
            cta_actual->num_cuenta, cta_actual->num_tarjeta, cta_actual->saldo, 
            cta_actual->interes, cta_actual->genero);
        printf("\n\tCuenta #%d Ingresada!", i+1);
    }
    fclose(parchivo);
}

int main(){
    srand(time(NULL));
    llenar_struct();
    return 0;
}