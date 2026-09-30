/*===============================================================================
* @file
Ejercicio_4_1.c
*
* @brief
Controla un LED conectado al pin P0.22, alternando periódicamente
*
entre los estados encendido y apagado, con un periodo de intermitencia
*
de 200ms.
*
* @details Implementa la temporización mediante interrupciones periódicas
*
(no bloqueante), vía SysTick cada 100 ms.
*
* @author Ing. E. Migliore
*
* @version 3.0
==============================================================================*/


#include "LPC17xx.h"

#define N_TICK 0x98967FU

#define PIN_LED (1<<22)



void confPin (){
	LPC_PINCON ->PINSEL1 &=~ (2 << 12);
	LPC_GPIO0 -> FIODIR |= PIN_LED;
	LPC_GPIO0 ->FIOMASK &= ~ PIN_LED;
	LPC_GPIO0 ->FIOCLR  |= PIN_LED;
}
void confSystick (uint32_N_TICK){
	SysTick->LOAD = N_TICK;
	SysTick ->CTRL = 0X07;
	SysTick->VAL = 0;
}

void SysTick_Handler (){
	if (LPC_GPIO0->FIOPIN & LED_PIN) {
	        LPC_GPIO0->FIOCLR = LED_PIN; // Si estaba encendido, lo apagamos
	    } else {
	        LPC_GPIO0->FIOSET = LED_PIN; // Si estaba apagado, lo encendemos
	    }
}


