#include "linker.h"

void ordenar_menu(void){
    int dec;
    do{
        printf("\n\t[MENU]ORDENAR POR");
        printf("\n\t[1]...Numero de Tarjeta");
        printf("\n\t[2]...Numero de Cuenta");
        printf("\n\t[3]...Saldo");
        printf("\n\t[4]...Regresar\n\t");
        validar_menu(&dec, 1, 4);//=>val.c
        
        if(dec!=4){ordenar(dec);}//=>man.c

    }while(dec!=4);
}

void leer_menu(void){
    int dec;
    do{
        printf("\n\t[MENU]LEER DATOS");
        printf("\n\t[1]...Mostrar Cuentas Activas");
        printf("\n\t[2]...Buscar una Cuenta");
        printf("\n\t[3]...Regresar\n\t");
        validar_menu(&dec, 1, 3);//=>val.c
        switch(dec){
            case 1:
                mostrar_todo();//=>mst.c
                break;
            case 2:
                buscar_una_cuenta();//=>bsc.c
                break;
            default:
                system("clear");
                break;
        }
    }while(dec!=3);
}

void modificar_menu(void){
    int dec;
    do{
        printf("\n\t[MENU]MODIFICAR DATOS");  
        printf("\n\t[1]...Ingresar una Nueva Cuenta");
        printf("\n\t[2]...Borrar Una Cuenta");
        printf("\n\t[3]...Hacer Transferencia");
        printf("\n\t[4]...Ordenar Datos");
        printf("\n\t[5]...Regresar\n\t");
        validar_menu(&dec, 1, 5);//=>val.c
        switch(dec){
            case 1:
                ingresar();//=>man.c
                break;
            case 2:
                borrar();//=>man.c
                break;
            case 3:
                transferir();//=>man.c
                break;
            case 4:
                ordenar_menu();
                break;
            default:
                system("clear");
                break;
        }
    }while(dec!=5);
}

void menu(void){
    int dec;
    do{
        printf("\n\tMENU PRINCIPAL");
        printf("\n\t[1]...Leer Cuentas");
        printf("\n\t[2]...Modificar Cuentas");
        printf("\n\t[3]...Salir\n\t");
        validar_menu(&dec, 1, 3);//=>val.c

        switch(dec){
            case 1:
                leer_menu();
                break;
            case 2:
                modificar_menu();
                break;
            default:
                fclose(parchivo);
                mensaje_log("===================CERRANDO SESION======================");
                printf("\n\tGracias por utilizar nuestro sistema!\n");
                exit(0);
                break;
        }
    }while(dec!=3);
}

int main(void){
    mensaje_log("===================NUEVA SESION======================");
    parchivo=fopen("archivos/banco.txt", "rt");
    if(!parchivo){
        parchivo=fopen("archivos/banco.txt", "wt");
    }else{
        leer_archivo();//=>mod.c
        ordenar(3);//=>man.c
    }
    fclose(parchivo);
    menu();
    return 0;
}