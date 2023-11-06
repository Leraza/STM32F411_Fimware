/*
  @author         : Jorge Azarel Velazquez Hernandez
*/

#include <STM32F411RE.h>
#include <STM32F411RE_GPIO.h>
#include <STM32F411RE_RCC.h>

void delay(int Cuenta);
void Iniciar_GPIO(void);
void HSE_Configurar(void);
void HSI_Configurar(void);
void PLL_Configurar(void);

GPIO_Handle PC10_Debug;
GPIO_Handle PA8_MC01;


int main(void)
{
	double Frecuencia = 1;
	uint8_t bandera = 1;

	Iniciar_GPIO();

	/*
	//------------------ HSE ------------------
	// 1. Configurar HSE como fuente de reloj del sistem
		HSE_Configurar();
	// 2. Configurar MC01 para sacar HSE por el pin PA8
		RCC_MC01Config(RCC_MC01_Source_HSE, RCC_MC01_Prescaler_2);
	// 3. Leer frecuencia de SYSCLK
		Frecuencia = RCC_GetSYSCLK();
		bandera = 0;
	// 4. Mostrar tiempo de procesamiento de espera en PC10
	*/


			//------------------ HSI ------------------
			// 1. Configurar HSI como fuente de reloj del sistem
				HSI_Configurar();
			// 2. Configurar MC01 para sacar HSI por el pin PA8
				RCC_MC01Config(RCC_MC01_Source_HSI, RCC_MC01_Prescaler_4);
			// 3. Leer frecuencia de SYSCLK
				Frecuencia = RCC_GetSYSCLK();
				bandera = 0;
			// 4. Mostrar tiempo de procesamiento de espera en PC10


/*
	//------------------ PLL ------------------
	// 1. Configurar PLL com fuente de reloj del sistema
		PLL_Configurar();
	// 2. Configurar MC01 para sacar PLL por su pin
		RCC_MC01Config(RCC_MC01_Source_PLL, RCC_MC01_Prescaler_None);
	// 3. Leer frecuencia de SYSCLK
		Frecuencia = RCC_GetSYSCLK();
		bandera = 0;
	// 4. Mostrar tiempo de procesamiento de espera en PC10
*/

	while(1)
	{
	}

}

void assert_failed(uint8_t *file, uint32_t line)
{
	while(1); //Quedarnos indefinidamente
}

void PLL_Configurar(void)
{
	// De esta manera obtengo 80 MHz
	uint32_t PLLM, PLLN, PLLP, PLLQ;
	PLLM = 8;
	PLLN = 160;
	PLLP = 2;
	PLLQ = 4;

	// Habilitar HSE
	RCC_HSEConfig(RCC_HSE_ON);
	// Esperar a que HSE este ok
	RCC_WaitForCLKRDY(RCC_Clock_HSE);
	// Configurar el PLL
	RCC_PLLConfig(RCC_PLL_Source_HSE, PLLM, PLLN, PLLP, PLLQ);

	/******************** Habilitar PLL ********************/
	RCC_PLLCmd(Activar);
	// Esperar a que PLL este ok
	RCC_WaitForCLKRDY(RCC_Clock_PLL);

	// Flash Latency
	*((volatile uint32_t *) 0x40023C00) = 0x02;

	// Selecionar PLL_P como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_PLL);
}

void HSI_Configurar(void)
{
	// Habilitar HSI
	RCC_HSICmd(Activar);

	// Esperar a que  HSI este listo (Ok)
	RCC_WaitForCLKRDY(RCC_Clock_HSI);

	// Seleccionar HSI como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_HSI);
}

void HSE_Configurar(void)
{
	// Habilitar HSE
	RCC_HSEConfig(RCC_HSE_ON);

	// Esperar a que  HSE este listo (Ok)
	RCC_WaitForCLKRDY(RCC_Clock_HSE);

	// Seleccionar HSE como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_HSE);

}

void Iniciar_GPIO(void)
{
	PC10_Debug.Puerto = GPIOC;
	PC10_Debug.Configuracion.GPIO_Pin = Pin_10;
	PC10_Debug.Configuracion.GPIO_Modo = Salida;
	PC10_Debug.Configuracion.GPIO_Otyper = Push_Pull;
	PC10_Debug.Configuracion.GPIO_Pull = None;
	PC10_Debug.Configuracion.GPIO_Speed = Fast;
	GPIO_Iniciar(&PC10_Debug);

	PA8_MC01.Puerto = GPIOA;
	PA8_MC01.Configuracion.GPIO_Pin = Pin_8;
	PA8_MC01.Configuracion.GPIO_Modo = Funcion_Alternativa;
	PA8_MC01.Configuracion.GPIO_Funcion_Alternativa = Funcion_Alternativa_0;
	PA8_MC01.Configuracion.GPIO_Speed = Fast;
	GPIO_Iniciar(&PA8_MC01);
}

void delay(int Cuenta)
{
	while(Cuenta)
		Cuenta--;
}
