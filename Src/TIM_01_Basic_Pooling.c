/*
  @author         : Jorge Azarel Velazquez Hernandez
*/

#include <STM32F411RE.h>
#include <STM32F411RE_GPIO.h>
#include <STM32F411RE_TIMER.h>

void Configurar_GPIO(void);
void Configurar_Timer(void);

GPIO_Handle Led;
TIM_handle_t htim_led; //crear el handle para el timer

int main(void)
{
	Configurar_GPIO();
	Configurar_Timer();
	TIM_Cmd(htim_led.Puerto, Activar);

	while(1)
	{
		if(TIM5->SR & TIM_UIF_Flag)	//Verificar si la bandera muestra que la interrupcion ya se atendio
		{
			TIM5->SR &= ~TIM_UIF_Flag;	//Borrar la bandera
			GPIO_Toggle(Led.Puerto, Led.Configuracion.GPIO_Pin);	//Toggle al pin del led
		}
	}
}

void Configurar_GPIO(void)
{
	// Led pin 5
	Led.Puerto = GPIOA;
	Led.Configuracion.GPIO_Pin = Pin_8;	//En lugar de usar el led conectado a la placa se puede el pin8 para ver la señal en el analizador logico
	Led.Configuracion.GPIO_Modo = Salida;
	Led.Configuracion.GPIO_Otyper = Push_Pull;
	Led.Configuracion.GPIO_Pull = Up;
	Led.Configuracion.GPIO_Speed = Low;
	GPIO_Iniciar(&Led);
}

void Configurar_Timer(void)
{
	htim_led.Puerto = TIM5;
	htim_led.TIM_TimeBase.TIM_Period = 31999;
	htim_led.TIM_TimeBase.TIM_Prescaler = 24;
	TIM_TimeBaseIniciar(&htim_led);
}
