/*
 * STM32F411RE_NVIC.h
 *      Author: velazjor
 */

#ifndef INCLUDE_STM32F411RE_NVIC_H_
#define INCLUDE_STM32F411RE_NVIC_H_

#include "STM32F411RE.h"

void NVIC_IRQ_Habilitar(uint8_t IRQ);
void NVIC_IRQ_Deshabilitar(uint8_t IRQ);
void NVIC_Prioridad(uint8_t Pin, uint8_t IRQ, uint32_t Prioridad);


#endif /* INCLUDE_STM32F411RE_NVIC_H_ */
