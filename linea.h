#ifndef LINEA_H
#define LINEA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Ruta del archivo de datos (junto al ejecutable)
#define LINEAS_FILE "lineas.txt"

// Estructura base de una línea de colectivo
typedef struct {
    int id;
    char nombre[64];
    char recorrido[128];
} Linea;

// Utilidades
int cargarLineaDesdeCadena(const char *lineaTxt, Linea *out);
void imprimirLinea(const Linea *l);

void consultarLinea();
void mostrarTodasLasLineas();
void agregarLinea();
void eliminarLinea();

static void trimNuevaLinea(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        // Manejar CRLF
        len = strlen(s);
        if (len > 0 && (s[len - 1] == '\r' || s[len - 1] == '\n')) {
            s[len - 1] = '\0';
        }
    }
}

static int equalsIgnoreCase(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        char ca = (char)tolower((unsigned char)*a);
        char cb = (char)tolower((unsigned char)*b);
        if (ca != cb) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

int cargarLineaDesdeCadena(const char *lineaTxt, Linea *out) {
    if (!lineaTxt || !out) return 0;
    // Formato: id;nombre;recorrido
    char buffer[256];
    strncpy(buffer, lineaTxt, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    trimNuevaLinea(buffer);

    char *p1 = strtok(buffer, ";");
    char *p2 = strtok(NULL, ";");
    char *p3 = strtok(NULL, ";");
    if (!p1 || !p2 || !p3) return 0;

    out->id = atoi(p1);
    strncpy(out->nombre, p2, sizeof(out->nombre) - 1);
    out->nombre[sizeof(out->nombre) - 1] = '\0';
    strncpy(out->recorrido, p3, sizeof(out->recorrido) - 1);
    out->recorrido[sizeof(out->recorrido) - 1] = '\0';
    return 1;
}

void imprimirLinea(const Linea *l) {
    if (!l) return;
    printf("ID: %d | Nombre: %s | Recorrido: %s\n", l->id, l->nombre, l->recorrido);
}

static int existeIdEnArchivo(int idBuscado) {
    FILE *f = fopen(LINEAS_FILE, "r");
    if (!f) return 0; // Si no existe archivo, no existe el id
    char linea[256];
    Linea l;
    while (fgets(linea, sizeof(linea), f)) {
        if (cargarLineaDesdeCadena(linea, &l)) {
            if (l.id == idBuscado) {
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}

void mostrarTodasLasLineas() {
    FILE *f = fopen(LINEAS_FILE, "r");
    if (!f) {
        printf("No hay datos. El archivo %s no existe.\n", LINEAS_FILE);
        return;
    }
    char linea[256];
    Linea l;
    int count = 0;
    printf("\n--- Todas las lineas ---\n");
    while (fgets(linea, sizeof(linea), f)) {
        if (cargarLineaDesdeCadena(linea, &l)) {
            imprimirLinea(&l);
            count++;
        }
    }
    if (count == 0) printf("(sin registros)\n");
    fclose(f);
}

void consultarLinea() {
    int modo = 0;
    printf("Buscar por: 1) ID  2) Nombre -> ");
    if (scanf("%d", &modo) != 1) { getchar(); printf("Entrada invalida.\n"); return; }
    getchar(); // limpiar fin de linea

    FILE *f = fopen(LINEAS_FILE, "r");
    if (!f) {
        printf("No hay datos. El archivo %s no existe.\n", LINEAS_FILE);
        return;
    }

    char linea[256];
    Linea l;
    int encontrado = 0;

    if (modo == 1) {
        int id;
        printf("Ingrese ID: ");
        if (scanf("%d", &id) != 1) { getchar(); printf("Entrada invalida.\n"); fclose(f); return; }
        getchar();
        while (fgets(linea, sizeof(linea), f)) {
            if (cargarLineaDesdeCadena(linea, &l) && l.id == id) { imprimirLinea(&l); encontrado = 1; break; }
        }
    } else if (modo == 2) {
        char nombre[64];
        printf("Ingrese nombre: ");
        if (!fgets(nombre, sizeof(nombre), stdin)) { printf("Entrada invalida.\n"); fclose(f); return; }
        trimNuevaLinea(nombre);
        while (fgets(linea, sizeof(linea), f)) {
            if (cargarLineaDesdeCadena(linea, &l) && equalsIgnoreCase(l.nombre, nombre)) { imprimirLinea(&l); encontrado = 1; break; }
        }
    } else {
        printf("Opcion invalida.\n");
    }

    if (!encontrado) printf("No se encontro la linea solicitada.\n");
    fclose(f);
}

void agregarLinea() {
    Linea nueva;
    printf("ID: ");
    if (scanf("%d", &nueva.id) != 1) { getchar(); printf("Entrada invalida.\n"); return; }
    getchar();
    printf("Nombre: ");
    if (!fgets(nueva.nombre, sizeof(nueva.nombre), stdin)) { printf("Entrada invalida.\n"); return; }
    trimNuevaLinea(nueva.nombre);
    printf("Recorrido: ");
    if (!fgets(nueva.recorrido, sizeof(nueva.recorrido), stdin)) { printf("Entrada invalida.\n"); return; }
    trimNuevaLinea(nueva.recorrido);

    if (existeIdEnArchivo(nueva.id)) {
        printf("Ya existe una linea con ID %d.\n", nueva.id);
        return;
    }

    FILE *f = fopen(LINEAS_FILE, "a");
    if (!f) {
        // Intentar crear directorio no portable; asumimos que existe. Informar error si no.
        printf("No se pudo abrir %s para escritura. Asegurese de que el directorio exista.\n", LINEAS_FILE);
        return;
    }
    fprintf(f, "%d;%s;%s\n", nueva.id, nueva.nombre, nueva.recorrido);
    fclose(f);
    printf("Linea agregada correctamente.\n");
}

void eliminarLinea() {
    int id;
    printf("ID a eliminar: ");
    if (scanf("%d", &id) != 1) { getchar(); printf("Entrada invalida.\n"); return; }
    getchar();

    FILE *fin = fopen(LINEAS_FILE, "r");
    if (!fin) { printf("No hay datos. El archivo %s no existe.\n", LINEAS_FILE); return; }
    FILE *fout = fopen("lineas.tmp", "w");
    if (!fout) { printf("No se pudo crear archivo temporal.\n"); fclose(fin); return; }

    char linea[256];
    Linea l;
    int borrados = 0;
    while (fgets(linea, sizeof(linea), fin)) {
        if (cargarLineaDesdeCadena(linea, &l)) {
            if (l.id == id) { borrados++; continue; }
            fprintf(fout, "%d;%s;%s\n", l.id, l.nombre, l.recorrido);
        }
    }
    fclose(fin);
    fclose(fout);

    if (borrados == 0) {
        remove("lineas.tmp");
        printf("No se encontro una linea con ID %d.\n", id);
        return;
    }

    if (remove(LINEAS_FILE) != 0 || rename("lineas.tmp", LINEAS_FILE) != 0) {
        printf("Error al actualizar el archivo de datos.\n");
        return;
    }
    printf("Linea eliminada correctamente.\n");
}

#endif

