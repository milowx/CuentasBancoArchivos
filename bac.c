/*
Txt
[Nombre del titular][Numero de cuenta][Numero De Tarjeta][Saldo][Interes]
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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

//VARIABLES GLOABLES
Cuenta cuentas[TAM];
int cuentas_leidas=0;
FILE* parchivo;

void leer_archivo(void){
    parchivo=fopen("banco.txt", "rt");

    while((fscanf(parchivo, "%s %s %ld %ld %lf %lf %s", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
        &cuentas[cuentas_leidas].num_cuenta, &cuentas[cuentas_leidas].num_tarjeta, &cuentas[cuentas_leidas].saldo, 
        &cuentas[cuentas_leidas].interes, &cuentas[cuentas_leidas].genero)==7)){

        cuentas_leidas++;
    }

    fclose(parchivo);
}

void actualizar_archivo(void){
    parchivo=fopen("banco.txt", "wt");
    for(int i=0; i<cuentas_leidas; i++){
        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[i].pnombre, cuentas[i].apellido, 
            cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, 
            cuentas[i].interes, cuentas[i].genero);
    }
    fclose(parchivo);
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

int pedir_cuenta(void){
    int num;
    do{
        printf("\n\tIngrese el numero de cuenta o numero de tarjeta[8 digitos]: ");
        scanf("%d", &num);
        if(num<10000000){
            printf("\n\tIngrese un numero de 8 digitos.\n\t");
        }
    }while(num<10000000);
    return num;
}


int buscar(int num){//regresa el indice de la cuenta
    int indice;
    bool encontrado=false;
    for(int i=0;i<cuentas_leidas;i++){
        if((cuentas[i].num_cuenta==num)||(cuentas[i].num_tarjeta==num)){
            indice = i;
            encontrado=true;
            break;
        }
    }
    
    if(encontrado){
        return indice;
    }else{
        return -1;
    }
}

void mostrar_una_cuenta(int indice_cuenta){
    printf("\n\t%s      %s        %c          %ld         %ld        %.2lf         %.2lf\n",
    cuentas[indice_cuenta].pnombre, cuentas[indice_cuenta].apellido, cuentas[indice_cuenta].genero,
    cuentas[indice_cuenta].num_cuenta, cuentas[indice_cuenta].num_tarjeta, cuentas[indice_cuenta].saldo, cuentas[indice_cuenta].interes);
}

void transferir(void){
    int ncuenta_origen, ncuenta_destino, icuenta_origen, icuenta_destino;
    char respuesta;
    double cantidad;

    do{
        printf("\n\tCUENTA ORIGEN:");
        ncuenta_origen = pedir_cuenta();
        printf("\n\tCUENTA DESTINO:");
        ncuenta_destino = pedir_cuenta();
        icuenta_origen = buscar(ncuenta_origen);
        icuenta_destino = buscar(ncuenta_destino);
        if((icuenta_destino==-1) || (icuenta_origen==-1)){
            printf("\n\tCuentas no encontradas!");    
        }else{
            if(cuentas[icuenta_origen].saldo<=0){
                printf("\n\tSaldo No Disponible!");
                mostrar_una_cuenta(icuenta_origen);
            }else{
                printf("\n\tCUENTA ORIGEN");
                mostrar_una_cuenta(icuenta_origen);
                printf("\n\tCUENTA DESTINO");
                mostrar_una_cuenta(icuenta_destino);
                do{
                    printf("\n\tIngrese la cantidad a transferir a la cuenta destino: ");
                    scanf("%lf", &cantidad);
                    if(cantidad<=0){
                        printf("\n\t\aERROR: Ingrese un numero positivo.\n\t");
                    }else if(cantidad>cuentas[icuenta_origen].saldo){
                        printf("\n\t\aERROR: La cantidad excede el saldo disponible.\n\t");
                    }
                }while(cantidad<=0 || cantidad>cuentas[icuenta_origen].saldo);

                cuentas[icuenta_origen].saldo-=cantidad;
                cuentas[icuenta_destino].saldo+=cantidad;
                printf("\n\tTransferencia exitosa de: L.%.2lf", cantidad);
                printf("\n\tCUENTA ORIGEN");
                mostrar_una_cuenta(icuenta_origen);
                printf("\n\tCUENTA DESTINO");
                mostrar_una_cuenta(icuenta_destino);
            }
        }

        printf("\n\tDesea realilzar otra transaccion?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');
    actualizar_archivo();
}

void borrar(void){
    char respuesta;
    int indice_cuenta;

    do{
        printf("\n\tBORRAR CUENTAS");
        int num=pedir_cuenta();
        indice_cuenta=buscar(num);

        if(indice_cuenta==-1){
            printf("\n\tCuenta No Encontrada");
        }else{
            printf("\n\n\tCuenta Eliminada!");
            mostrar_una_cuenta(indice_cuenta);
            for(int j=indice_cuenta; j<cuentas_leidas-1;j++){
                cuentas[j]=cuentas[j+1];
            }
            cuentas_leidas--;
        }

        printf("\n\tDesea borrar otra cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');

    actualizar_archivo();
}

void buscar_una_cuenta(){
    char respuesta;
    int num, indice_cuenta;

    do{
        num=pedir_cuenta();
        indice_cuenta=buscar(num);

        if(indice_cuenta==-1){
            printf("\n\tCuentra no encontrada");
        }else{
            printf("\n\n\tCuenta Encontrada!");
            mostrar_una_cuenta(indice_cuenta);
        }

        printf("\n\tDesea buscar otra cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');

    }while(respuesta=='S');
}

void mostrar_todo(void){
    printf("\n\tNOMBRE    APELLIDO     GENERO       NUMERO DE CUENTA      NUMERO DE TARJETA         SALDO       INTERES");
    for(int i=0; i<cuentas_leidas; i++){
        printf("\n\t%s      %s        %c          %ld         %ld        %.2lf         %.2lf",
        cuentas[i].pnombre, cuentas[i].apellido, cuentas[i].genero,
        cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, cuentas[i].interes);
    }
}

void ingresar(void){
    char respuesta;

    parchivo=fopen("banco.txt", "at");
    do{
        printf("\n\tINGRESANDO CUENTA #%d", cuentas_leidas+1);
        printf("\n\tIngrese el primer nombre del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].pnombre);

        printf("\n\tIngrese el apellido del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].apellido);

        printf("\n\tIngrese el genero del titular de la cuenta[M/F]: ");
        validar_char(&cuentas[cuentas_leidas].genero, 'M', 'F');

        printf("\n\tIngrese el numero de cuenta: ");
        validar_int(&cuentas[cuentas_leidas].num_cuenta, 10000000);

        printf("\n\tIngrese el numero de tarjeta: ");
        validar_int(&cuentas[cuentas_leidas].num_tarjeta, 10000000);

        printf("\n\tIngrese el saldo de la cuenta: ");
        scanf("%lf", &cuentas[cuentas_leidas].saldo);

        printf("\n\tIngrese el interes de la cuenta: ");
        validar_fl(&cuentas[cuentas_leidas].interes, 0);

        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
            cuentas[cuentas_leidas].num_cuenta, cuentas[cuentas_leidas].num_tarjeta, cuentas[cuentas_leidas].saldo, 
            cuentas[cuentas_leidas].interes, cuentas[cuentas_leidas].genero);
        cuentas_leidas++;

        printf("\n\tDesea Ingresar Una Nueva Cuenta?[S/N]: ");
        validar_char(&respuesta, 'S', 'N');
    }while(respuesta=='S');

    fclose(parchivo);
}

void menu(void){
    int dec;
    do{
        do{
            printf("\n\tMENU");
            printf("\n\t[1]...Ingresar Una Nueva Cuenta");
            printf("\n\t[2]...Borrar Una Cuenta");
            printf("\n\t[3]...Mostrar Cuentas Activas");
            printf("\n\t[4]...Buscar Una Cuenta");
            printf("\n\t[5]...Hacer transferencia");
            printf("\n\t[6]...Salir\n\t");
            scanf("%d", &dec);
            if(dec<1||dec>6){
                printf("\n\t\aERROR:Ingrese un digito entre 1-7\n\t");
            }
        }while(dec<1||dec>6);

        switch(dec){
            case 1:
                ingresar();
                break;
            case 2:
                borrar();
                break;
            case 3:
                mostrar_todo();
                break;
            case 4:
                buscar_una_cuenta();
                break;
            case 5:
                transferir();
                break;
            default:
                fclose(parchivo);
                printf("\n\tGracias por utilizar nuestro sistema!\n");
                exit(0);
                break;
        }
    }while(dec!=6);
}

int main(void){
    parchivo=fopen("banco.txt", "rt");
    if(!parchivo){
        parchivo=fopen("banco.txt", "wt");
    }else{
        leer_archivo();
    }
    fclose(parchivo);
    menu();
    return 0;
}