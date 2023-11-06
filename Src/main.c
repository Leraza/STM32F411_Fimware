/*
  @author         : Jorge Azarel Velazquez Hernandez
*/

#include <STM32F411RE.h>
#include <STM32F411RE_GPIO.h>

void Contador(int Cuenta);
void Iniciar_GPIO(void);

GPIO_Handle Led;
GPIO_Handle Boton;

int main(void)
{
	Iniciar_GPIO();
	while(1)
	{
		if(!GPIO_LeerPin(Boton.Puerto, Boton.Configuracion.GPIO_Pin))
		{
			Contador(500000);
			GPIO_Toggle(Led.Puerto, Led.Configuracion.GPIO_Pin);
		}
	}
}

void Iniciar_GPIO(void)
{
	Led.Puerto = GPIOA;
	Led.Configuracion.GPIO_Pin = Pin_5;
	Led.Configuracion.GPIO_Modo = Salida;
	Led.Configuracion.GPIO_Otyper = Push_Pull;
	Led.Configuracion.GPIO_Pull = Up;
	Led.Configuracion.GPIO_Speed = Low;

	GPIO_Iniciar(&Led);

	Boton.Puerto = GPIOC;
	Boton.Configuracion.GPIO_Pin = Pin_13;
	Boton.Configuracion.GPIO_Modo = Entrada;
	Boton.Configuracion.GPIO_Pull = None;
	Boton.Configuracion.GPIO_Speed = Low;

	GPIO_Iniciar(&Boton);
}

void Contador(int Cuenta)
{
	while(Cuenta)
		Cuenta--;
}
