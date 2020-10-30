
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	DoorStateMachine(&doorSM);
	driveSM.speed = doorSM.speed;
	DriveStateMachine(&driveSM);
	ledSM.state = doorSM.state;
	LedStateMachine(&ledSM);
}
