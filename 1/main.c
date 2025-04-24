#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 32         // Valor ASCII mínimo imprimible
#define MAX 126        // Valor ASCII máximo imprimible
#define RANGO (MAX - MIN + 1)

// Función para cifrar una frase
void cifrar(char *frase, int key, char *resultado) {
    for (int i = 0; i < strlen(frase); i++) {
        char c = frase[i];
        if (c >= MIN && c <= MAX) {
            resultado[i] = (char)(((c - MIN + key) % RANGO) + MIN);
        } else {
            resultado[i] = c; // Mantiene caracteres fuera del rango
        }
    }
    resultado[strlen(frase)] = '\0';
}

// Función para descifrar una frase
void descifrar(char *frase, int key, char *resultado) {
    for (int i = 0; i < strlen(frase); i++) {
        char c = frase[i];
        if (c >= MIN && c <= MAX) {
            resultado[i] = (char)(((c - MIN - key + RANGO) % RANGO) + MIN);
        } else {
            resultado[i] = c;
        }
    }
    resultado[strlen(frase)] = '\0';
}

int main() {
    char *frase = NULL;
    char *resultado = NULL;
    int key, opcion;
    size_t tam = 100;

    frase = (char *)malloc(tam * sizeof(char));
    if (!frase) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    while (1) {
        system("cls || clear");

        printf("Seleccione una opcion:\n");
        printf("1. Cifrar\n");
        printf("2. Descifrar\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 3) break;

        printf("Ingresa la frase: ");
        fgets(frase, tam, stdin);
        frase[strcspn(frase, "\n")] = '\0';
        do {
            printf("Ingresa la clave (1-10): ");
            scanf("%d", &key);
            getchar();
        } while (key < 1 || key > 10);

        resultado = (char *)malloc(strlen(frase) + 1);
        if (!resultado) {
            printf("Error al asignar memoria.\n");
            free(frase);
            return 1;
        }

        if (opcion == 1) {
            cifrar(frase, key, resultado);
            printf("Frase cifrada: %s\n", resultado);
        } else if (opcion == 2) {
            descifrar(frase, key, resultado);
            printf("Frase descifrada: %s\n", resultado);
        }

        free(resultado);
        resultado = NULL;

        printf("\nPresiona Enter para continuar...");
        getchar();
    }

    free(frase);
    return 0;
}


