#include <stdio.h>
#include <stdlib.h>

// Prototipos
int dades();
long long int fibonacci_recursivo(int n);
void mostrar_fibonacci(int n);

int main()
{
    int num;
    num = dades();
    mostrar_fibonacci(num);
    return 0;
}

int dades()
{
    int num;
    printf("Introduce cuantos numeros de Fibonacci quieres mostrar: ");
    scanf("%d", &num);
    return num;
}

long long int fibonacci_recursivo(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

void mostrar_fibonacci(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%lld ", fibonacci_recursivo(i));
    }
    printf("\n");
}
