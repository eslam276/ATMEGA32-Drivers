

#ifndef TIMER_REG_H
#define TIMER_REG_H



#define TCCR0            *( (volatile uint8*) 0x53)

#define WGM00            6u
#define WGM01            3u



#define TCNT0            *( (volatile uint8*) 0x52)



#define TIMSK            *( (volatile uint8*) 0x59)
#define TOIE0            0u




#endif