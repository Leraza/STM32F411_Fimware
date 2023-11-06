#include "STM32F411RE_NVIC.h"

void NVIC_IRQ_Habilitar(uint8_t IRQ)
{
	if(IRQ < 32)
	{
		NVIC_ISER0 |= (1 << IRQ);
	}
	else if(IRQ < 64)
	{
		NVIC_ISER1 |= (1 << (IRQ - 32));
	}
	else if(IRQ < 96)
	{
		NVIC_ISER2 |= (1 << (IRQ - 64));
	}
}

void NVIC_IRQ_Deshabilitar(uint8_t IRQ)
{
	if(IRQ < 32)
	{
		NVIC_ICER0 |= (1 << IRQ);
	}
	else if(IRQ < 64)
	{
		NVIC_ICER1 |= (1 << (IRQ - 32));
	}
	else if(IRQ < 96)
	{
		NVIC_ICER2 |= (1 << (IRQ - 64));
	}
}

void NVIC_Prioridad(uint8_t Pin, uint8_t IRQ, uint32_t Prioridad)
{
	uint8_t Registro = Pin/4;
	uint8_t Bloque = Pin%4;

	uint32_t *NVIC_IPR = (uint32_t *)(NVIC_IPR_Direccion + (Registro * 4));
	*NVIC_IPR &= ~(0XFF << (Bloque * 8));
	*NVIC_IPR |= ~(Prioridad << (Bloque * 8 + 4));
}
