#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_ROJO "\x1b[31m"

int menu();
int seleccionar_simbolos(char *apt_simbolo_1, char *apt_simbolo_2);
int imprimir_tablero(char tablero[3][3]);
int registrar_tirada(char tablero[3][3], bool *apt_turno, int jugadores, char simbolo_1, char simbolo_2);
int comprobar_tablero(char tablero[3][3], bool turno);

int inicializar_juego(char tablero[3][3], int jugadores);



int main(int argc, char const *argv[])
{
    char matriz[3][3] = 
        {   
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
    menu() ? inicializar_juego(matriz, 2) : inicializar_juego(matriz, 1);

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

int registrar_tirada(char tablero[3][3], bool *apt_turno, int jugadores, char simbolo_1, char simbolo_2) 
{
    int columna, fila, error = 0;
    if(jugadores == 1) 
    {
        if(*apt_turno == true) 
        {
            
            do
            {
                if(error)
                {
                    system("@cls||clear");
                    printf(COLOR_ROJO"Posicion invalida\n"COLOR_RESET);
                    imprimir_tablero(tablero);
                }
                printf("Turno del jugador numero %d\n\n", *apt_turno ? 1 : 2);
                printf("¿Donde desea tirar?\nNumero de fila:\n");
                scanf("%d", &fila);
                printf("Numero de columna:\n");
                scanf("%d", &columna);
                error = 1;
                printf("\n%d %d\n", fila, columna);
            } while (tablero[fila][columna] != ' ' || fila < 0 || columna < 0 || fila > 2 || columna > 2);
            tablero[fila][columna] = simbolo_1;
            *apt_turno = false;
        }else 
        {
            int r_columna, r_fila;
            do
            {
                srand (time(NULL)); 
                r_columna = rand() % 3;
                r_fila = rand() % 3;
            } while (tablero[r_fila][r_columna] != ' ' || r_fila < 0 || r_columna < 0 || r_fila > 2 || r_columna > 2);
            tablero[r_fila][r_columna] = simbolo_2;
            *apt_turno = true;
        }
    }else
    {
        do
        {
            if(error)
            {
                system("@cls||clear");
                printf(COLOR_ROJO"Posicion invalida\n"COLOR_RESET);
                imprimir_tablero(tablero);
            }
            printf("Turno del jugador numero %d\n\n", *apt_turno ? 1 : 2);
            printf("¿Donde desea tirar?\nNumero de columna:\n");
            scanf("%d", &columna);
            printf("Numero de fila:\n");
            scanf("%d", &fila);
            error = 1;
        } while (tablero[fila][columna] != ' ');
        tablero[fila][columna] = *apt_turno ? simbolo_1 : simbolo_2;
        *apt_turno = !*apt_turno;
    }
    return 0;
}

int comprobar_tablero(char tablero[3][3], bool turno)
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
        system("@cls||clear");
        printf(COLOR_CYAN"Juego terminado\nGanador: Jugador %d\n"COLOR_RESET, turno ? 2 : 1);  
        return 1; 
    }else 
    {
        return 0;
    }
}

int seleccionar_simbolos(char *apt_simbolo_1, char *apt_simbolo_2)
{
    do
    {
        printf("Ingresa el simbolo del jugador 1\n");
        scanf(" %c", &(*apt_simbolo_1));
        printf("Ingresa el simbolo del jugador 2\n");
        scanf(" %c", &(*apt_simbolo_2));
    } while (apt_simbolo_1 == apt_simbolo_2);
        
    return 0;
}

int inicializar_juego(char tablero[3][3], int jugadores) 
{
    bool turno_jugador = true;
    char simbolo_1, simbolo_2;
    seleccionar_simbolos(&simbolo_1, &simbolo_2);
    do
    {
        system("@cls||clear");
        imprimir_tablero(tablero);
        printf("\n");
        registrar_tirada(tablero, &turno_jugador, jugadores, simbolo_1, simbolo_2);
    } while (!comprobar_tablero(tablero, turno_jugador));
    imprimir_tablero(tablero);
    return 0;
}
