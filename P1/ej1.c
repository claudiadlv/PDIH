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

/**
 * @brief coloca el cursor en una posicion determinada
 * 
 * @param x 
 * @param y 
 */

void xy(int x, int y){
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
 * @brief modifica el color de primer plano con que se mostrarán los caracteres y tambien modifica el color del fondo
 * 
 */

void escribir_char_con_color(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = '*';    //una funcion más general debe recibir el caracter a imprimir
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
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

int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

int main(){
	xy(11,11);
	printf("**");

	mi_pausa();

	return 0;
}