
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H



typedef enum
{
    TIMER0_OVF=0,
    TIMER0_COMP,
    TIMER1_COMP

}TIMERS_Int_Src_t;



void TIMER0_voidInit(void);


uint8 TIMERS_u8SetCallBack( TIMERS_Int_Src_t Copy_u8TimerIntSource ,  void (* Copy_pvCallBackFunction )(void) );

 
void TIMER0_voidSetCompValue(uint8 Copy_u8Value);




void TIMER1_voidInit(void);
void TIMER1_voidSetCompValue(uint8 Copy_u8Value);




#endif