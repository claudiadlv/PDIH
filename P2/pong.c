/**
 * @file pong.c
 * @author Claudia de la Vieja Lafuente
 * @brief PONG
 * @version 0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
 * gcc pong.c -o pong -lncurses
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 50000

void show_menu() {
    clear();
    int max_y, max_x;
    // Obtener el tamaño de la pantalla
    getmaxyx(stdscr, max_y, max_x);
    // Calcular la posición central para el menú
    int start_y = max_y / 2 - 5;
    int start_x = max_x / 2 - 15;

    // Crear una nueva ventana para el menú
    WINDOW *menu_win = newwin(15, 40, start_y, start_x);
    // Dibujar un borde alrededor de la ventana
    box(menu_win, 0, 0); 
    refresh(); 
    
    // Desactivar el parpadeo
    nodelay(stdscr, TRUE);

    mvprintw(start_y - 3, start_x + 2, " ____   ___ __  __   ___");
    mvprintw(start_y - 2, start_x + 2, "|  _   / _  |   | |/ ___|");
    mvprintw(start_y - 1, start_x + 2, "| |_) | | | | | | | |  _");
    mvprintw(start_y, start_x + 2,     "| |   | |_| | |   | |_| |");
    mvprintw(start_y + 1, start_x + 2, "|_|     ___/|_| |_| ____|");

    // Mostrar las opciones del menú
    mvwprintw(menu_win, 3, 2, "1. Iniciar juego");
    mvwprintw(menu_win, 5, 2, "2. Controles");
    mvwprintw(menu_win, 7, 2, "3. Salir del juego");
    mvwprintw(menu_win, 9, 2, "Selecciona una opcion:"); 
    mvwprintw(menu_win, 11, 2, "Realizado por: Claudia de la Vieja"); 

    wrefresh(menu_win); 
}

void show_controls() {
    clear(); 
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    int start_x = max_x / 2 - 15;
    
    // Imprimir los controles del juego
    mvprintw(10, start_x, "Controles del juego:");
    mvprintw(12, start_x, "Jugador 1: W (arriba), S (abajo)");
    mvprintw(14, start_x, "Jugador 2: O (arriba), L (abajo)");
    mvprintw(16, start_x, "Presiona cualquier tecla para volver al menú.");

    refresh(); 
}

int main(int argc, char *argv[]) {
    int x = 5, y = 0;
    int max_y = 25, max_x = 80;
    int next_x = 0;
    int directionx = 1;
    int next_y = 0;
    int directiony = 1;
    
    //Posicion del player 1
    int p1_x = 2, p1_y = max_y/2;
    // Puntaje del jugador 1
    int p1_score = 0; 
    
    //Posicion player 2
    int p2_x = max_x - 2, p2_y = max_y/2;
    // Puntaje del jugador 2
    int p2_score = 0; 

    int ch = 0;

    //Inicializacion ncurser 
    initscr();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    while(1) {
        if (ch == '1') {
            // Iniciar el juego si se presiona la tecla '1'
            break;
                   
        } else if (ch == '2') {
            // Mostrar los controles si se presiona la tecla '2'
            show_controls();
            while (1) {
                ch = getch();
                if (ch != ERR) {
                    break;
                }
            }
        } else if (ch == '3') {
            // Salir del juego si se presiona la tecla '3'
            endwin();
            exit(EXIT_SUCCESS);
        } else {
            show_menu(); // Mostrar el menú al principio del juego y cada vez que se vuelva a mostrar
            ch = getch();
        }
    }
    // Bucle principal del juego
    while(1) {
        clear();
        mvprintw(y, x, "o");

        // Dibujar líneas verticales para el jugador 1
        for(int i = 0; i < 4; i++){
            mvprintw(p1_y + i, p1_x, "||");
        }

        // Dibujar líneas verticales para el jugador 2
        for(int i = 0; i < 4; i++){
            mvprintw(p2_y + i, p2_x, "||");
        }

        // Mostrar los puntajes de los jugadores
        mvprintw(0, max_x / 2 - 10, "Puntaje Jugador 1: %d", p1_score);
        mvprintw(1, max_x / 2 - 10, "Puntaje Jugador 2: %d", p2_score);

        refresh();  	
        ch = getch();

        //Controlador Player 1
        if (ch == 'w' && p1_y > 0)
            p1_y -= 1;
        else if (ch == 's' && p1_y < max_y - 4)
            p1_y += 1;

        //Controlador Player 2
        if (ch == 'o' && p2_y > 0)
            p2_y -= 1;
        else if (ch == 'l' && p2_y < max_y - 4)
            p2_y += 1;   

    	usleep(DELAY);  	

        next_x = x + directionx;
        next_y = y + directiony;    

        if (next_x >= max_x || next_x < 0) {
            directionx *= -1;
            if (next_x < 0) {
                p2_score++;
                if (p2_score >= 3) {
                    clear();
                    mvprintw(max_y / 2, max_x / 2 - 10, "¡Jugador 2 gana con %d puntos!", p2_score);
                    refresh();
                    usleep(2000000);
                    endwin();
                    exit(EXIT_SUCCESS);
                }
            } else {
                p1_score++;
                if (p1_score >= 3) {
                    clear();
                    mvprintw(max_y / 2, max_x / 2 - 10, "¡Jugador 1 gana con %d puntos!", p1_score);
                    refresh();
                    usleep(2000000);
                    endwin();
                    exit(EXIT_SUCCESS);
                }
            }
            x = max_x / 2;
            y = max_y / 2;
        } else {
            x += directionx;
        }   

        if (next_y >= max_y || next_y < 0) {
            directiony *= -1;
        } else {
            y += directiony;
        }

        if (next_x == p1_x && (next_y >= p1_y && next_y <= p1_y + 3)) {
            directionx *= -1;
        }

        if (next_x == p2_x && (next_y >= p2_y && next_y <= p2_y + 3)) {
            directionx *= -1;
        }

        x += directionx;

        usleep(DELAY); 
    }   
    
    endwin();
}