#ifndef DRIVERS_INCLUDE_STM32F411RE_H_
#define DRIVERS_INCLUDE_STM32F411RE_H_

#include <stdint.h>
/*
  La funcion assert_failed se implementa para que hga lo que nosotros queramos en caso de que falle algun assert
  (Notificar al usuario, Grabar un log, "Colgar el micro", etc...)
*/

void assert_failed(uint8_t *file, uint32_t line);

#define	ASSERT_TRUE(expr)	((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
#define	ASSERT_FALSE(expr)	(!(expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

#define HSE_FREQ			((uint32_t)8000000)
#define HSI_FREQ			((uint32_t)16000000)

#define AHB1_Direccion		0X40020000UL
#define APB1_Direccion		0x40000000UL
#define APB2_Direccion		0x40010000UL
#define EXTI_Direccion		0x40013C00UL
#define SYSCFG_Direccion	0x40013800UL
#define RCC_Direccion		0X40023800UL
#define PWR_Direccion		0X40007000UL

/*--------- Timer que cuelgan del APB2 ---------*/
#define	TIM1_Direccion		0x40010000UL
#define	TIM9_Direccion		0x40014000UL
#define	TIM10_Direccion		0x40014400UL
#define	TIM11_Direccion		0x40014800UL

/*--------- Timer que cuelgan del APB1 ---------*/
#define	TIM5_Direccion		0x40000C00UL
#define	TIM4_Direccion		0x40000800UL
#define	TIM3_Direccion		0x40000400UL
#define	TIM2_Direccion		0x40000000UL

#define NVIC_ISER0			(*((volatile uint32_t *)0XE000E100UL))
#define NVIC_ISER1			(*((volatile uint32_t *)0XE000E104UL))
#define NVIC_ISER2			(*((volatile uint32_t *)0XE000E108UL))
#define NVIC_ICER0			(*((volatile uint32_t *)0XE000E180UL))
#define NVIC_ICER1			(*((volatile uint32_t *)0XE000E184UL))
#define NVIC_ICER2			(*((volatile uint32_t *)0XE000E188UL))

/*Posiciones de bits de los registros*/

#define RCC_CR_HSION		0	// Internal high-speed clock enable
#define RCC_CR_HSIRDY		1	// Internal high-speed clock ready flag
#define RCC_CR_HSITRIM		3	// Bits 7:3 --> Internal high-speed clock trimming
#define RCC_CR_HSICAL		8	// Bits 15:8 --> Internal high-speed clock calibration
#define RCC_CR_HSEON		16	// HSE clock enable
#define RCC_CR_HSERDY		17	// HSE clock ready flag
#define RCC_CR_HSEBYP		18	// HSE clock bypass
#define RCC_CR_CSSON		19	// Clock security system enable
#define RCC_CR_PLLON		24	// Main PLL (PLL) enable
#define RCC_CR_PLLRDY		25	// Main PLL (PLL) clock ready flag
#define RCC_CR_PLLI2SON		26	// PLLI2S enable
#define RCC_CR_PLLI2SRDY	27	// PLLI2S clock ready flag

#define RCC_PLLCFGR_PLLM	0	// Bits 5:0 PLLM: Division factor for the main PLL (PLL) input clock
#define RCC_PLLCFGR_PLLN	6	// Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO
#define RCC_PLLCFGR_PLLP	16	// Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock
#define RCC_PLLCFGR_PLLSRC	22	// Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
#define RCC_PLLCFGR_PLLQ	24	// Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, and SDIO clocks

#define RCC_CFGR_SW			0	// Bits 1:0 SW: System clock switch
#define RCC_CFGR_SWS		2	// Bits 3:2 SWS: System clock switch status
#define RCC_CFGR_HPRE		4	// Bits 7:4 HPRE: AHB prescaler
#define RCC_CFGR_PPRE1		10	// Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
#define RCC_CFGR_PPRE2		13	// Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
#define RCC_CFGR_RTCPRE		16	// Bits 20:16 RTCPRE: HSE division factor for RTC clock
#define RCC_CFGR_MCO1		21	// Bits 22:21 MCO1: Microcontroller clock output 1
#define RCC_CFGR_I2SSRC		23	// Bit 23 I2SSRC: I2S clock selection
#define RCC_CFGR_MCO1PRE	24	// Bits 26:24 MCO1PRE: MCO1 prescaler
#define RCC_CFGR_MCO2PRE	27	// Bits 29:27 MCO2PRE: MCO2 prescaler
#define RCC_CFGR_MCO2		30	// Bits 31:30 MCO2[1:0]: Microcontroller clock output 2

