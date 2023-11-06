#include "STM32F411RE_GPIO.h"

void GPIO_Control_Reloj(GPIO_Reg *Puerto, uint8_t Accion)
{
	if(Accion == Activar)
	{
		if(Puerto == GPIOA)	GPIOA_Activar_Reloj();
		else if(Puerto == GPIOB)	GPIOB_Activar_Reloj();
		else if(Puerto == GPIOC)	GPIOC_Activar_Reloj();
		else if(Puerto == GPIOD)	GPIOD_Activar_Reloj();
		else if(Puerto == GPIOE)	GPIOE_Activar_Reloj();
		else if(Puerto == GPIOH)	GPIOH_Activar_Reloj();
	}
	else if(Accion == Desactivar)
	{
		if(Puerto == GPIOA)	GPIOA_Desactivar_Reloj();
		else if(Puerto == GPIOB)	GPIOB_Desactivar_Reloj();
		else if(Puerto == GPIOC)	GPIOC_Desactivar_Reloj();
		else if(Puerto == GPIOD)	GPIOD_Desactivar_Reloj();
		else if(Puerto == GPIOE)	GPIOE_Desactivar_Reloj();
		else if(Puerto == GPIOH)	GPIOH_Desactivar_Reloj();
	}
}


void GPIO_Iniciar(GPIO_Handle *GPIO_Handle)
{
	// Habilitar el Clock
	GPIO_Control_Reloj(GPIO_Handle->Puerto, Activar);
	// Configurar Modo
	if(GPIO_Handle->Configuracion.GPIO_Modo > Modo_Analogico)
	{
		// Modo con interrupcion
		//Configurar flancos de disparos
		if(GPIO_Handle->Configuracion.GPIO_Modo == Interrupcion_FE)
		{
			EXTI->EXTI_FTSR |= (1 << GPIO_Handle->Configuracion.GPIO_Pin);
			EXTI->EXTI_RTSR &= ~(1 << GPIO_Handle->Configuracion.GPIO_Pin);
		}
		else if(GPIO_Handle->Configuracion.GPIO_Modo == Interrupcion_RE)
		{
			EXTI->EXTI_RTSR |= (1 << GPIO_Handle->Configuracion.GPIO_Pin);
			EXTI->EXTI_FTSR &= ~(1 << GPIO_Handle->Configuracion.GPIO_Pin);
		}
		else if(GPIO_Handle->Configuracion.GPIO_Modo == Interrupcion_ReFe)
		{
			EXTI->EXTI_FTSR |= (1 << GPIO_Handle->Configuracion.GPIO_Pin);
			EXTI->EXTI_RTSR |= (1 << GPIO_Handle->Configuracion.GPIO_Pin);
		}
		//Configurar SYSCFG
		SYSCFG_Activar_Reloj();
		uint8_t Registro = GPIO_Handle->Configuracion.GPIO_Pin/4;
		uint8_t Bloque = GPIO_Handle->Configuracion.GPIO_Pin%4;
		SYSFG->SYSCFG_EXTICR[Registro] &= ~(0X0F << (Bloque * 4));
		SYSFG->SYSCFG_EXTICR[Registro] |= (PORT_NUMBER(GPIO_Handle->Puerto) << (Bloque * 4));

		//Habilitar la interrupcion EXTI
		EXTI->EXTI_IMR |= (1 << GPIO_Handle->Configuracion.GPIO_Pin);
	}
	else
	{
		// Modo sin interrupcion
		GPIO_Handle->Puerto->MODER &= ~(0x03 << (GPIO_Handle->Configuracion.GPIO_Pin * 2));	//Reset
		GPIO_Handle->Puerto->MODER |= (GPIO_Handle->Configuracion.GPIO_Modo << (GPIO_Handle->Configuracion.GPIO_Pin * 2));	//Set
	}

	// Configurar Speed
	GPIO_Handle->Puerto->SPEED &= ~(0x03 << (GPIO_Handle->Configuracion.GPIO_Pin * 2));	//Reset
	GPIO_Handle->Puerto->SPEED |= (GPIO_Handle->Configuracion.GPIO_Speed << (GPIO_Handle->Configuracion.GPIO_Pin * 2));	//Set

	// Configurar Pull-Up o Pull-Down
	GPIO_Handle->Puerto->PUPDR |= (0x01 << (GPIO_Handle->Configuracion.GPIO_Pin * 2));
	GPIO_Handle->Puerto->PUPDR |= (GPIO_Handle->Configuracion.GPIO_Pull << (GPIO_Handle->Configuracion.GPIO_Pin * 2));

	// Configurar Tipo de Salida
	GPIO_Handle->Puerto->OTYPER &= ~(0x01 << GPIO_Handle->Configuracion.GPIO_Pin); //Reset
	GPIO_Handle->Puerto->OTYPER |= (GPIO_Handle->Configuracion.GPIO_Otyper << GPIO_Handle->Configuracion.GPIO_Pin); //Reset

	// Configurar Funcion Alternativa
	if(GPIO_Handle->Configuracion.GPIO_Modo == Funcion_Alternativa)
	{
		uint8_t Registro = GPIO_Handle->Configuracion.GPIO_Pin/8;
		uint8_t Bloque = GPIO_Handle->Configuracion.GPIO_Pin%8;
		GPIO_Handle->Puerto->AFR[Registro] &= ~(0x0F << (Bloque * 4)); // Poner el bloque a 1
		GPIO_Handle->Puerto->AFR[Registro] |= (GPIO_Handle->Configuracion.GPIO_Funcion_Alternativa << (Bloque * 4));
	}
}


void GPIO_Reset(GPIO_Reg *Puerto)
{
	if(Puerto == GPIOA)	GPIOA_Reset_Reloj();
	else if(Puerto == GPIOB)	GPIOB_Reset_Reloj();
	else if(Puerto == GPIOC)	GPIOC_Reset_Reloj();
	else if(Puerto == GPIOD)	GPIOD_Reset_Reloj();
	else if(Puerto == GPIOE)	GPIOE_Reset_Reloj();
	else if(Puerto == GPIOH)	GPIOH_Reset_Reloj();
}

uint8_t GPIO_LeerPin(GPIO_Reg *Puerto, GPIO_Pin_t Pin)
{
	return (uint8_t)((Puerto->IDR >> Pin) & 0x01);
}

uint16_t GPIO_LeerPuerto(GPIO_Reg *Puerto)
{
	return (uint16_t)(Puerto->IDR & 0xFFFF);
}

void GPIO_EscribirPin(GPIO_Reg *Puerto, GPIO_Pin_t Pin, uint8_t Valor)
{
	if(Valor == Activar)
		Puerto->ODR |= (1<<Pin);
	else if(Valor == Desactivar)
		Puerto->ODR &= ~(1<<Pin);
}

void GPIO_EscribirPuerto(GPIO_Reg *Puerto, uint16_t Valor)
{
	Puerto->ODR = (uint32_t) Valor;
}

void GPIO_Toggle(GPIO_Reg *Puerto, GPIO_Pin_t Pin)
{
	Puerto->ODR	^= (1<<Pin);
}

void GPIO_IRQHandler(uint8_t Pin)
{
	if(EXTI->EXTI_PR & (1 << Pin))
	{
		EXTI->EXTI_PR |= (1 << Pin);
	}
}


