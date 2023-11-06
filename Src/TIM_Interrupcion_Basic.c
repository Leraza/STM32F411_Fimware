/*
  @author         : Jorge Azarel Velazquez Hernandez
*/

#include <STM32F411RE.h>
#include <STM32F411RE_RCC.h>
#include <STM32F411RE_GPIO.h>
#include <STM32F411RE_TIMER.h>
#include <STM32F411RE_NVIC.h>

void Configurar_GPIO(void);
void Configurar_Timer(void);

GPIO_Handle Led;
TIM_handle_t htim_led; //crear el handle para el timer

void Contador(int Cuenta)
{
	while(Cuenta)
		Cuenta--;
}

int main(void)
{
	Configurar_GPIO();
	Configurar_Timer();

	TIM_ITConfiguracion(htim_led.Puerto, TIM_IT_UI, Activar);
	TIM_Cmd(htim_led.Puerto, Activar);

	NVIC_IRQ_Habilitar(30);

	while(1);
}

void TIM4_IRQHandler()
{
	TIM_IRQHandler(&htim_led);
}


void TIM_EventCallBack(TIM_handle_t *pTIMHandle, TIM_Event_t evento)
{
	GPIO_Toggle(Led.Puerto, Led.Configuracion.GPIO_Pin);
}


void Configurar_GPIO(void)
{
	// Led pin 5
	Led.Puerto = GPIOA;					// El 5 es el led
	Led.Configuracion.GPIO_Pin = Pin_5;	//En lugar de usar el led conectado a la placa se puede el pin8 para ver la señal en el analizador logico
	Led.Configuracion.GPIO_Modo = Salida;
	Led.Configuracion.GPIO_Otyper = Push_Pull;
	Led.Configuracion.GPIO_Pull = None;
	Led.Configuracion.GPIO_Speed = Low;
	GPIO_Iniciar(&Led);
}

void Configurar_Timer(void)
{
	htim_led.Puerto = TIM4;
	htim_led.TIM_TimeBase.TIM_Period = 62499;
	htim_led.TIM_TimeBase.TIM_Prescaler = 255;
	TIM_TimeBaseIniciar(&htim_led);
}
