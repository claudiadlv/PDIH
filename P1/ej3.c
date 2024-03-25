/**
 * @file ej3.c
 * @author Claudia de la Vieja 
 * @brief Implementar en lenguaje C un programa que establezca modo gráfico CGA (modo=4) para crear dibujos
            sencillos en pantalla.
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dos.h>
int x;
int y;

// Función para establecer el modo gráfico CGA (modo 4)
void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

// Función para dibujar un píxel en las coordenadas (x, y) con el color especificado
void dibujar_pixel(int x, int y, unsigned char color) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x0C; // Función 0Ch para dibujar un píxel
    inregs.h.al = color; // Color del píxel
    inregs.x.cx = x; // Coordenada x del píxel
    inregs.x.dx = y; // Coordenada y del píxel
    int86(0x10, &inregs, &outregs);
}

void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

void mi_cls(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {
    mi_cls();

    setvideomode(4);

    // Dibujar el texto "ᓚ₍ ^. .^₎"
    // ᓚ
    dibujar_pixel(50, 50, 0x0F); // Línea superior
    dibujar_pixel(49, 51, 0x0F); // Línea izquierda
    dibujar_pixel(51, 51, 0x0F); // Línea derecha
    dibujar_pixel(49, 52, 0x0F); // Línea inferior izquierda
    dibujar_pixel(51, 52, 0x0F); // Línea inferior derecha

    // ₍
    dibujar_pixel(60, 50, 0x0F); // Línea superior izquierda
    dibujar_pixel(59, 51, 0x0F); // Línea izquierda
    dibujar_pixel(61, 51, 0x0F); // Línea derecha

    // ^
    dibujar_pixel(70, 50, 0x0F); // Punto central
    dibujar_pixel(69, 51, 0x0F); // Línea izquierda
    dibujar_pixel(71, 51, 0x0F); // Línea derecha

    // .
    dibujar_pixel(80, 50, 0x0F); // Píxel central

    // .
    dibujar_pixel(90, 50, 0x0F); // Píxel central

    // ^
    dibujar_pixel(100, 50, 0x0F); // Punto central
    dibujar_pixel(99, 51, 0x0F); // Línea izquierda
    dibujar_pixel(101, 51, 0x0F); // Línea derecha

    // ₎
    dibujar_pixel(110, 50, 0x0F); // Línea superior derecha
    dibujar_pixel(109, 51, 0x0F); // Línea izquierda
    dibujar_pixel(111, 51, 0x0F); // Línea derecha

    mi_pausa();
    
    setvideomode(3);	
   	mi_pausa();

    return 0;
}