#define RCC_BDCR_LSEON		0	// Bit 0 LSEON: External low-speed oscillator enable
#define RCC_BDCR_LSERDY		1	// Bit 1 LSERDY: External low-speed oscillator ready
#define RCC_BDCR_LSEBYP		2	// Bit 2 LSEBYP: External low-speed oscillator bypass
#define RCC_BDCR_LSEMOD		3	// Bit 3 LSEMOD: External low-speed oscillator bypass
#define RCC_BDCR_RTCSEL		8	// Bits 9:8 RTCSEL[1:0]: RTC clock source selection
#define RCC_BDCR_RTCEN		15	// Bit 15 RTCEN: RTC clock enable
#define RCC_BDCR_BDRST		16	// Bit 16 BDRST: Backup domain software reset

#define RCC_CSR_LSION		0	// Bit 0 LSION: Internal low-speed oscillator enable
#define RCC_CSR_LSIRDY		1	// Bit 1 LSIRDY: Internal low-speed oscillator ready
#define RCC_CSR_RMVF		24	// Bit 24 RMVF: Remove reset flag
#define RCC_CSR_BORRSTF		25	// Bit 25 BORRSTF: BOR reset flag
#define RCC_CSR_PINRSTF		26	// Bit 26 PINRSTF: PIN reset flag
#define RCC_CSR_PORRSTF		27	// Bit 27 PORRSTF: POR/PDR reset flag
#define RCC_CSR_SFTRSTF		28	// Bit 28 SFTRSTF: Software reset flag
#define RCC_CSR_IWDGRSTF	29	// Bit 29 IWDGRSTF: Independent watchdog reset flag
#define RCC_CSR_WWDGRSTF	30	// Bit 30 WWDGRSTF: Window watchdog reset flag
#define RCC_CSR_LPWRRSTF	31	// Bit 31 LPWRRSTF: Low-power reset flag

/*-------------- BITS DE LOS REGISTROS DE TIMERS --------------*/
#define TIM_CR1_CEN			0
#define TIM_CR1_UDIS		1
#define TIM_CR1_URS			2
#define TIM_CR1_OPM			3
#define TIM_CR1_DIR			4
#define TIM_CR1_CMS			5
#define TIM_CR1_ARPE		7
#define TIM_CR1_CKD			8

#define	TIM_CR2_CCDS		3
#define	TIM_CR2_MMS			4
#define	TIM_CR2_TI1S		7

#define	TIM_SMCR_SMS		0
#define	TIM_SMCR_TS			4
#define	TIM_SMCR_MSM		7
#define	TIM_SMCR_ETF		8
#define	TIM_SMCR_ETPS		12
#define	TIM_SMCR_ECE		14
#define	TIM_SMCR_ETP		15

#define	TIM_DIER_UIE		0
#define	TIM_DIER_CC1IE		1
#define	TIM_DIER_CC2IE		2
#define	TIM_DIER_CC3IE		3
#define	TIM_DIER_CC4IE		4
#define	TIM_DIER_TIE		6
#define	TIM_DIER_UDE		8
#define	TIM_DIER_CC1DE		9
#define	TIM_DIER_CC2DE		10
#define	TIM_DIER_CC3DE		11
#define	TIM_DIER_CC4DE		12
#define	TIM_DIER_TDE		14

#define TIM_SR_UIF			0
#define TIM_SR_CC1IF		1
#define TIM_SR_CC2IF		2
#define TIM_SR_CC3IF		3
#define TIM_SR_CC4IF		4
#define TIM_SR_TIF			6
#define TIM_SR_CC1OF		9
#define TIM_SR_CC2OF		10
#define TIM_SR_CC3OF		11
#define TIM_SR_CC4OF		12

#define TIM_EGR_UG			0
#define TIM_EGR_CC1G		1
#define TIM_EGR_CC2G		2
#define TIM_EGR_CC3G		3
#define TIM_EGR_CC4G		4
#define TIM_EGR_TG			6

