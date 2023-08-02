

#include "STD_TYPES.h"
#include "defines.h"


#include "TIMER_interface.h"
#include "Kernel_interface.h"
#include "Kernel_private.h"
#include "Kernel_cfg.h"

static Task_t SystemTasks[TASK_NUM] = {{0}}; /* Initialize  all tasks to zero(NULL) */


void RTOS_voidStart(void)
{
    TIMER0_voidInit();
    TIMER0_voidSetCompValue(250u);
    TIMERS_u8SetCallBack(TIMER0_COMP,& scheduler);

}


uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority ,uint16 Copy_u16Periodicity , uint16 Copy_u16FirstDelay ,void (* Copy_pvoidTaskfunc)(void))
{
    uint8 Local_ErrorState = OK;

    if (Copy_pvoidTaskfunc != NULL)
    {

        if (SystemTasks[Copy_u8Priority].TaskFunc == NULL)
        {
            SystemTasks[Copy_u8Priority].Periodicity =  Copy_u16Periodicity ;
            SystemTasks[Copy_u8Priority].TaskFunc    =  Copy_pvoidTaskfunc ;
            SystemTasks[Copy_u8Priority].Status      =  ACTIVE ;
            SystemTasks[Copy_u8Priority].FirstDelay  =  Copy_u16FirstDelay ;
        }
        else
        {
            /* Priority is used before , Caan't overwrite */
            Local_ErrorState = NOK ;
        }
        


    }
    else
    {
        Local_ErrorState = NULL_PTR_ERR;
    }
    

    return Local_ErrorState;
}





void RTOS_voidSuspendTask(uint8 Copy_u8Priority)
{
    SystemTasks[Copy_u8Priority].Status      =  NOT_ACTIVE ;

}

void RTOS_voidResumeTask(uint8 Copy_u8Priority)
{
    SystemTasks[Copy_u8Priority].Status      =  ACTIVE ;

}


void RTOS_voidDeleteTask(uint8 Copy_u8Priority)
{
    SystemTasks[Copy_u8Priority].TaskFunc = NULL ;
}












static void scheduler(void)
{
    
    uint8 Local_u8TaskCounter ;

   


    /* Check the periodicity of each Task */
    for (Local_u8TaskCounter  = 0; Local_u8TaskCounter < TASK_NUM ; Local_u8TaskCounter++)
    {


        /* Check if The periodicity of the current Task */
        if (  SystemTasks[Local_u8TaskCounter].FirstDelay == 0 )
        {



            /* check if the current Task suspended or not */
            if (SystemTasks[Local_u8TaskCounter].Status == ACTIVE )
            {


                /* check if the current Task deleted or not */
                if (SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
                {
                    /* Invoke the Task function */
                    SystemTasks[Local_u8TaskCounter].TaskFunc();
                }
                else
                {
                    /* Deleted Task  */
                }
                

                
            }
            else
            {
                /* Suspended Task */
            }


            SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity - 1 ;

            
            
            
        }
        else
        {
            
            SystemTasks[Local_u8TaskCounter].FirstDelay--;

        }



        
    }
    


}
