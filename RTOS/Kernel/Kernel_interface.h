
#ifndef KERNEL_INTERFACE_H
#define KERNEL_INTERFACE_H

#include "STD_TYPES.h"


void RTOS_voidStart(void);

uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority ,uint16 Copy_u16Periodicity , void (* Copy_pvoidTaskfunc)(void));

void RTOS_voidSuspendTask(uint8 Copy_u8Priority);
void RTOS_voidResumeTask(uint8 Copy_u8Priority);

void RTOS_voidDeleteTask(uint8 Copy_u8Priority);



#endif