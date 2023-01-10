/*
 * button_cfg.c
 *
 * Created: 12/31/2022 9:59:47 PM
 *  Author: ncm
 */ 

#include "stdtypes.h"
#include "DIO/DIO.h"
#include "button_cfg.h"


/*
Button Configurations
@note : Pin and Port must not be used by another resources
BUTTON_t mapped to button index
i.e BUTTON_0 --> ButtonConfigs[0]
*/
BUTTONConfig_t ButtonConfigs[] = {
		{PIN_0,PORT_D ,FALSE, ACTIVE_HIGH},
		{PIN_1,PORT_D, FALSE, ACTIVE_HIGH},
			};
uint8 ButtonConfigCount = sizeof(ButtonConfigs)/sizeof(BUTTONConfig_t) ;

