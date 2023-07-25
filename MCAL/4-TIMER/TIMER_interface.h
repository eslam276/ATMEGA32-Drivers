
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H


typedef struct TIMER_interface
{
    Timer0_2_WFGen_Mode_t WFGen ;
    Timer0_2_CTC_Mode_t CTC ;
    Timer0_2_PWM_Mode_t PWM ;
    Timer0_2_Phase_Correct_Mode_t Phase_Correct ;
    CLK_Prescaler_t CLK_Prescaler ;

    uint8 CompValue ;

    

} Timer0_2_cfg_t;




typedef enum
{
    TIMER0_OVF=0,
    TIMER0_COMP,
    TIMER1_COMP,
    TIMER1_ICU

}TIMERS_Int_Src_t;



uint8 Timer0_u8Init(Timer0_2_cfg_t * Copy_pstCFG );



void TIMER0_voidInit(void);


uint8 TIMERS_u8SetCallBack( TIMERS_Int_Src_t Copy_u8TimerIntSource ,  void (* Copy_pvCallBackFunction )(void) );

 
void TIMER0_voidSetCompValue(uint8 Copy_u8Value);




void TIMER1_voidInit(void);
void TIMER1_voidSetCompValue(uint8 Copy_u8Value);

void TIMER1_voidSetTimerVal(uint16 Copy_u16Value);
uint16 TIMER1_u16GetTimerVal(void);


void ICU_voidInit(void);



uint8 ICU_voidSetTriggerSrc(uint8 Copy_u8TriggerSrc);
/* choose the edge 1-FALLING_EDGE
                   2-RISSING_EDGE

**/


uint16 ICU_voidGetVal(void);

void ICU_voidIntEnable(void);
void ICU_voidIntDisable(void);



  



#endif