#define TIM_CCMR1_CC1S		0
#define TIM_CCMR1_OC1FE		2
#define TIM_CCMR1_OC1PE		3
#define TIM_CCMR1_OC1M		4
#define TIM_CCMR1_OC1CE		7
#define TIM_CCMR1_CC2S		8
#define TIM_CCMR1_OC2FE		10
#define TIM_CCMR1_OC2PE		11
#define TIM_CCMR1_OC2M		12
#define TIM_CCMR1_OC2CE		15

#define TIM_CCMR2_CC3S		0
#define TIM_CCMR2_OC3FE		2
#define TIM_CCMR2_OC3PE		3
#define TIM_CCMR2_OC3M		4
#define TIM_CCMR2_OC3CE		7
#define TIM_CCMR2_CC4S		8
#define TIM_CCMR2_OC4FE		10
#define TIM_CCMR2_OC4PE		11
#define TIM_CCMR2_OC4M		12
#define TIM_CCMR2_OC4CE		15

#define	TIM_CCER_CC1E		0
#define	TIM_CCER_CC1P		1
#define	TIM_CCER_CC1NP		3
#define	TIM_CCER_CC2E		4
#define	TIM_CCER_CC2P		5
#define	TIM_CCER_CC2NP		7
#define	TIM_CCER_CC3E		8
#define	TIM_CCER_CC3P		9
#define	TIM_CCER_CC3NP		11
#define	TIM_CCER_CC4E		12
#define	TIM_CCER_CC4P		13
#define	TIM_CCER_CC4NP		15

#define	TIM_CNT_CNT			0
#define	TIM_CNT_CNT_HCV		0

#define	TIM_PSC_PSC			0

#define	TIM_ARR_ARR_0		0
#define	TIM_ARR_ARR_16		16

#define TIM_CCR1_CCR_0		0
#define TIM_CCR1_CCR_16		0

#define TIM_CCR2_CCR0		0
#define TIM_CCR2_CCR16		16

#define TIM_CCR3_CCR0		0
#define TIM_CCR3_CCR16		16

#define TIM_CCR4_CCR0		0
#define TIM_CCR4_CCR16		16

#define TIM_DCR_DBA			0
#define TIM_DCR_DBL			8

#define TIM_DMAR_DMAB		0


/*--------------------------------------------------------*/
//Mascaras de Bit

#define	TIM_UIF_Flag			((uint16_t) 0x0001)
#define	TIM_CC1IF_Flag			((uint16_t) 0x0002)
#define	TIM_CC2IF_Flag			((uint16_t) 0x0004)
#define	TIM_CC3IF_Flag			((uint16_t) 0x0008)
#define	TIM_CC4IF_Flag			((uint16_t) 0x0010)
#define	TIM_COMIF_Flag			((uint16_t) 0x0020)
#define	TIM_TIF_Flag			((uint16_t) 0x0040)
#define	TIM_BIF_Flag			((uint16_t) 0x0080)
#define	TIM_BIF_Flag			((uint16_t) 0x0080)
#define	TIM_CC10F_Flag			((uint16_t) 0x0200)
#define	TIM_CC20F_Flag			((uint16_t) 0x0400)
#define	TIM_CC30F_Flag			((uint16_t) 0x0800)
#define	TIM_CC40F_Flag			((uint16_t) 0x1000)

#define	 TIM_IT_UI				((uint16_t)0x0001)	//Interrupcion por update
#define	 TIM_IT_CC1I			((uint16_t)0x0002)
#define	 TIM_IT_CC2I			((uint16_t)0x0003)
#define	 TIM_IT_CC3I			((uint16_t)0x0008)
#define	 TIM_IT_CC4I			((uint16_t)0x0010)
#define	 TIM_IT_COMI			((uint16_t)0x0020)
#define	 TIM_IT_TI				((uint16_t)0x0040)
#define	 TIM_IT_BI				((uint16_t)0x0080)
#define	 TIM_IT_UD				((uint16_t)0x0100)
#define	 TIM_IT_CC1D			((uint16_t)0x0200)
#define	 TIM_IT_CC2D			((uint16_t)0x0400)
#define	 TIM_IT_CC3D			((uint16_t)0x0800)
#define	 TIM_IT_CC4D			((uint16_t)0x1000)


