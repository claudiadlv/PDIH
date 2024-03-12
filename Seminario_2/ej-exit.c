/**
 * @file ej-exit.c
 * @author Claudia de la Vieja
 * @brief Ejemplo el cual al pulsar una leltra del teclado se termina el programa
 * @version 0.1
 * @date 2024-03-12
 * Para compilar c ej-exit
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <dos.h>

void mi_pausa(){
	union REGS inregs, outregs;
	
	//registo -> h bytes registro -> ah
	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs); //Ejecucion de llamada del SO y que actualice estruct registo entrada y salida

}

void mi_exit(){
	union REGS inregs, outregs;
	inregs.x.ax = 0x4C00;
	int86(0x21, &inregs, &outregs);
}

void main(){
	printf("\nPulsa una tecla para terminar...  ");

	mi_pausa();

   mi_exit();
}
