#include "STM32F411RE_RCC.h"

void RCC_HSEConfig(RCC_HSE_Status_t	HSE_Status)
{
	//Limpiar los bits del HSE antes de configurarlo (RCC_HSE_OFF)
	RCC_Registros->RCC_CR &= ~(RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_CSSON);
	if(HSE_Status ==  RCC_HSE_ON)
	{
		RCC_Registros->RCC_CR |= (1 << RCC_CR_HSEON);
	}
	else
	{
		RCC_Registros->RCC_CR |= ((1 << RCC_CR_HSEBYP) | (1 << RCC_CR_HSEON));
	}
}

void RCC_LSEConfig(RCC_LSE_Status_t	lSE_Status)
{
	//Habilitar la escritura
	Activar_PWR();
	PRW->CR |= (1 << PWR_CR_DBP);

	//Limpiar los bits del HSE antes de configurarlo (RCC_HSE_OFF)
	RCC_Registros->RCC_BDCR &= ~(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON | RCC_BDCR_LSEMOD);
	if(lSE_Status ==  RCC_LSE_ON)
	{
		RCC_Registros->RCC_BDCR |= (1 << RCC_BDCR_LSEON);
	}
	else
	{
		RCC_Registros->RCC_BDCR |=	((1 << RCC_BDCR_LSEBYP) | (1 << RCC_BDCR_LSEON));
	}

}


void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ)
{
	uint32_t temp_RCC_PLLCFGR;
	ASSERT_TRUE(IS_VALID_PLLM_VALUE(PLLM));
	ASSERT_TRUE(IS_VALID_PLLN_VALUE(PLLN));
	ASSERT_TRUE(IS_VALID_PLLP_VALUE(PLLP));
	ASSERT_TRUE(IS_VALID_PLLQ_VALUE(PLLQ));

	temp_RCC_PLLCFGR = PLLM | (PLLN << RCC_PLLCFGR_PLLN) | ((PLLP >> 1) - 1) << RCC_PLLCFGR_PLLP | (PLL_Source << RCC_PLLCFGR_PLLSRC);

	RCC_Registros->RCC_PLLCFGR = temp_RCC_PLLCFGR;
}

void RCC_HSICmd(uint8_t status)
{
	if(status == Activar)
	{
		RCC_Registros->RCC_CR |= (1 << RCC_CR_HSEON);
	}
	else if(status == Desactivar)
	{
		RCC_Registros->RCC_CR &= ~(1 << RCC_CR_HSEON);
	}
}

void RCC_LSICmd(uint8_t status)
{
	if(status == Activar)
	{
		RCC_Registros->RCC_CR |= (1 << RCC_CR_HSEON);
	}
	else if(status == Desactivar)
	{
		RCC_Registros->RCC_CR &= ~(1 << RCC_CR_HSEON);
	}
}

void RCC_PLLCmd(uint8_t status)
{
	if(status == Activar)
	{
		RCC_Registros->RCC_CR |= (1 << RCC_CR_PLLON);
	}
	else if(status == Desactivar)
	{
		RCC_Registros->RCC_CR &= ~(1 << RCC_CR_PLLON);
	}
}


void RCC_MC01Config(RCC_MC01_Source_t MC01_Source, RCC_MC01_Prescaler_t MC01_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC_Registros->RCC_CFGR;

	//Limpiar los bits de source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_MCO1);
	//Seteamos los bit del source
	temp_RCC_CFGR |= (MC01_Source << RCC_CFGR_MCO1);

	//Limpiar los bits de Prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_MCO1PRE);
	//Seteamos los bit del Prescaler
	temp_RCC_CFGR |= (MC01_Prescaler << RCC_CFGR_MCO1PRE);

	RCC_Registros->RCC_CFGR = temp_RCC_CFGR;
}


void RCC_WaitForCLKRDY(RCC_Clock_t clk)
{
	if(clk == RCC_Clock_HSI)
	{
		while(!(RCC_Registros->RCC_CR & (1 << RCC_CR_HSIRDY)));
	}
	else if(clk == RCC_Clock_HSE)
	{
		while(!(RCC_Registros->RCC_CR & (1 << RCC_CR_HSERDY)));
	}
	else if(clk == RCC_Clock_PLL)
	{
		while(!(RCC_Registros->RCC_CR & (1 << RCC_CR_PLLRDY)));
	}
	else if(clk == RCC_Clock_LSE)
	{
		//Habilitar la escritura
		Activar_PWR();
		PRW->CR |= (1 << PWR_CR_DBP);
		while(!(RCC_Registros->RCC_BDCR & (1 << RCC_BDCR_LSERDY)));
	}

}


