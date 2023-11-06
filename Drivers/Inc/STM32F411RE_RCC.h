/*
 * STM32F411RE_RCC.h
 *      Author: velazjor
 */

#ifndef INCLUDE_STM32F411RE_RCC_H_
#define INCLUDE_STM32F411RE_RCC_H_

#include "STM32F411RE.h"

#define	IS_VALID_PLLM_VALUE(X)	((X < 64) && (X > 1))
#define	IS_VALID_PLLN_VALUE(X)	((X < 433) && (X > 50))
#define	IS_VALID_PLLP_VALUE(X)	((X == 2) || (X == 4) || (X == 6) || (X == 8))
#define	IS_VALID_PLLQ_VALUE(X)	((X < 16) && (X > 1))

/*Configuracion external clocks (On, Off o Bypass)
 * By pass solo es en caso de que sea posible en otra placa con el mismo mcu
 * */

typedef enum
{
	RCC_HSE_OFF,
	RCC_HSE_ON,
	RCC_HSE_BYP,
}RCC_HSE_Status_t;

typedef enum
{
	RCC_LSE_OFF,
	RCC_LSE_ON,
	RCC_LSE_BYP,
}RCC_LSE_Status_t;


typedef enum
{
	RCC_PLL_Source_HSI,
	RCC_PLL_Source_HSE,
}RCC_PLL_Source_t;


typedef enum
{
	RCC_MC01_Source_HSI,
	RCC_MC01_Source_LSE,
	RCC_MC01_Source_HSE,
	RCC_MC01_Source_PLL,
}RCC_MC01_Source_t;


typedef enum
{
	RCC_MC01_Prescaler_None,
	RCC_MC01_Prescaler_2 = 4,
	RCC_MC01_Prescaler_3 = 5,
	RCC_MC01_Prescaler_4 = 6,
	RCC_MC01_Prescaler_5 = 7
}RCC_MC01_Prescaler_t;


typedef enum
{
	RCC_Clock_HSI,
	RCC_Clock_HSE,
	RCC_Clock_PLL,
	RCC_Clock_LSE,
}RCC_Clock_t;

typedef enum
{
	RCC_SYSCLK_Source_HSI,
	RCC_SYSCLK_Source_HSE,
	RCC_SYSCLK_Source_PLL
}RCC_SYSCLK_Source_t;



typedef enum
{
	RCC_AHB_Prescaler_None = 0,
	RCC_AHB_Prescaler_2 = 8,
	RCC_AHB_Prescaler_4	= 9,
	RCC_AHB_Prescaler_8 = 10,
	RCC_AHB_Prescaler_16 =  11,
	RCC_AHB_Prescaler_64 =  12,
	RCC_AHB_Prescaler_128 = 13,
	RCC_AHB_Prescaler_256 = 14,
	RCC_AHB_Prescaler_512 = 15,
}RCC_AHB_Prescaler_t;

typedef enum
{
	RCC_APB_Prescaler_None = 0,
	RCC_APB_Prescaler_2 = 4,
	RCC_APB_Prescaler_4	= 5,
	RCC_APB_Prescaler_8 = 6,
	RCC_APB_Prescaler_16 =  7
}RCC_APB_Prescaler_t;


void RCC_HSEConfig(RCC_HSE_Status_t	HSE_Status);
void RCC_LSEConfig(RCC_LSE_Status_t	lSE_Status);

//Configuracion del PLL
void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ);

//Habilitar/Deshabilitar internal clocks y PLL
void RCC_HSICmd(uint8_t status);
void RCC_LSICmd(uint8_t status);
void RCC_PLLCmd(uint8_t status);

//Configuracion salidas MC01 y MC02
void RCC_MC01Config(RCC_MC01_Source_t MC01_Source, RCC_MC01_Prescaler_t MC01_Prescaler);

//Rutina para esperar a que un determinado click este ok
void RCC_WaitForCLKRDY(RCC_Clock_t clk);

//Configurar la fuente de clock del sistema
void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source);

//Obtener la fuente de clock del sistema
RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void);

// Configurar los prescalers de AHB, PAB1 y APB2
void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler);
void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler);
void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler);


//Obtener frecuencia de clock del sistema y de los buses
uint32_t RCC_GetSYSCLK(void);
uint32_t RCC_GetAHBCLK(void);
uint32_t RCC_GetAPB1CLK(void);
uint32_t RCC_GetAPB2CLK(void);



#endif /* INCLUDE_STM32F411RE_RCC_H_ */


