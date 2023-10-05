#include "M3508_gear.h"

#if defined(EXAMPLE_M3508_GEAR)
	M3508_gear_t example_M3508_gear;
#endif


void M3508_gear_feedback_handler(M3508_gear_t *kit)
{
	M3508_gear_feedback_process(kit);	
	kit->status.output_speed_rpm = kit->feedback.current_rotor_rpm / kit->parameter.reduction_rate;
}

void M3508_gear_init(void)
{
	M3508_Init();
	M3508_gear_parameter_init();
	
}

void M3508_gear_parameter_init(void)
{
	#if defined(EXAMPLE_M3508_GEAR)
		example_M3508_gear.parameter.ESC_ID 		= 4;
		example_M3508_gear.parameter.bus			= &M3508_bus_1;
		example_M3508_gear.parameter.reduction_rate	= 3591/187.f;
	#endif
}

void M3508_gear_set_torque_current_lsb(M3508_gear_t *kit, uint16_t torque_current_lsb, M3508_SINGLE_COMMAND_HOLD_t hold)
{
	kit->command.torque_current_lsb	= torque_current_lsb;
	kit->command.torque_current		= m3508_from_lsb_to_torque_current(kit->command.torque_current_lsb);
	kit->command.torque				= m3508_from_torque_current_to_torque(kit->command.torque_current) * kit->parameter.reduction_rate;
	M3508_gear_command_transmit(kit, hold);
}

