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

void leer_archivo(){
    parchivo=fopen("banco.txt", "rt");

    while((fscanf(parchivo, "%s %s %ld %ld %lf %lf %s", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
        &cuentas[cuentas_leidas].num_cuenta, &cuentas[cuentas_leidas].num_tarjeta, &cuentas[cuentas_leidas].saldo, 
        &cuentas[cuentas_leidas].interes, &cuentas[cuentas_leidas].genero)==7)){

        cuentas_leidas++;
    }

    fclose(parchivo);
}

void actualizar_archivo(){
    parchivo=fopen("banco.txt", "wt");
    for(int i=0; i<cuentas_leidas; i++){
        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[i].pnombre, cuentas[i].apellido, 
            cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, 
            cuentas[i].interes, cuentas[i].genero);
    }
    fclose(parchivo);
}

char validar_char(char* letra, char opc1, char opc2){

}

int pedir_cuenta(){
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

void transferir(){
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
        respuesta=validar_char(respuesta, 'F', 'M');

        do{
            printf("\n\tDesea realizar otra transaccion?[S/N]: ");
            scanf(" %c", &respuesta);
            respuesta=toupper(respuesta);
            if(respuesta!='S' && respuesta!='N'){
                printf("\n\tIngrese la letra S o N\n\t");
            }
        }while(respuesta!='S' && respuesta!='N');
    }while(respuesta=='S');
    actualizar_archivo();
}

void borrar(){
    Cuenta buffer;
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

        do{
            printf("\n\tDesea borrar otra cuenta?[S/N]: ");
            scanf(" %c", &respuesta);
            respuesta=toupper(respuesta);

            if(respuesta!='S' && respuesta!='N'){
                printf("\n\tIngrese la letra S o N\n\t");
            }
        }while(respuesta!='S' && respuesta!='N');
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

        do{
            printf("\n\tDesea buscar otra cuenta?[S/N]");
            scanf(" %c", &respuesta);
            respuesta=toupper(respuesta);
            if(respuesta!='S' && respuesta!='N'){
                printf("\n\tIngrese la letra N o S");
            }
        }while(respuesta!='S'&&respuesta!='N');

    }while(respuesta=='S');
}

void mostrar_todo(){
    printf("\n\tNOMBRE    APELLIDO     GENERO       NUMERO DE CUENTA      NUMERO DE TARJETA         SALDO       INTERES");
    for(int i=0; i<cuentas_leidas; i++){
        printf("\n\t%s      %s        %c          %ld         %ld        %.2lf         %.2lf",
        cuentas[i].pnombre, cuentas[i].apellido, cuentas[i].genero,
        cuentas[i].num_cuenta, cuentas[i].num_tarjeta, cuentas[i].saldo, cuentas[i].interes);
    }
}

void ingresar(){
    char respuesta;

    parchivo=fopen("banco.txt", "at");
    do{
        printf("\n\tINGRESANDO CUENTA #%d", cuentas_leidas+1);
        printf("\n\tIngrese el primer nombre del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].pnombre);

        printf("\n\tIngrese el apellido del titular de la cuenta: ");
        scanf("%s", cuentas[cuentas_leidas].apellido);

        do{
            printf("\n\tIngrese el genero del titular de la cuenta[M/F]: ");
            scanf(" %c", &cuentas[cuentas_leidas].genero);
            cuentas[cuentas_leidas].genero=toupper(cuentas[cuentas_leidas].genero);
            if(cuentas[cuentas_leidas].genero!='M' && cuentas[cuentas_leidas].genero!='F'){
                printf("\n\t\aERROR: Ingrese la letra M o F\n\t");
            }
        }while(cuentas[cuentas_leidas].genero!='M' && cuentas[cuentas_leidas].genero!='F');

        do{
            printf("\n\tIngrese el numero de cuenta: ");
            scanf("%ld", &cuentas[cuentas_leidas].num_cuenta);
            if(cuentas[cuentas_leidas].num_cuenta<8){
                printf("\n\t\aERROR: Ingrese un numero de al menos 8 digitos.\n\t");
            }
        }while(cuentas[cuentas_leidas].num_cuenta<8);

        do{
            printf("\n\tIngrese el numero de tarjeta: ");
            scanf("%ld", &cuentas[cuentas_leidas].num_tarjeta);
            if(cuentas[cuentas_leidas].num_tarjeta<8){
                printf("\n\t\aERROR: Ingrese un numero de al menos 8 digitos.\n\t");
            }
        }while(cuentas[cuentas_leidas].num_tarjeta<8);

        printf("\n\tIngrese el saldo de la cuenta: ");
        scanf("%lf", &cuentas[cuentas_leidas].saldo);

        do{
            printf("\n\tIngrese el interes de la cuenta: ");
            scanf("%lf", &cuentas[cuentas_leidas].interes);
            if(cuentas[cuentas_leidas].interes<=0){
                printf("\n\t\aERROR: Ingrese un numero positivo.\n\t");
            }
        }while(cuentas[cuentas_leidas].interes<=0);

        fprintf(parchivo, "\n%10s %10s %10ld %10ld %12.2lf %12.2lf %10c", cuentas[cuentas_leidas].pnombre, cuentas[cuentas_leidas].apellido, 
            cuentas[cuentas_leidas].num_cuenta, cuentas[cuentas_leidas].num_tarjeta, cuentas[cuentas_leidas].saldo, 
            cuentas[cuentas_leidas].interes, cuentas[cuentas_leidas].genero);
        cuentas_leidas++;

        do{
            printf("\n\tDesea ingresar una nueva cuenta?[S/N]");
            scanf(" %c", &respuesta);
            respuesta=toupper(respuesta);
            if(respuesta!='S' && respuesta!='N'){
                printf("\n\t\aERROR: Ingrese la letra S o N\n\t");
            }
        }while(respuesta!='S' && respuesta!='N');
    }while(respuesta=='S');

    fclose(parchivo);
}

void menu(){
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

int main(){
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