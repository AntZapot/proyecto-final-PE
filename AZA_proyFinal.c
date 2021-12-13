#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Colores
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_ROJO "\x1b[31m"

//Funciones
int menu(char tablero[3][3]);
int crear_archivo(char tablero[3][3]);
int seleccionar_simbolos();
int imprimir_tablero(char tablero[3][3]);
int comprobar_tablero(char tablero[3][3], bool turno, int turnos);
int registrar_tirada(char tablero[3][3], bool *apt_turno, int jugadores);
int obtener_tips(char tablero[3][3], char simbolo_actual, char simbolo_contrario);
//Actual indica si el simbolo evaluado es un simbolo aliado o contrario
int comprobar_tips(char tablero[3][3], int i, int j, int actual);
int mensaje_tip(int i, int j, int tipo_tip);

int reiniciar_juego();
int inicializar_juego(char tablero[3][3], int jugadores);

//estructura para almacenar los simbolos a usar
struct simbolos
{
    char simbolo_1;
    char simbolo_2;
}simbolos;


int main()
{
    char matriz[3][3] = 
        {   
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };

    //menu donde se elegira el modo de juego y los jugadores
    switch (menu(matriz))   
    {
    case -1:
        return 0;
        break;
    case 0:
        inicializar_juego(matriz, 1); 
        break;
    case 1:
        inicializar_juego(matriz, 2); 
        break;
    }
    return 0;
}

int menu(char tablero[3][3]) {
    char eleccion;
    int num;
    do
    {
        printf("¿Desea jugarlo en computadora? [s/n]\n");
        scanf(" %c", &eleccion);
    } while (!eleccion == 's' || !eleccion == 'n');

    if(eleccion == 'n')
    {
        crear_archivo(tablero);
        return -1;
    }
    do
    {
        printf("Numero de jugadores (1) (2)\n");
        scanf("%d", &num);
    } while (num != 1 && num != 2);
    //Si retorna 0 sera modo 1 jugador, sino sera modo 2 jugadores
    return num == 1 ? 0 : 1;
}