/*--------------------------------------------------------*/

#define PWR_CR_DBP			8

#define NVIC_IPR_Direccion	0XE000E400UL

#define Activar				1
#define Desactivar			0

/*--------------------------------------------------------------------------*/
/*---------------------------------RCC--------------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	uint32_t Reservado[2];
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	uint32_t Reservado_1[2];
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	uint32_t Reservado_2[2];
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	uint32_t Reservado_3[2];
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	uint32_t Reservado_4[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	uint32_t Reservado_5[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_DCKCFGR;
}RCC_Reg;

#define RCC_Registros	((RCC_Reg *) RCC_Direccion)


/*--------------------------------------------------------------------------*/
/*---------------------------------TIMER-------------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct
{
	volatile uint32_t	CR1;
	volatile uint32_t	CR2;
	volatile uint32_t	SMCR;
	volatile uint32_t	DIER;
	volatile uint32_t	SR;
	volatile uint32_t	EGR;
	volatile uint32_t	CCMR1;
	volatile uint32_t	CCMR2;
	volatile uint32_t	CCER;
	volatile uint32_t	CNT;
	volatile uint32_t	PSC;
	volatile uint32_t	ARR;
	volatile uint32_t	Reservado1;
	volatile uint32_t	CCR1;
	volatile uint32_t	CCR2;
	volatile uint32_t	CCR3;
	volatile uint32_t	CCR4;
	volatile uint32_t	Reservado2;
	volatile uint32_t	DCR;
	volatile uint32_t	DMAR;
	volatile uint32_t	OR;
}TIM_Reg;

#define TIM1				((TIM_Reg *)TIM1_Direccion)
#define TIM2				((TIM_Reg *)TIM2_Direccion)
#define TIM3				((TIM_Reg *)TIM3_Direccion)
#define TIM4				((TIM_Reg *)TIM4_Direccion)
#define TIM5				((TIM_Reg *)TIM5_Direccion)
#define TIM9				((TIM_Reg *)TIM9_Direccion)
#define TIM10				((TIM_Reg *)TIM10_Direccion)
#define TIM11				((TIM_Reg *)TIM11_Direccion)



// Activar los relojes
#define TIM1_Activar_Reloj()			(RCC_Registros->RCC_APB2ENR |= (1 << 0))
#define TIM2_Activar_Reloj()			(RCC_Registros->RCC_APB1ENR |= (1 << 0))
#define TIM3_Activar_Reloj()			(RCC_Registros->RCC_APB1ENR |= (1 << 1))
#define TIM4_Activar_Reloj()			(RCC_Registros->RCC_APB1ENR |= (1 << 2))
#define TIM5_Activar_Reloj()			(RCC_Registros->RCC_APB1ENR |= (1 << 3))
#define TIM9_Activar_Reloj()			(RCC_Registros->RCC_APB2ENR |= (1 << 16))
#define TIM10_Activar_Reloj()			(RCC_Registros->RCC_APB2ENR |= (1 << 17))
#define TIM11_Activar_Reloj()			(RCC_Registros->RCC_APB2ENR |= (1 << 18))

// Desactivar los relojes
#define TIM1_Desactivar_Reloj()			(RCC_Registros->RCC_APB2ENR &= ~(1 << 0))
#define TIM2_Desactivar_Reloj()			(RCC_Registros->RCC_APB1ENR &= ~(1 << 0))
#define TIM3_Desactivar_Reloj()			(RCC_Registros->RCC_APB1ENR &= ~(1 << 1))
#define TIM4_Desactivar_Reloj()			(RCC_Registros->RCC_APB1ENR &= ~(1 << 2))
#define TIM5_Desactivar_Reloj()			(RCC_Registros->RCC_APB1ENR &= ~(1 << 3))
#define TIM9_Desactivar_Reloj()			(RCC_Registros->RCC_APB2ENR &= ~(1 << 16))
#define TIM10_Desactivar_Reloj()			(RCC_Registros->RCC_APB2ENR &= ~(1 << 17))
#define TIM11_Desactivar_Reloj()			(RCC_Registros->RCC_APB2ENR &= ~(1 << 18))

/*--------------------------------------------------------------------------*/
/*---------------------------------GPIO-------------------------------------*/
/*--------------------------------------------------------------------------*/

