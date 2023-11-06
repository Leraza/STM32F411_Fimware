/*
 * STM32F411RE_TIMER.h
 *      Author: velazjor
 */

#ifndef INCLUDE_STM32F411RE_TIMER_H_
#define INCLUDE_STM32F411RE_TIMER_H_

#include "STM32F411RE.h"

typedef enum
{
	TIM_Event_UI,
	TIM_Event_CC1I,
	TIM_Event_CC2I,
	TIM_Event_CC3I,
	TIM_Event_CC4I,
	TIM_Event_COMI,
	TIM_Event_TI,
	TIM_Event_BI,
	TIM_Event_CC10,
	TIM_Event_CC20,
	TIM_Event_CC30,
	TIM_Event_CC40
}TIM_Event_t;

typedef enum
{
	TIM_Counter_Mode_UP,
	TIM_Counter_Mode_DOWN,
	TIM_Counter_Mode_Center_Align1,
	TIM_Counter_Mode_Center_Align2,
	TIM_Counter_Mode_Center_Align3
}TIM_Counter_Mode;


//Canales
typedef enum
{
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4
}TIM_Channels_t;

//Polaridades
typedef enum
{
	TIM_ICPolarity_RE,
	TIM_ICPolarity_FE,
	TIM_ICPolarity_RFE //ambas
}TIM_ICPolarity_t;

typedef enum
{
	TIM_ICSelection_Direct = 1,
	TIM_ICSelection_Indirect,
	TIM_ICSelection_TRC
}TIM_ICSelection_t;

typedef enum
{
	TIM_ICPrescaler_NONE,
	TIM_ICPrescaler_2,
	TIM_ICPrescaler_4,
	TIM_ICPrescaler_8
}TIM_ICPrescaler_t;

typedef enum
{

}TIM_ICFilter_t;

typedef struct
{
	TIM_Channels_t TIM_Channel;				//Canales
	TIM_ICPolarity_t TIM_ICPolarity;		//Polaridad de la detecion
	TIM_ICSelection_t TIM_ICSelection;		//Tipo de entrada al prescaler
	TIM_ICPrescaler_t TIM_ICPrescaler;		//Prescaler
	TIM_ICFilter_t	TIM_ICFilter;			//Filtrado
}TIM_IC_t;


typedef struct
{
	uint16_t TIM_Prescaler;
	uint32_t TIM_Period;
	TIM_Counter_Mode Counter_Modo;	//Bit de direccion 0=upcounter, 1=downcounter
}TIM_TimeBase_t;

typedef struct
{
	TIM_Reg *Puerto;
	TIM_TimeBase_t TIM_TimeBase;
	TIM_IC_t	TIM_Input_Capture;
}TIM_handle_t;

/************* APIs *************/

void TIM_Control_Reloj(TIM_Reg *pTIMx, uint8_t Acccion);
void TIM_ITConfiguracion(TIM_Reg *pTIMx, uint16_t IT_Tipo, uint8_t Accion); //Configurar las interrupciones
void TIM_EventCallBack(TIM_handle_t *pTIMHandle, TIM_Event_t evento);
void TIM_IRQHandler(TIM_handle_t *pTIMHandle);
uint8_t TIM_ObtenerITestatus(TIM_Reg *pTIMx, uint16_t TIM_IT); //Ver el estatus de las interrupciones que estan por ser atendidas
void TIM_Limpiar_Bandera_Pendiente(TIM_Reg *pTIMx, uint16_t TIM_IT);

// Time Base
void TIM_TimeBaseIniciar(TIM_handle_t *pTIMHandle);
void TIM_Desactivar(TIM_Reg *pTIMx);
void TIM_Cmd(TIM_Reg *pTIMx, uint8_t Acccion);



#endif /* INCLUDE_STM32F411RE_TIMER_H_ */
