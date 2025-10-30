#ifndef MENU_H
#define MENU_H
#include "linea.h" 

void mostrarMenuPrincipal() {
    printf("\n=== GESTOR DE LINEAS DE COLECTIVOS ===\n");
    printf("1. Consultar una l�nea\n");
    printf("2. Mostrar todas las l�neas\n");
    printf("3. Agregar una nueva l�nea\n");
    printf("4. Eliminar una l�nea\n");
    printf("5. Guardar y salir\n");
    printf("Seleccione una opci�n: ");
}
void ejecutarMenu() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        scanf("%d", &opcion);
        getchar(); // Limpia el buffer

        switch (opcion) {
            case 1:
                consultarLinea();
                break;
            case 2:
                mostrarTodasLasLineas();
                break;
            case 3:
                agregarLinea();
                break;
            case 4:
                eliminarLinea();
                break;
            case 5:
                printf("Guardando datos y saliendo...\n");
                break;
            default:
                printf("Opci�n inv�lida. Intente nuevamente.\n");
        }
    } while (opcion != 5);
}


#endif

