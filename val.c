//funciones que validan datos de entrada
#include "linker.h"

void validar_cuenta(int* num){
    do{
        printf("\n\tIngrese el numero de cuenta o numero de tarjeta[8 digitos]: ");
        scanf("%d", num);
        if(*num<10000000){
            printf("\n\tIngrese un numero de 8 digitos.\n\t");
        }
    }while(*num<10000000);
}

void validar_menu(int* dec, int li, int ls){
    do{
        scanf("%d", dec);
        if(*dec<li || *dec>ls){
            printf("\n\t\aERROR: Ingresar un numero entre %d y %d.\n\t", li, ls);
        }
    }while(*dec<li || *dec>ls);
}

void validar_int(unsigned long int* num,unsigned long int limite){
    do{
        scanf("%ld", num);
        if(*num<=limite){
            if(limite==0){
                printf("\n\t\aERROR: Ingresar un numero positivo.\n\t");
            }else{
                printf("\n\t\aERROR: Ingrese un numero de 8 digitos.\n\t");
            }
        }
    }while(*num<=limite);
}

void validar_char(char* letra, char opc1, char opc2){
    do{
        scanf(" %c", letra);
        *letra=toupper((*letra));
        if(*letra!=opc1 && *letra!=opc2){
            printf("\n\t\aERROR:Ingresar la letra [%c]/[%c]!\n\t", opc1, opc2);
        }
    }while(*letra!=opc1 && *letra!=opc2);
}

void validar_fl(double* fl, double limite){
    do{
        scanf("%lf", fl);
        if(*fl<=limite){
            printf("\n\t\aERROR: Ingresar un numero positivo.\n\t");
        }
    }while(*fl<=limite);
}