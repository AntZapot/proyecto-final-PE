#include <stdio.h>
#include <stdbool.h>

int menu();
int imprimir_tablero(char tablero[3][3]);
int registrar_tirada(char tablero[3][3]);
int comprobar_tablero(char tablero[3][3]);

int modo_un_jugador(char tablero[3][3]);
int modo_dos_jugadores();



int main(int argc, char const *argv[])
{
    char matriz[3][3] = 
        {   
            {'x', ' ', ' '},
            {' ', 'x', ' '},
            {' ', ' ', ' '}
        };

    menu() ? modo_dos_jugadores(matriz) : modo_un_jugador(matriz);

    return 0;
}

int menu(void) {
    int num;
    printf("Numero de jugadores (1) (2)\n");
    do
    {
        scanf("%d", &num);
    } while (num != 1 && num != 2);
    return num == 1 ? 0 : 1;
}

int imprimir_tablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j == 2) 
            {
                printf("| %c |", tablero[i][j]);
            }else 
            {
                printf("| %c ", tablero[i][j]);
            }
        }
        if(i != 2) 
        {
            printf("\n-------------\n");
        }else 
        {
            printf("\n");
        }
    }
    return 0;
}

int registrar_tirada(char tablero[3][3]) {
    int columna, fila;
    printf("¿Donde desea tirar?\nNumero de columna:\n");
    scanf("%d", &columna);
    printf("Numero de fila:\n");
    scanf("%d", &fila);

    if(tablero[columna][fila] == ' ') 
    {
        tablero[columna][fila] = 'x';
    }else 
    {
        printf("Posicion invalida\n");
    }
    return 0;
}

int comprobar_tablero(char tablero[3][3]){
    bool terminado = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(tablero[i][j] == tablero[i][j+1] && tablero[i][j] == tablero[i][j+2] && tablero[i][j] != ' ')
            {
                terminado = true;
            }
            if(tablero[i][j] == tablero[i+1][j] && tablero[i][j] == tablero[i+2][j] && tablero[i][j] != ' ')
            {
                terminado = true;
            }
            if(tablero[i][j] == tablero[i+1][j+1] && tablero[i][j] == tablero[i+2][j+2] && tablero[i][j] != ' ')
            {
                terminado = true;
            }
        }
    }
    if(terminado) 
    {
        printf("Juego terminado\n");  
        return 1; 
    }else 
    {
        return 0;
    }
}

int modo_un_jugador(char tablero[3][3]) {
    printf("Modo un jugador seleccionado\n");
    do
    {
        imprimir_tablero(tablero);
        registrar_tirada(tablero);
    } while (!comprobar_tablero(tablero));
    imprimir_tablero(tablero);
}

int modo_dos_jugadores() {
    printf("Modo de dos jugadores seleccionado\n");
}
