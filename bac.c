#include "linker.h"

void menu(void){
    int dec;
    do{
        printf("\n\tMENU");
        printf("\n\t[1]...Ingresar Una Nueva Cuenta");
        printf("\n\t[2]...Borrar Una Cuenta");
        printf("\n\t[3]...Mostrar Cuentas Activas");
        printf("\n\t[4]...Buscar Una Cuenta");
        printf("\n\t[5]...Hacer transferencia");
        printf("\n\t[6]...Salir\n\t");
        validar_menu(&dec, 1, 6);

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
        ordenar(3);
        actualizar_archivo();
    }
    fclose(parchivo);
    menu();
    return 0;
}