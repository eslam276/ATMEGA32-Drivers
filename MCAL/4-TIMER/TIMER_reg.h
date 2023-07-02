

#ifndef TIMER_REG_H
#define TIMER_REG_H


#define OCR0             *( (volatile uint8*) 0x5C)          /* Output compare match Register */




#define TCCR0            *( (volatile uint8*) 0x53)          /* Timer counter control  Register 0 */

#define TCCR0_COM01            5                             /* Compare match output mode bit 1 */
#define TCCR0_COM00            4                             /* Compare match output mode bit 0 */
#define TCCR0_WGM00            6                             /* Waveform generation mode bit 0 */
#define TCCR0_WGM01            3                             /* Waveform generation mode bit 1 */





#define TCNT0            *( (volatile uint8*) 0x52)          /* Timer counter 0 register */



#define TIMSK            *( (volatile uint8*) 0x59)          /* Timer Mask  Register */
#define TIMSK_TOIE0      0                                   /* Timer0 Overflow Interrupt Enable */
#define TIMSK_OCIE0      1                                   /* Timer0 Compare match Interrupt Enable */





#endif