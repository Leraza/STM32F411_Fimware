#include "STM32F411RE_TIMER.h"

void TIM_Control_Reloj(TIM_Reg *pTIMx, uint8_t Acccion)
{
	if(Acccion == Activar)
	{
		if(pTIMx == TIM1)
		{
			TIM1_Activar_Reloj();
		}
		else if(pTIMx == TIM2)
		{
			TIM2_Activar_Reloj();
		}
		else if(pTIMx == TIM3)
		{
			TIM3_Activar_Reloj();
		}
		else if(pTIMx == TIM4)
		{
			TIM4_Activar_Reloj();
		}
		else if(pTIMx == TIM5)
		{
			TIM5_Activar_Reloj();
		}
		else if(pTIMx == TIM9)
		{
			TIM9_Activar_Reloj();
		}
		else if(pTIMx == TIM10)
		{
			TIM10_Activar_Reloj();
		}
		else if(pTIMx == TIM11)
		{
			TIM11_Activar_Reloj();
		}
	}
	else if(Acccion == Desactivar)
	{
		if(pTIMx == TIM1)
		{
			TIM1_Desactivar_Reloj();
		}
		else if(pTIMx == TIM2)
		{
			TIM2_Desactivar_Reloj();
		}
		else if(pTIMx == TIM3)
		{
			TIM3_Desactivar_Reloj();
		}
		else if(pTIMx == TIM4)
		{
			TIM4_Desactivar_Reloj();
		}
		else if(pTIMx == TIM5)
		{
			TIM5_Desactivar_Reloj();
		}
		else if(pTIMx == TIM9)
		{
			TIM9_Desactivar_Reloj();
		}
		else if(pTIMx == TIM10)
		{
			TIM10_Desactivar_Reloj();
		}
		else if(pTIMx == TIM11)
		{
			TIM11_Desactivar_Reloj();
		}
	}
}



uint8_t TIM_ObtenerITestatus(TIM_Reg *pTIMx, uint16_t TIM_IT)
{
	uint16_t IT_Estatus = 0, IT_Enable = 0;

	IT_Estatus = pTIMx->SR & TIM_IT;
	IT_Enable = pTIMx->DIER & TIM_IT;

	if(IT_Estatus != (uint16_t)Desactivar && (IT_Enable != (uint16_t)Desactivar))  //Verificar que las flags esten en cero para indigar que hay un interrupcion
	{
		return Activar;
	}
	else
	{
		return Desactivar;
	}
}

void TIM_Limpiar_Bandera_Pendiente(TIM_Reg *pTIMx, uint16_t TIM_IT)
{
	pTIMx->SR = (uint16_t)~TIM_IT;
}


void TIM_TimeBaseIniciar(TIM_handle_t *pTIMHandle)
{
	TIM_Control_Reloj(pTIMHandle->Puerto, Activar); //Activar el reloj
	pTIMHandle->Puerto->ARR = pTIMHandle->TIM_TimeBase.TIM_Period;
	pTIMHandle->Puerto->PSC = pTIMHandle->TIM_TimeBase.TIM_Prescaler;
	pTIMHandle->Puerto->EGR = 1; //Reinicia la cuenta del timer
}

void TIM_Cmd(TIM_Reg *pTIMx, uint8_t Acccion)
{
	//Activar o desactivar el conteo del timer
	if(Acccion == Activar)
	{
		pTIMx->CR1 |= (1 << TIM_CR1_CEN);
	}
	else if(Acccion == Desactivar)
	{
		pTIMx->CR1 &= ~(1 << TIM_CR1_CEN);
	}
}

void TIM_ITConfiguracion(TIM_Reg *pTIMx, uint16_t IT_Tipo, uint8_t Accion)
{
	if(Accion == Activar)
	{
		pTIMx->DIER |= IT_Tipo;
	}
	else if(Accion == Desactivar)
	{
		pTIMx->DIER &= ~IT_Tipo;
	}
}

void TIM_IRQHandler(TIM_handle_t *pTIMHandle)
{
	if(TIM_ObtenerITestatus(pTIMHandle->Puerto , TIM_IT_UI) == Activar)
	{
		TIM_Limpiar_Bandera_Pendiente(pTIMHandle->Puerto, TIM_IT_UI);	//Limpiar la bandera
		TIM_EventCallBack(pTIMHandle->Puerto, TIM_Event_UI);			// a implementar en la aplicacion
	}
}

__attribute__((weak)) void TIM_EventCallBack(TIM_handle_t *pTIMHandle, TIM_Event_t evento)
{

}








