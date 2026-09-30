
/* Ejercicio 1: Toggle de LED mediante Interrupción Dedicada (EINT0)
 * Nivel: Principiante
 * Objetivo de Hardware: Conectar un pulsador en el pin dedicado P2.10 (EINT0) y un LED verde en P0.22.
 * Cada vez que presiones el pulsador (flanco descendente), el LED debe cambiar de estado (encender si está apagado, apagar si está encendido).
 * Fundamento Técnico: EINT0 es una línea de interrupción directa al NVIC (IRQ 18). No comparte su canal con otros pines de GPIO.
 */
#include "LPC17xx.h"

void confPinLed (){

	LPC_PINCON->PINSEL1 &= ~ (3<<12);
	LPC_GPIO0->FIODIR |= (1 << 22);
	LPC_GPIO0 ->FIOMASK &= ~ (1 <<22);
	LPC_GPIO0 ->FIOCLR |= (1 <<22);
}

void confPinBoton(){
	LPC_PINCON ->PINSEL4 |= (3 << 20); //PONEMOS EL PIN P2.10 EN MODO INTERRUPCION EINT0
	LPC_SC ->EXTMODE |= (1<<0); // SELECCIONAMOS LA ACTIVACION POR FLANCO
	LPC_SC ->EXTPOLAR &= ~ (1<<0); //SELECCIONAMOS LA ACTIVACION POR FLANCO DESCENDENTE
	LPC_SC ->EXTINT |= (1 << 0); //LIMPIAMOS LA FLAG

	LPC_GPIO2 ->FIODIR &= ~ (1 << 10);
	LPC_PINCON->PINMODE4 &= ~ (3 << 20);
	NVIC_EnableIRQ(EINT0_IRQn);
}
void EINT0_Handler(){

	if (LPC_GPIO2 ->FIOSET &~ (1<<10)){
		LPC_GPIO0 ->FIOSET |= (1 <<20);
	}else { LPC_GPIO0 ->FIOCLR |= (1 <<20);	}
}

int main (void){
	confPinLed();
	confPinBoton();
	while(1){__WFI();}
	return 0;
};
