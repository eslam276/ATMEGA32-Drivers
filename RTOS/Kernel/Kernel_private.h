
#ifndef KERNEL_PRIVATE_H
#define KERNEL_PRIVATE_H


typedef struct 
{
    
    uint16 Periodicity;
    void (* TaskFunc)(void);

    uint8 Status ;




}Task_t;


#define ACTIVE          1u
#define NOT_ACTIVE      2u



 static void scheduler(void);







#endif