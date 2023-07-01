
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_reg.h"
#include "TIMER_cfg.h"


#include "TIMER_interface.h"




static uint16 counter ;

void (*func)(void) ;


void TIMER_voidActiveT0(void (*ptrf)(void))
{

    CLR_BIT(TCCR0,WGM00);
    CLR_BIT(TCCR0,WGM01);

    TCCR0 &= 0b11111000;
    TCCR0 |= DIVBY_8;

    TCNT0 = PRELOAD;

    SET_BIT(TIMSK,TOIE0);



    counter = 0 ;
    func = ptrf ;

}



void __vector_11(void)   __attribute((signal));

void __vector_11(void)
{
    counter++;
    if (counter==7813)
    {
        
        counter = 0 ;
        TCNT0 = PRELOAD;

        func();

    }
    
}







