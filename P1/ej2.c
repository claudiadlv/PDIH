/**
 * @file ej2.c
 * @author Claudia de la Vieja
 * @brief Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dos.h>

unsigned char cfondo=0;
unsigned char ctexto=0;
int i = 0, j = 0; 

char caracter='c';

void textbackground(char caracter, int color_fondo) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = color_fondo << 4; // Desplazamos el color de fondo a la parte alta del byte BL
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

void textcolor(char caracter, int color_texto) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = color_texto; // El color de texto va directamente en BL
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

#include <dos.h> // Incluir la biblioteca dos.h para el uso de la estructura REGS
#include <stdio.h> // Incluir la biblioteca stdio.h para el uso de la función printf

void cputchar(char caracter) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09; // Función 09h para escribir un carácter en pantalla
    inregs.h.al = caracter; // Carácter a imprimir
    inregs.h.bl = 0x00; // Página de pantalla
    inregs.h.bh = 0x00; // Color del carácter y del fondo
    int86(0x10, &inregs, &outregs);
}

void dibujar_recuadro(int x1, int y1, int x2, int y2, int color_texto, int color_fondo) {
    // Establecer el color de fondo y de primer plano
    textbackground(' ', color_fondo);
    textcolor(' ', color_texto);

    // Dibujar el recuadro línea por línea
    for (i = y1; i <= y2; i++) {
        // Mover el cursor a la posición inicial de la línea
        gotoxy(x1, i);

        // Escribir los caracteres para dibujar la línea
        for (j = x1; j <= x2; j++) {
            // Verificar si estamos en una esquina o borde del cuadrado
            if ((i == y1 && (j == x1 || j == x2)) || (i == y2 && (j == x1 || j == x2))) {
                cputchar('*'); // Carácter de borde
            } else if (i != y1 && i != y2 && (j == x1 || j == x2)) {
                cputchar('*'); // Carácter de borde
            } else {
                cputchar(' '); // Carácter de relleno
            }
        }
    }
}

void mi_pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x08; // Función 08h para esperar a que se presione una tecla
    int86(0x21, &inregs, &outregs);
}

void mi_cls(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {
    mi_cls();
    
    cfondo = 1; // Color de fondo
    ctexto = 3; // Color de texto
    
    // Establecer colores
    textbackground(' ', cfondo);
    textcolor(' ', ctexto);
    
    // Llamar a la función para dibujar un recuadro
    dibujar_recuadro(5, 5, 9, 9, ctexto, cfondo); // Coordenadas superior izquierda (5, 5), inferior derecha (9, 9), color de primer plano, color de fondo

    mi_pausa();
    return 0;
}