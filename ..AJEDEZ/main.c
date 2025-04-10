//caballo
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
  *                                                                          *
  *                                                                          *
  *                  CIRCUITO DEL CABALLO (FUERZA BRUTA)                     *
  *                                                                          *
  *  Este programa intenta el recorrido del caballo en un tablero de ajedrez *
  *  mediante la fuerza bruta.                                               *
  *                                                                          *
  *                                                                          *
  *                                                                          *
  *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*                                                                         *
*                                ALGORITMO:                               *
*                                __________                               *
*                                                                         *
*  La idea de este algorimo es bastante simple:                           *
*                                                                         *
* PASO 1: El tablero de ajedrez (arreglo de NxN) se llena con 0 en todas  *
* las entradas exepto en la esquina superior izuierda, que se coloca un 1 *
* De ahi es de donde parte el caballo.                                    *
*                                                                         *
* PASO 2: Se lanza un par de "dados" de ocho caras. El primer dado decide *
* el renglon, el siguiente                                                *
* decide la columna donde se colocara el caballo a continuacion.          *
*                                                                         *
* PASO 3: Es necesario verificar que el caballo no haya pasado antes por  *
* ahi, o que la casilla seleccionada tenga un 0 Si no es asi se repite el *
* Paso2. Si efectivamente es un 0, entonces se verifica que la casilla    *
* elegida al azar sea "legal" o este en forma de L Para esto se verifican *
* las distancias en X y en Y. Si el valor absoluto de la diferencia entre *
* la casilla elegida por el dado1 y la casilla x actual es igual a 2 o  1 *
* se procede a checar el valor absoluto de la distancia entre dado2 y Y. 1*
* para el primer caso y 2 para el segundo, indican que la casilla es      *
* valida. Se procede a poner el numero  2 ( o 3 o 4 o el que sea)  en la  *
* casilla, lo cual indica que  esa es la siguiente parada del caballo. Se *
* incrementa la variable contador y se procede de esa manera.             *
*                                                                         *
*                                                                         *
* Eso es todo. Esa es la idea central. Lo demas consiste en decirle al    *
* programa cuando ya no es                                                *
* posible encontrar mas casillas, y por lo tanto se ha llegado a un       *
* rincon sin salida. Para eso se introduce una variable que cuenta el     *
* numero de veces que se ha lanzado los dos dados sin cambiar de casilla. *
* Si se cumplen estos el programa entiende que no hay salida y deja de    *
* intentar buscarla. Esto significa que 15 de cada 1000 veces dejara de   *
* intentar cuando en realidad hay una casilla a la cual mover. Se puede   *
* cambiar y poner un limite mas grande, pero como he puesto un ciclo mas  *
* grande afuera que permite al usuario pedir una cuota minima de          *
* recorrido, hacerlo significa  mas tiempo.                               *
*                                                                         *
*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int x = 1; // El caballo inica en la casilla superior
int y = 1; // izquierda
const int TAMANO = 5; // Cambiar esta variable para resolver el problema del
// recorrido del caballo en un tablero de N * N
int contador = 1; // Esta variable lleva la cuenta de las casillas
// recorridas
int ciclos = 0; // Esta variable cuenta los ciclos que se intentan
// antes de terminar que ya no haya lugares a los cuales
// ir
int intentos_fallidos = 0; // Esta variable cuenta cuantos ciclos se
// intentan antes de obtener el que pidio el usuario.

