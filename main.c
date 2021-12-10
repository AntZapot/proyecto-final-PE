#include <stdio.h>

int imprimir_menu(void);

int main(int argc, char const *argv[])
{
    if(imprimir_menu()) {
        printf("Ha seleccionado 2 jugadores\n");
    }
        printf("Ha seleccionado 1 jugadores\n");


    printf("|   |   |   |\n");
    printf("-------------\n");
    printf("|   |   |   |\n");
    printf("-------------\n");
    printf("|   |   |   |\n");

    return 0;
}

int imprimir_menu(void) {
    int num;
    printf("Numero de jugadores (1) (2)\n");
    do
    {
        scanf("%d", &num);
    } while (num != 1 && num != 2);
    return num == 1 ? 0 : 1;
}
