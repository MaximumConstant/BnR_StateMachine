
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "DriveLib.h"
#ifdef __cplusplus
	};
#endif

void DriveStateMachine(struct DriveStateMachine* inst)
{
	UINT mask = inst->state & 0x6f;
	if(!inst->enable)
	{
		inst->command = CMD_SHUTDOWN;
	}
	else
	{
		switch (mask)
		{
			//Выключенный двигатель
			case STATE_DISABLED:			
				inst->command = CMD_SHUTDOWN;
				break;
			
			//Готовый двигатель
			case STATE_READY:
				inst->command = CMD_ENABLED;
				break;
			
			//Включенный двигатель
			case STATE_SWITCHED_ON:
				inst->command = CMD_SWITCHED_ON;
				break;
		}
	}	

}
