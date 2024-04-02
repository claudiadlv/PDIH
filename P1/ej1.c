/**
 * @file ej1.c
 * @author Claudia de la Vieja Lafuente
 * @brief 
 * @version 0.1
 * @date 2024-03-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <dos.h>

unsigned char cfondo=0;
unsigned char ctexto=1;
char caracter='c';
char caracater2='*';

/**
 * @brief coloca el cursor en una posicion determinada
 * 
 * @param x 
 * @param y 
 */

void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

/**
 * @brief fijar el aspecto del cursor, debe admitir tres valores: Invisible, normal y grueso
 * 
 * @param tipo_cursor 
 */

void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

/**
 * @brief Fija el modo de video deseado
 * 
 * @param modo 
 */

void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

/**
 * @brief obtiene el modo de video actual
 * 
 * @return unsigned char 
 */

unsigned char getvideomode() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F; // Función 0Fh del BIOS para obtener el modo de video actual
    int86(0x10, &inregs, &outregs);
    return outregs.h.al; // El modo de video actual se encuentra en AL
}

/**
 * @brief modifica el color de primer plano con que se mostrarán los caracteres
 * 
 */

void textcolor(char caracter, int color_texto) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = color_texto; // El color de texto va directamente en BL
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

/**
 * @brief modifica el color de fondo con que se mostrarán los caracteres
 * 
 */

void textbackground(char caracter, int color_fondo) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = color_fondo << 4; // Desplazamos el color de fondo a la parte alta del byte BL
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

/**
 * @brief Borra toda la pantalla
 * 
 */

void mi_cls(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/**
 * @brief obtiene un carácter de teclado y lo muestra en pantalla
 * 
 * @return int 
 */

int getche(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

/**
 * @brief escribe un carácter en pantalla
 * 
 * @param caracter 
 */

void cputchar(char caracter) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter; 
    inregs.h.bl = 0x00; 
    inregs.h.bh = 0x00; 
    int86(0x10, &inregs, &outregs);
}


void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

int main(){

	mi_cls();
	
	//Cambiamos de modo de pantalla
	setvideomode(1);	
   	mi_pausa();

	//Coloca el cursor
	gotoxy(11,11);
	
	//obtiene un carácter de teclado y lo muestra en pantalla
	getche();
	mi_pausa();
	mi_cls();
	
	//Cambiar el color de un caracter
	cfondo=4; ctexto=1; // cfondo=4=rojo , ctexto=1=azul
	textcolor(caracter, ctexto); 
	mi_pausa();
	
	//Cambiar el color del fondo
	textcolor(caracater2, cfondo); 
   	mi_pausa();

	//Cambia el tipo de cursor
   	setcursortype(2);
   	mi_pausa();

	getvideomode();
	mi_pausa();

	//Volvemos al modo de video original
	setvideomode(3);	
   	mi_pausa();

	return 0;
} 	