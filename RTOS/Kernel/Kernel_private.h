
#ifndef KERNEL_PRIVATE_H
#define KERNEL_PRIVATE_H


typedef struct 
{
    
    uint16 Periodicity;
    void (* TaskFunc)(void);




}Task_t;





 static void scheduler(void);







#endif