#define GPIOA_Direccion		(AHB1_Direccion + 0X0000)
#define GPIOB_Direccion		(AHB1_Direccion + 0X0400)
#define GPIOC_Direccion		(AHB1_Direccion + 0X0800)
#define GPIOD_Direccion		(AHB1_Direccion + 0X0C00)
#define GPIOE_Direccion		(AHB1_Direccion + 0X1000)
#define GPIOH_Direccion		(AHB1_Direccion + 0X1C00)

// Habilitar/Deshabilitar/Reset Reloj de Perifericos
#define GPIOA_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<0)
#define GPIOB_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<1)
#define GPIOC_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<2)
#define GPIOD_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<3)
#define GPIOE_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<4)
#define GPIOH_Activar_Reloj()		RCC_Registros->RCC_AHB1ENR |= (1<<7)

#define GPIOA_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<0)
#define GPIOB_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<1)
#define GPIOC_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<2)
#define GPIOD_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<3)
#define GPIOE_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<4)
#define GPIOH_Desactivar_Reloj()	RCC_Registros->RCC_AHB1ENR &= ~(1<<7)

#define GPIOA_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<0); RCC_Registros->RCC_AHB1RSTR &= ~(1<<0);}while(0)
#define GPIOB_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<1); RCC_Registros->RCC_AHB1RSTR &= ~(1<<1);}while(0)
#define GPIOC_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<2); RCC_Registros->RCC_AHB1RSTR &= ~(1<<2);}while(0)
#define GPIOD_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<3); RCC_Registros->RCC_AHB1RSTR &= ~(1<<3);}while(0)
#define GPIOE_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<4); RCC_Registros->RCC_AHB1RSTR &= ~(1<<4);}while(0)
#define GPIOH_Reset_Reloj()			do{RCC_Registros->RCC_AHB1RSTR |= (1<<7); RCC_Registros->RCC_AHB1RSTR &= ~(1<<7);}while(0)

#define SYSCFG_Activar_Reloj()			RCC_Registros->RCC_APB2ENR |= (1<<14)
#define SYSCFG_Desactivar_Reloj()		RCC_Registros->RCC_APB2ENR &= ~(1<<14)

// Estructura con registros de configuracion de GPIO
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t SPEED;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_Reg;

#define GPIOA	((GPIO_Reg *)GPIOA_Direccion)
#define GPIOB	((GPIO_Reg *)GPIOB_Direccion)
#define GPIOC	((GPIO_Reg *)GPIOC_Direccion)
#define GPIOD	((GPIO_Reg *)GPIOD_Direccion)
#define GPIOE	((GPIO_Reg *)GPIOE_Direccion)
#define GPIOH	((GPIO_Reg *)GPIOH_Direccion)

#define PORT_NUMBER(X)	((X == GPIOA) ? 0 : \
						 (X == GPIOB) ? 1 : \
						 (X == GPIOC) ? 2 : \
						 (X == GPIOD) ? 3 : \
						 (X == GPIOE) ? 4 : \
						 (X == GPIOH) ? 5 : 6)

//Interrupciones de GPIO

typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
	uint32_t Reservado[2];
	volatile uint32_t SYSCFG_CMPCR;
}SYSCFG_Reg;

typedef struct
{
	uint32_t EXTI_IMR;
	uint32_t EXTI_EMR;
	uint32_t EXTI_RTSR;
	uint32_t EXTI_FTSR;
	uint32_t EXTI_SWIER;
	uint32_t EXTI_PR;
}EXTI_Reg;

typedef struct
{
	uint32_t CR;
	uint32_t CSR;
}PWR_RegDef_t;

#define	EXTI		((EXTI_Reg *) EXTI_Direccion)
#define SYSFG		((SYSCFG_Reg *) SYSCFG_Direccion)
#define	PRW			((PWR_RegDef_t *) PWR_Direccion)


#define Activar_PWR()		(RCC_Registros->RCC_APB1ENR |= (1 << 28))
#define Desactivar_PWR()	(RCC_Registros->RCC_APB1ENR &= ~(1 << 28))


#endif /* DRIVERS_INCLUDE_STM32F411RE_H_ */
