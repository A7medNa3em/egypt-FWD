/*
 ******************************************************************************
 * @file           : state.h
 * @author         : Ahmed Naeem
 * @brief          : state header file
 ******************************************************************************
 */

#ifndef STATE_H
#define STATE_H

/************************** State Genertator **************************/

/*State Function*/
#define Define_State(State_Func) void ST_##State_Func()
/*State Symbol*/
#define State(State_Func) ST_##State_Func

/************************** Transtions APIs **************************/

void Pedestrian_Request(int Normal_id);
void Pedestrian_HandlingDone();


/************************** State machines **************************/

extern void (*Normal_State)();
extern void (*Pedestrian_State)();

extern int Normal_Id;

#endif
