/*
 * button_cfg.h
 *
 * Created: 12/31/2022 9:59:26 PM
 *  Author: ncm
 */ 


#ifndef BUTTON_CFG_H_
#define BUTTON_CFG_H_


typedef struct
{
	PIN_t buttonpin;
	PORT_t buttonport;
	PULLUP_t internalpullup;
	ActiveState_t activestate;
}BUTTONConfig_t;

extern BUTTONConfig_t ButtonConfigs[];
extern uint8 ButtonConfigCount ;



#endif /* BUTTON_CFG_H_ */