int crear_archivo(char tablero[3][3])
{
    printf("¡¡Archivo txt generado con exito!!\n");
    freopen("juego_gato.txt", "w", stdout);
    printf("|   |   |   |\n");
    printf("-------------\n");
    printf("|   |   |   |\n");
    printf("-------------\n");
    printf("|   |   |   |\n");
    fclose(stdout);
    return 0;
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

int registrar_tirada(char tablero[3][3], bool *apt_turno, int jugadores) 
{
    int columna, fila, error = 0;
    char simbolo_1, simbolo_2;
    //filtrar por  numero de jugadores
    if(jugadores == 1) 
    {
        if(*apt_turno == true) 
        {
            
            do
            {
                //manejo de errores 
                if(error)
                {
                    system("@cls||clear");
                    if (columna == 4 && fila == 4)
                    {
                        obtener_tips(tablero, simbolos.simbolo_1, simbolos.simbolo_2);
                    }else
                    {
                        printf(COLOR_ROJO"Posicion invalida\n"COLOR_RESET);
                    }
                    imprimir_tablero(tablero);
                }
                //obtener fila y columna y comprobar que sean posiciones validas en el tablero
                printf("Para obtener un consejo inserte 4 4\n");
                printf("Turno del jugador numero %d\n\n", *apt_turno ? 1 : 2);
                printf("¿Donde desea tirar?\nNumero de fila:\n");
                scanf("%d", &fila);
                printf("Numero de columna:\n");
                scanf("%d", &columna);
                error = 1;
                printf("\n%d %d\n", fila, columna);
            } while (tablero[fila][columna] != ' ' || fila < 0 || columna < 0 || fila > 2 || columna > 2);
            tablero[fila][columna] = simbolos.simbolo_1;
            *apt_turno = false;
        }else 
        {
            int r_columna, r_fila;
            do
            {
                //Generacion de numeros aleatorios entre 0 y 2 para el juego en solitario
                srand (time(NULL)); 
                r_columna = rand() % 3;
                r_fila = rand() % 3;
            } while (tablero[r_fila][r_columna] != ' ' || r_fila < 0 || r_columna < 0 || r_fila > 2 || r_columna > 2);
            tablero[r_fila][r_columna] = simbolos.simbolo_2;
            *apt_turno = true;
        }
    }else
    {
        do
        {
            //manejo de errores
            if(error)
            {
                system("@cls||clear");
                if(columna == 4 && fila == 4)
                {
                    //Determinar el simbolo del jugador actual
                    if(*apt_turno)
                    {
                        simbolo_1 = simbolos.simbolo_1;
                        simbolo_2 = simbolos.simbolo_2;
                    }else
                    {
                        simbolo_1 = simbolos.simbolo_2;
                        simbolo_2 = simbolos.simbolo_1;
                    }
                    obtener_tips(tablero, simbolo_1, simbolo_2);
                }else
                {
                    printf(COLOR_ROJO"Posicion invalida\n"COLOR_RESET);
                }
                imprimir_tablero(tablero);
            }
            //obtener fila y columnas
            printf("Turno del jugador numero %d\n\n", *apt_turno ? 1 : 2);
            printf("¿Donde desea tirar?\nNumero de fila:\n");
            scanf("%d", &fila);
            printf("Numero de columna:\n");
            scanf("%d", &columna);
            error = 1;
        } while (tablero[fila][columna] != ' ');
        tablero[fila][columna] = *apt_turno ? simbolos.simbolo_1 : simbolos.simbolo_2;
        //invertir el estado del turno para que cambie el jugador a tirar
        *apt_turno = !*apt_turno;
    }
    return 0;
}

int comprobar_tablero(char tablero[3][3], bool turno, int turnos)
{
    //comprobacion de el tablero para saber si hay un ganador
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
    if(turnos == 9)
    {
        system("@cls||clear");
        printf(COLOR_CYAN"Juego terminado: EMPATE\n"COLOR_RESET);  
        return 1; 
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

int seleccionar_simbolos()
{
    //obtener los simbolos y comprobar si son validos
    do
    {
        printf("Ingresa el simbolo del jugador 1\n");
        scanf(" %c", &simbolos.simbolo_1);
        printf("Ingresa el simbolo del jugador 2\n");
        scanf(" %c", &simbolos.simbolo_2);
    } while (simbolos.simbolo_1 == simbolos.simbolo_2);

    return 0;
}

int reiniciar_juego()
{
    //Comprobar si se desea reiniciar el juego
    char eleccion;
    do
    {
        printf("¿Desea volver a jugar?[s/n]\n");
        scanf(" %c", &eleccion);
    } while (!eleccion == 's' || !eleccion == 'n');
    return eleccion == 's' ? 1 : 0;
}

int mensaje_tip(int i, int j, int tipo_tip)
{
    if(tipo_tip)
    {
        printf(COLOR_CYAN"¡TIP!\n"COLOR_RESET);
        printf("Posibilidad de ganar si se tira en %d %d\n", i, j);
    }else 
    {
        printf(COLOR_ROJO"!ADVERTENCIA!\n"COLOR_RESET);
        printf("Posibilidad de perder en %d %d\n", i, j);
    }
}

int comprobar_tips(char tablero[3][3], int i, int j, int actual)
{
    if(tablero[i][j] == tablero[i][j+1] && tablero[i][j+2] == ' ')
    {
        mensaje_tip(i, j+2, actual);
        return 1;
    }
    if(tablero[i][j] == tablero[i+1][j] && tablero[i+2][j] == ' ')
    {
        mensaje_tip(i+2, j, actual);
        return 1;
    }
    if(i == 0 && j == 0 && tablero[i][j] == tablero[i+1][j+1] && tablero[i+2][j+2] == ' ')
    {
        mensaje_tip(i+2, j+2, actual);
        return 1;
    }
    if(i == 0 && j == 2 && tablero[i][j] == tablero[i+1][j-1] && tablero[i+2][j-2] == ' ')
    {
        mensaje_tip(i+2, j-2, actual);
        return 1;
    }

    if(i == 2 && tablero[i][j] == tablero[i-1][j] && tablero[i-2][j] == ' ')
    {
        mensaje_tip(i-2, j, actual);
        return 1;
    }
    if(j == 2 && tablero[i][j] == tablero[i][j-1] && tablero[i][j-2] == ' ')
    {
        mensaje_tip(i, j-2, actual);
        return 1;
    }
    if(i == 2 && j == 2 && tablero[i][j] == tablero[i-1][j-1] && tablero[i-2][j-2] == ' ')
    {
        mensaje_tip(i-2, j-2, actual);
        return 1;
    }
    if(i == 2 && j == 0 && tablero[i][j] == tablero[i-1][j+1] && tablero[i-2][j+2] == ' ')
    {
        mensaje_tip(i-2, j+2, actual);
        return 1;
    }


    if(tablero[i][j] == tablero[i][j+2] && tablero[i][j+1] == ' ')
    {
        mensaje_tip(i, j+1, actual);
        return 1;
    }
    if(tablero[i][j] == tablero[i+2][j] && tablero[i+1][j] == ' ')
    {
        mensaje_tip(i+1, j, actual);
        return 1;
    }

    if(i == 2 && j == 2 && tablero[i][j] == tablero[i-2][j-2] && tablero[i-1][j-1] == ' ')
    {
        mensaje_tip(i-1, j-1, actual);
        return 1;
    }
    if(i == 2 && j == 0 && tablero[i][j] == tablero[i-2][j+2] && tablero[i-1][j+1] == ' ')
    {
        mensaje_tip(i-1, j+1, actual);
        return 1;
    }

    return 0;
}

int obtener_tips(char tablero[3][3], char simbolo_actual, char simbolo_contrario) 
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //verificar si hay casillas disponibles para ganar de manera inmediata
            if(tablero[i][j] == simbolo_actual)
            {
                if(comprobar_tips(tablero, i, j, 1))
                {
                    return 0;
                }
            }
            if (tablero[i][j] == simbolo_contrario)
            {
                if(comprobar_tips(tablero, i, j, 0))
                {
                    return 0;
                }
            }
        }
    }
    printf("Sin Posibilidad de ganar de manera inmediata, y sin peligro de perder\n");
    return 0;
}

int inicializar_juego(char tablero[3][3], int jugadores) 
{
    bool turno_jugador = true;
    int turnos = 0;
    seleccionar_simbolos();
    //Manejo del juego 
    do
    {
        system("@cls||clear");
        imprimir_tablero(tablero);
        printf("\n");
        registrar_tirada(tablero, &turno_jugador, jugadores);
        turnos ++;
    } while (!comprobar_tablero(tablero, turno_jugador, turnos));
    imprimir_tablero(tablero);
    //Obtener si el usuario quiere jugar otra partida o no
    return reiniciar_juego() ? main() : 0;
    return 0;
}