// Prototipo de funcion Imprime
void Imprime( int a[TAMANO + 1][TAMANO + 1]);
int main()
{
    // Abre main
    srand(time(NULL));
    int Arreglo[TAMANO + 1][TAMANO + 1];

    Arreglo[y][x] = 1;
    int dado1;
    int dado2;
    int casillas_requeridas = 0;

    do
    {
        // Abre while
        printf("\nCuantas casillas quiere que recorra por lo menos?");
        printf("\n(Un numero positivo menor o igual que %d): ", TAMANO*TAMANO );
        scanf("%d", &casillas_requeridas);
    }
    while ((TAMANO*TAMANO < casillas_requeridas) || (0 > casillas_requeridas));

    while ( contador < casillas_requeridas )
    {
        // Abre while
        intentos_fallidos++; // Se incrementa cada que inica un intento de
        // completar las casillas pedidas por el usuario
        contador = 1; // Dado que ya se ha colocado al caballo en (y,X), se
        // inicia el contador en 1
        int ciclos = 0; // Se inicia con 0 ciclos o lanzamientos de dados infructuosos
// Cada vez que se aborta un intento han de limpiarse las casillas, con
// el siguiente par de ciclos se establecen a 0 nuevamente.
        int s;
        int t;
        for ( s = 0; s <= TAMANO; s++ )
        {
            // Abre for
            for ( t = 0; t <= TAMANO; t++ )
                Arreglo[s][t] = 0;
        }        // Cierra for

// Se ha de colocar el caballo en la esquina superior izquierda cada vez
// Desde luego se puede poner en cualquier parte
        x = 1;
        y = 1;
        Arreglo[y][x] = 1;

// Mientras no se encuentre un lugar para el caballo
        while ( 1000 != ciclos )
// Por que 100? En el caso extremo en el que solo falte una casilla por
// llenar (la 64 para un tablero de 8*8) la mayoria de las casillas aleatorias
// estaran ya ocupadas, pero a la larga, una de cada 64 (TAMANO*TAMANO) sera
// la correcta. Para evitar que el intento se aborte debido a una fluctuacion
// estadistica (por ejemplo que de 500 casillas aleatorias ninguna sea la
// casilla en blanco) se pone un "colchon" de 1000 casillas. Esto se puede
// cambiar, desde luego, teniendo en cuenta cual es la probabilidad de que se
// obtenga una casilla cualquiera.

        {
            // Abre while
            ciclos++;
            dado1 = 1 +  rand() % TAMANO;
            dado2 = 1 +  rand() % TAMANO;

            if ( 2 == fabs(x - dado1))
            {
                // Abre if
                if ( 1 == fabs(y - dado2))
                    if ( 0 == Arreglo[dado1][dado2] )
                    {
                        // Abre if
                        Arreglo[dado1][dado2] = ++contador;
                        x = dado1;
                        y = dado2;
                        ciclos = 0;
                    }     // Cierra if
            }       // Cierra if

            if ( fabs(fabs(x) - fabs(dado1)) == 1)
            {
                // abre if
                if ( fabs(fabs(y) - fabs(dado2)) == 2  )
                    if ( 0 == Arreglo[dado1][dado2] )
                    {
                        // Abre if
                        Arreglo[dado1][dado2] = ++contador;
                        x = dado1;
                        y = dado2;
                        ciclos = 0;
                    }  // Cierra if
            }  // Cierra if

        }       // Cierra while
    }    // Cierra while

    printf("\nLISTO!\n");
    printf("\nSe recorrieron %d casillas\n", contador);
    printf("\nSe intentaron %d circuitos antes de obtener", intentos_fallidos);
    printf(" el requerido.\n");

    Imprime( Arreglo);


}    // Cierra main


/*La funcion siguiente despliega el tablero de ajedrez */

//////////////////////////////////////////
// Imprime
///////////////////////////////////////////

void Imprime( int Matriz[TAMANO + 1][TAMANO + 1])

{
    // Abre la funcion Imprimir
    int i;
    int j;
    printf("\n\nEste es el tablero:\n\n ");
    for ( i = 1; i <= TAMANO; i++ )
    {
        // Abre for
        for ( j = 1; j <= TAMANO; j++)
        {
            // abre for anidado
            printf(" %d\t",  Matriz[i][j]);
        } // Cierra for anidado
        printf("\n\n\n");
    } // Cierra for

    printf("\n\n\n");
} // Cierra la funcion
