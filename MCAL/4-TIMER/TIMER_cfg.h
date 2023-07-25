
#ifndef TIMER_CFG_H
#define TIMER_CFG_H


#include "TIMER_private.h"



typedef enum
{
    SYSTEM = 1 ,
    DIVBY_8,
    DIVBY_64,
    DIVBY_256,
    DIVBY_1024,
    External_CLK_Falling,/* External clock source on T0 pin. Clock on falling edge */
    External_CLK_Rising, /* External clock source on T0 pin. Clock on rising edge */
    

}CLK_Prescaler_t;












/* Configration for timer 0 */


typedef enum
{
    Normal,
    Phase_Correct,
    Fast_PWM,
    CTC

} Timer0_2_WFGen_Mode_t ;



typedef enum
{
    /* PIN OC0 */
    Toggle,
    Clear,
    Set,

} Timer0_2_CTC_Mode_t ;



typedef enum
{
    /* PIN OC0 */ 

    NonInverted, /* Clear OC0 on compare match, set OC0 at TOP */
    Inverted, /* Set OC0 on compare match, clear OC0 at TOP */
   

} Timer0_2_PWM_Mode_t ;



typedef enum
{
    /* PIN OC0 */
    
    NonInverted, /* Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. */
    Inverted, /* Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. */
   

} Timer0_2_Phase_Correct_Mode_t ;
































/* Configration for timer 1 */



typedef enum
{
    Normal,
    Phase_Correct,
    Fast_PWM,
    CTC

} Timer1_WFGen_Mode_t ;


#define ICU_u8_TRIGGER_SRC  RISSING_EDGE


#define ICU_u8_INT_INIT_STATE  ENABLE

#define TIMERMODE    NORMALMODE


#define TIMER_CLOCK   DIVBY_64

#define CTC_VALUE 250u 

#define TIMER1_TOP_VALUE 40000

#define PRELOAD 128



#endif