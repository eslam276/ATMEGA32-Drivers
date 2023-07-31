

#include "STD_TYPES.h"
#include "defines.h"


#include "TIMER_interface.h"
#include "Kernel_interface.h"
#include "Kernel_private.h"
#include "Kernel_cfg.h"

static Task_t SystemTasks[TASK_NUM];


void RTOS_voidStart(void)
{
    TIMER0_voidInit();
    TIMER0_voidSetCompValue(250u);
    TIMERS_u8SetCallBack(TIMER0_COMP,& scheduler);

}


uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority ,uint16 Copy_u16Periodicity , void (* Copy_pvoidTaskfunc)(void))
{
    uint8 Local_ErrorState = OK;

    if (Copy_pvoidTaskfunc != NULL)
    {
        SystemTasks[Copy_u8Priority].Periodicity =  Copy_u16Periodicity ;
        SystemTasks[Copy_u8Priority].TaskFunc    =  Copy_pvoidTaskfunc ;

    }
    else
    {
        Local_ErrorState = NULL_PTR_ERR;
    }
    

    return Local_ErrorState;
}


 static void scheduler(void)
 {
    
    uint8 Local_u8TaskCounter ;

    static uint16 Local_u16TickCounter =  0 ;
    Local_u16TickCounter++ ; 

    for (Local_u8TaskCounter  = 0; Local_u8TaskCounter < TASK_NUM ; Local_u8TaskCounter++)
    {
        if ( (Local_u16TickCounter % SystemTasks[Local_u8TaskCounter].Periodicity) == 0 )
        {
            /* Invoke the Task function */
            SystemTasks[Local_u8TaskCounter].TaskFunc();
        }
        else
        {
            /* Do nothing */
        }
        
    }
    


 }
