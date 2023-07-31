
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"


#include "TIMER_reg.h"
#include "TIMER_private.h"
#include "TIMER_cfg.h"
#include "TIMER_interface.h"




static uint16 counter ;




/* Global ARR of pointers to functions */

static void (* TIMERS_pvCallBackFuncArr [8])(void) = {NULL} ;





uint8 TIMERS_u8SetCallBack( TIMERS_Int_Src_t Copy_u8TimerIntSource ,  void (* Copy_pvCallBackFunction )(void) )
{

    uint8 LOCAL_u8ErrorState = OK ;

    if (Copy_pvCallBackFunction != NULL)
    {
       TIMERS_pvCallBackFuncArr[Copy_u8TimerIntSource]= Copy_pvCallBackFunction ;
    }
    else
    {
        LOCAL_u8ErrorState = NOK ;
    }





    return LOCAL_u8ErrorState ;

}


void TIMER0_voidInit(void)
{

    /* Waveform generation mode : CTC */

    CLR_BIT(TCCR0,TCCR0_WGM00);
    SET_BIT(TCCR0,TCCR0_WGM01);

 

    /* Set prescaler */

    TCCR0 &= PRESCALER_MASK;
    TCCR0 |= TIMER_CLOCK;



    /* Output compare match interrupt enable */

     SET_BIT(TIMSK,TIMSK_OCIE0);




}



void TIMER0_voidSetCompValue(uint8 Copy_u8Value)
{
    OCR0 = Copy_u8Value ;
}







/* 42 Datasheet vector table */






/* ISR for TIMER 0 Overflow */

void __vector_11(void)   __attribute((signal));

void __vector_11(void)
{
    counter++;
    if (counter==7813)
    {
        
        counter = 0 ;
        TCNT0 = PRELOAD;

         TIMERS_pvCallBackFuncArr[TIMER0_OVF]();

    }
    
}





/* ISR for TIMER 0 Copmare match */

void __vector_10 (void)   __attribute((signal));

void __vector_10(void)
{



        if (TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
        {
             TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
        }
        
    
    
    
}

