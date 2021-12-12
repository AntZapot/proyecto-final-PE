#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int menu();
int imprimir_tablero(char tablero[3][3]);
int registrar_tirada(char tablero[3][3], bool *apt_turno, int modo);
int comprobar_tablero(char tablero[3][3]);

int modo_un_jugador(char tablero[3][3]);
int modo_dos_jugadores();



int main(int argc, char const *argv[])
{
    char matriz[3][3] = 
        {   
            {' ', ' ', ' '},
            {' ', ' ', ' '},
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

int imprimir_tablero(char tablero[3][3]) 
{
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

int registrar_tirada(char tablero[3][3], bool *apt_turno, int modo) 
{
    int columna, fila, error = 0;
    if(modo == 1) 
    {
        if(*apt_turno == true) 
        {
            
            do
            {
                if(error)
                {
                    printf("Posicion invalida,\n");
                    imprimir_tablero(tablero);
                }
                printf("¿Donde desea tirar?\nNumero de columna:\n");
                scanf("%d", &columna);
                printf("Numero de fila:\n");
                scanf("%d", &fila);
                error = 1;
            } while (tablero[fila][columna] != ' ');
            tablero[fila][columna] = 'x';
            *apt_turno = false;
        }else 
        {
            int r_columna, r_fila;
            do
            {
                srand (time(NULL)); 
                r_columna = rand() % 3;
                r_fila = rand() % 3;
            } while (tablero[r_fila][r_columna] != ' ');
            tablero[r_fila][r_columna] = 'o';
            *apt_turno = true;
        }
    }else
    {
        do
        {
            if(error)
            {
                printf("Posicion invalida,\n");
                imprimir_tablero(tablero);
            }
            printf("¿Donde desea tirar?\nNumero de columna:\n");
            scanf("%d", &columna);
            printf("Numero de fila:\n");
            scanf("%d", &fila);
            error = 1;
        } while (tablero[fila][columna] != ' ');

        tablero[fila][columna] = *apt_turno ? 'o' : 'x';
        *apt_turno = !*apt_turno;
    }
    return 0;
}

int comprobar_tablero(char tablero[3][3])
{
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
            if(i == 0 && j == 0 && tablero[i][j] == tablero[i+1][j+1] && tablero[i][j] == tablero[i+2][j+2] && tablero[i][j] != ' ')
            {
                terminado = true;
            }
            if(i == 0 && j == 2 && tablero[i][j] == tablero[i+1][j-1] && tablero[i][j] == tablero[i+2][j-2] && tablero[i][j] != ' ')
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

int modo_un_jugador(char tablero[3][3]) 
{
    bool turno_jugador = true;
    printf("Modo un jugador seleccionado\n");
    do
    {
        imprimir_tablero(tablero);
        printf("\n");
        registrar_tirada(tablero, &turno_jugador, 1);
    } while (!comprobar_tablero(tablero));
    imprimir_tablero(tablero);
}

int modo_dos_jugadores(char tablero[3][3]) 
{
    bool turno_jugador = true;
    printf("Modo de dos jugadores seleccionado\n");
    do
    {
        imprimir_tablero(tablero);
        printf("\n");
        registrar_tirada(tablero, &turno_jugador, 2);
    } while (!comprobar_tablero(tablero));
    imprimir_tablero(tablero);
    return 0;
}
