#include "DIO.h"
#include "DIO_cfg.h"

PinConfig_t PinConfigs[] = {

	{PIN_0, PORT_B, OUTPUT, FALSE},
	{PIN_1, PORT_B, OUTPUT, FALSE},
	{PIN_2, PORT_B, INPUT, TRUE},

};

unsigned char PinConfigCount = sizeof(PinConfigs) / sizeof(PinConfig_t);