void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC_Registros->RCC_CFGR;

	//Limpiar bits de source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_SW);
	// Setear bits de source
	temp_RCC_CFGR |= (SYSCLK_Source << RCC_CFGR_SW);

	RCC_Registros->RCC_CFGR = temp_RCC_CFGR;
}


RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void)
{
	uint32_t sws;

	sws = (RCC_Registros->RCC_CFGR & 0x0C) >> RCC_CFGR_SWS;

	return (RCC_SYSCLK_Source_t)sws;
}


//Configurar prescaler de AHB, APB1 y APB2
void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC_Registros->RCC_CFGR;

	//Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x0F << RCC_CFGR_HPRE);
	// Setear bits de prescaler
	temp_RCC_CFGR |= (AHB_Prescaler << RCC_CFGR_HPRE);

	RCC_Registros->RCC_CFGR = temp_RCC_CFGR;
}

void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC_Registros->RCC_CFGR;

	//Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE1);
	// Setear bits de prescaler
	temp_RCC_CFGR |= (APB1_Prescaler << RCC_CFGR_PPRE1);

	RCC_Registros->RCC_CFGR = temp_RCC_CFGR;
}

void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC_Registros->RCC_CFGR;

	//Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE2);
	// Setear bits de prescaler
	temp_RCC_CFGR |= (APB2_Prescaler << RCC_CFGR_PPRE2);

	RCC_Registros->RCC_CFGR = temp_RCC_CFGR;
}



uint32_t RCC_GetSYSCLK(void)
{
	uint32_t PLL_src;
	uint32_t PLL_M;
	uint32_t PLL_N;
	uint32_t PLL_VCO;
	uint32_t PLL_P;
	uint32_t freq;
	uint32_t rcc_cfgr_sws;

	rcc_cfgr_sws = (RCC_Registros->RCC_CFGR >> RCC_CFGR_SWS) & 0x03;

	if(rcc_cfgr_sws == 0)
	{
		// La frecuencia es del HSI
		freq = HSI_FREQ;
	}
	else if(rcc_cfgr_sws == 1)
	{
		// La frecuencia es del HSE xd
		freq = HSE_FREQ;
	}
	else if(rcc_cfgr_sws == 2)
	{
		// La frecuencia es el PLL
		/***************** PPLP *****************
		 * 	PLL_VCo = (PLL_src / PLLM) * PLLN
		 * 	SYSCLK = PLL_VCo / PLLP
		 * */
		PLL_src = (RCC_Registros->RCC_PLLCFGR >> RCC_PLLCFGR_PLLSRC) & 0x01;
		PLL_M = RCC_Registros->RCC_PLLCFGR & 0x3F;
		PLL_N = (RCC_Registros->RCC_PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FF;

		if(PLL_src == 1)
		{
			// 	HSE es la fuente del reloj del PLL
			PLL_VCO = (HSE_FREQ / PLL_M) * PLL_N;
		}
		else
		{
			// HSI es la fuente del reloj del PLL
			PLL_VCO = (HSI_FREQ / PLL_M) * PLL_N;
		}
		/*
			El software debe configurar estos bits correctamente para que no excedan los 100 MHz en este dominio.
			La frecuencia de salida del PLL = frecuencia VCO / PLLP, con PLLP = 2, 4, 6 o
		 * */
		PLL_P = (((RCC_Registros->RCC_PLLCFGR >> RCC_PLLCFGR_PLLP) & 0x03) + 1) * 2;
		freq = PLL_VCO / PLL_P;
	}

	return freq;
}


uint16_t AHB_prescaler[16] = {1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512};
uint16_t APBx_prescaler[8] = {1,1,1,1,2,4,8,16};

uint32_t RCC_GetAHBCLK(void)
{
	uint32_t rcc_cfgr_hpre;
	uint16_t preescaler;

	rcc_cfgr_hpre = (RCC_Registros->RCC_CFGR >> RCC_CFGR_HPRE) & 0x0F;
	preescaler = AHB_prescaler[rcc_cfgr_hpre];

	return RCC_GetSYSCLK()/preescaler;
}

uint32_t RCC_GetAPB1CLK(void)
{
	uint32_t rcc_cfgr_ppre1;
	uint16_t preescaler;

	rcc_cfgr_ppre1 = (RCC_Registros->RCC_CFGR >> RCC_CFGR_PPRE1) & 0x07;
	preescaler = APBx_prescaler[rcc_cfgr_ppre1];

	return RCC_GetAHBCLK()/preescaler;
}

uint32_t RCC_GetAPB2CLK(void)
{
	uint32_t rcc_cfgr_ppre2;
	uint16_t preescaler;

	rcc_cfgr_ppre2 = (RCC_Registros->RCC_CFGR >> RCC_CFGR_PPRE2) & 0x07;
	preescaler = APBx_prescaler[rcc_cfgr_ppre2];

	return RCC_GetAHBCLK()/preescaler;
}














