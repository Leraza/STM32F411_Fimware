#ifndef DRIVERS_INCLUDE_STM32F411RE_GPIO_H_
#define DRIVERS_INCLUDE_STM32F411RE_GPIO_H_

#include "STM32F411RE.h"

// Pines
typedef enum
{
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7,
	Pin_8,
	Pin_9,
	Pin_10,
	Pin_11,
	Pin_12,
	Pin_13,
	Pin_14,
	Pin_15,
}GPIO_Pin_t;

// Modo de trabajo
typedef enum
{
	Entrada,				//00
	Salida,					//01
	Funcion_Alternativa,	//10
	Modo_Analogico,			//11
	Interrupcion_RE,
	Interrupcion_FE,
	Interrupcion_ReFe
}GPIO_Modo_t;

// Otyper : determina si un pin GPIO en modo de salida será de tipo push-pull o de tipo drenador abierto (open-drain)
typedef enum
{
	Push_Pull,				//00
	Open_Drain				//01
}GPIO_Otyper_t;

// Speed
typedef enum
{
	Low,					//00
	Medium,					//01
	Fast,					//10
	High					//11
}GPIO_Speed_t;

//Pull-Up, Pull-Down
typedef enum
{
	None,	// No Pull-up, No Pull-Down
	Up,		// Pull-Up
	Down	// Pull-Down
}GPIO_Pull_t;

//Funciones Alternativas
typedef enum
{
	Funcion_Alternativa_0,
	Funcion_Alternativa_1,
	Funcion_Alternativa_2,
	Funcion_Alternativa_3,
	Funcion_Alternativa_4,
	Funcion_Alternativa_5,
	Funcion_Alternativa_6,
	Funcion_Alternativa_7,
	Funcion_Alternativa_8,
	Funcion_Alternativa_9,
	Funcion_Alternativa_10,
	Funcion_Alternativa_11,
	Funcion_Alternativa_12,
	Funcion_Alternativa_13,
	Funcion_Alternativa_14,
	Funcion_Alternativa_15
}GPIO_Funcion_Alternativa_t;

typedef struct
{
	GPIO_Pin_t GPIO_Pin;										//Seleccionar un Pin (GPIO tiene 16 pines)
	GPIO_Modo_t GPIO_Modo;										// Seleccionar el modo de trabajo del pin
	GPIO_Otyper_t GPIO_Otyper;									//Determina si un pin GPIO en modo de salida será de tipo push-pull o de tipo drenador abierto (open-drain)
	GPIO_Speed_t GPIO_Speed;									//Velocidad de operacion
	GPIO_Pull_t	GPIO_Pull;										//Pull-Up, Pull-Down
	GPIO_Funcion_Alternativa_t GPIO_Funcion_Alternativa;		//Funcion Alternativa
}GPIO_Config;

typedef struct
{
	GPIO_Reg	* Puerto;			//Apunta a la Estructura con registros de configuracion de GPIO
	GPIO_Config	Configuracion;
}GPIO_Handle;



/*-------------------------Funciones-------------------------*/
void GPIO_Control_Reloj(GPIO_Reg *Puerto, uint8_t Accion);
void GPIO_Iniciar(GPIO_Handle *GPIO_Handle);
void GPIO_Reset(GPIO_Reg *Puerto);

uint8_t GPIO_LeerPin(GPIO_Reg *Puerto, GPIO_Pin_t Pin);
uint16_t GPIO_LeerPuerto(GPIO_Reg *Puerto);

void GPIO_EscribirPin(GPIO_Reg *Puerto, GPIO_Pin_t Pin, uint8_t Valor);
void GPIO_EscribirPuerto(GPIO_Reg *Puerto, uint16_t Valor);

void GPIO_Toggle(GPIO_Reg *Puerto, GPIO_Pin_t Pin);

void GPIO_IRQHandler(uint8_t Pin);

#endif
