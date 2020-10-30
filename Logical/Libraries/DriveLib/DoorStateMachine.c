
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "DriveLib.h"
#ifdef __cplusplus
	};
#endif
void DoorStateMachine(struct DoorStateMachine* inst)
{
	switch(inst->state)
	{
		case ST_INIT:
			{
				//Переход в неизвестное состояние
				inst->state=ST_UNKNOWN;
				break;
			}
		case ST_UNKNOWN:
			{
				//При неизвестном состоянии:
				if(inst->direction==0 && inst->sw4!=inst->swo4) //Открыто
					inst->state=ST_OPEN;
				if(inst->direction==1 && inst->sw1!=inst->swo1) //Закрыто
					inst->state=ST_CLOSE;
				break;
			}		
	//---------------------------------------------------------------------------------------
		case ST_OPEN:
			{
				//При открытом состоянии:
				inst->speed = 0;
				if(inst->direction==0) //При переключении направления -> Старт закрывания
					inst->state=ST_POS; 
				break;
			}
		case ST_POS:
			{
				//При старте закрывания:
				inst->speed = 250;
				
				if(inst->direction==1) //При переключении направления -> Завершение открывания
					inst->state=ST_DEC_NEG;
				if(inst->direction==0 && inst->sw3!=inst->swo3) //При нажатии следующей кнопки -> Закрывание на большой скорости
					inst->state=ST_ACC_POS;
				
				break;
			}
		case ST_ACC_POS:
			{
				//При закрывании на большой скорости
				inst->speed = 750;
				
				if(inst->direction==1) //При переключении направления -> Открывание на большой скорости
					inst->state=ST_ACC_NEG;
				if(inst->direction==0 && inst->sw2!=inst->swo2) //При нажатии следующей кнопки -> Завершение закрывания
					inst->state=ST_DEC_POS;
				
				break;
			}
		case ST_DEC_POS:
			{
				//При завершении закрывания
				inst->speed = 250;
				
				if(inst->direction==1)//При переключении направления -> Старт открывания
					inst->state=ST_NEG;
				if(inst->direction==0 && inst->sw1!=inst->swo1) //При нажатии следующей кнопки -> Закрытое состояние
					inst->state=ST_CLOSE;
				

				break;
			}
	//----------------------------------------------------------------------------
		case ST_CLOSE:
			{
				//При закрытом состоянии:
				inst->speed = 0;
				if(inst->direction==1)//При переключении направления -> Старт открывания
					inst->state=ST_NEG;
				break;
			}
		case ST_NEG:
			{
				//При старте открывания:
				inst->speed = -250;
				
				if(inst->direction==0)//При переключении направления -> Завершение закрывания
					inst->state=ST_DEC_POS;
				if(inst->direction==1 && inst->sw2!=inst->swo2) //При нажатии следующей кнопки -> Открывание на большой скорости
					inst->state=ST_ACC_NEG;
				break;
				
			}
		case ST_ACC_NEG:
			{
				//При открывании на большой скорости
				inst->speed = -750;
				
				if(inst->direction==0) //При переключении направления -> Закрывание на большой скорости
					inst->state=ST_ACC_POS;
				if(inst->direction==1 && inst->sw3!=inst->swo3) //При нажатии следующей кнопки -> Завершение открывания
					inst->state=ST_DEC_NEG;
				break;
			}
		case ST_DEC_NEG:
			{
				//При завершении открывания
				inst->speed = -250;
				
				if(inst->direction==0)//При переключении направления -> Старт закрывания
					inst->state=ST_POS;
				if(inst->direction==1 && inst->sw4!=inst->swo4) //При нажатии следующей кнопки -> Открытое состояние
					inst->state=ST_OPEN;
				break;
			}
	}
	
	//Обновление текущих состояний
	inst->swo1=inst->sw1;
	inst->swo2=inst->sw2;
	inst->swo3=inst->sw3;
	inst->swo4=inst->sw4;
}
