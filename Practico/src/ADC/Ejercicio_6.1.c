/*===============================================================================
* @file
Ejercicio_6_1_2.c
*
* @brief
Se requiere monitorizar la temperatura ambiente mediante un sensor analógico LM35 conectado al canal AD0.0 del ADC..
*
Realizar el muestreo periódico de la señal y la detección de sobrepaso de un umbral crítico de temperatura de 60 °C mediante una
*
alarma técnica visual de prioridad alta, conformada por un LED rojo en el pin P0.22.
*
* @details - Las señales de los sensores LM35 se acondicionan mediante amplificadores operacionales configurados para maximizar el
*
aprovechamiento del rango dinámico del ADC.El acondicionamiento adapta la tensión generada por los sensores al rango de entrada del LPC1769 (0 V a 3.3 V),
*
incrementando la resolución efectiva de la medición y mejorando la inmunidad al ruido durante la adquisición.
*
- Base de tiempo de adquisición: 1 muestra por segundo (1 Hz) mediante el disparo por hardware de MAT0.1 del Timer 0.
*
- Implementación en alto nivel mediante drivers (NXP LPC17xx).
*
* @author Ing. E. Migliore
*
* @version 3.0
==============================================================================*/
#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

const PINSEL_CFG_T cfgPinLed = {
    .port      = PORT_0,           // Puerto 0
    .pin       = PIN_22,           // Pin 22
    .func      = PINSEL_FUNC_00,   // Función GPIO
    .mode      = PINSEL_PULLUP,    // Resistencia de Pull-Up[cite: 2]
    .openDrain = DISABLE           // Modo Push-Pull normal[cite: 2]
};
void configAdc (){
	// 1. Inicializa el reloj y el divisor interno del ADC[cite: 2]
	    ADC_Init(rate);

	    // 2. Enciende el bloque analógico del ADC[cite: 2]
	    ADC_PowerUp();

	    // 3. Configura automáticamente el pin físico asociado al Canal 0 (P0.23 en Tristate)[cite: 2]
	    ADC_PinConfig(ADC_CHANNEL_0);

	    // 4. Habilita el Canal 0 dentro del registro de selección de canales[cite: 2]
	    ADC_ChannelEnable(ADC_CHANNEL_0);

	    // 5. Configura el modo de disparo por hardware mediante el timer (MAT0.1)[cite: 2]
	    ADC_StartCmd(ADC_START_ON_MAT01);

	    // 6. Configura el disparo ante flanco descendente de la señal MAT0.1[cite: 2]
	    ADC_EdgeStartConfig(ADC_START_ON_FALLING);

	    // 7. Habilita la interrupción al finalizar la conversión en el Canal 0[cite: 2]
	    ADC_IntEnable(ADC_INT_CH0);

	    // 8. Habilita la interrupción del ADC en el NVIC del ARM Cortex-M3
	    NVIC_EnableIRQ(ADC_IRQn);
	}

void configLed(){
	PINSEL_ConfigPin (&cfgPinLed);
	// B. Configuración de dirección del Módulo GPIO (Salida Digital)[
	// Usamos la máscara binaria para el bit 22: (1U << 22)[cite: 1]
	GPIO_SetDir(PORT_0, (1U << 22), GPIO_OUTPUT); //[cite: 2]

	// C. Estado Inicial (LED Apagado)[cite: 1, 2]
	GPIO_ClearPins(PORT_0, (1U << 22));
}
void configTimer0 (){}

 int main (void){
	 configAdc ();
	 configLed();
	 configTimer0();

	 while(1){
		 __WFI();

	 }
 };
