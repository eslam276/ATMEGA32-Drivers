

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "defines.h"

#include "ADC_reg.h"
#include "ADC_cfg.h"

static void (* ADC_pvNotificationFunc )(void) = NULL;
static uint16 * ADC_pu16ConversionResult = NULL ;

static ADC_ChainConv_t * ADC_pstChainData = NULL;

static uint8 ADC_u8ChannelCounter ; 

static uint8 ADC_u8BusyFlag = IDLE ;
static uint8 ADC_u8IsrSrc ;


void ADC_voidInit(void)
{




    /* Set voltage refrence  */


    #if ADC_u8REF_VOLT == AREF_REF

        CLR_BIT(ADMUX,ADMUX_REFS0);
        CLR_BIT(ADMUX,ADMUX_REFS1);

    #elif ADC_u8REF_VOLT == AVCC_REF


        SET_BIT(ADMUX,ADMUX_REFS0);
        CLR_BIT(ADMUX,ADMUX_REFS1);


    #elif ADC_u8REF_VOLT == INTERNAL_2560mV_REF

        SET_BIT(ADMUX,ADMUX_REFS0);
        SET_BIT(ADMUX,ADMUX_REFS1);


    #else 

        #error Wrong ADC_u8REF_VOLT confegration option 


    #endif








    /* Set ADC Left Adjust Result */

    #if ADC_u8RESOLUTION == EIGHT_BITS

         SET_BIT(ADMUX,ADMUX_ADLAR);

    #elif ADC_u8RESOLUTION == TEN_BITS

         CLR_BIT(ADMUX,ADMUX_ADLAR);

    #else 

        #error Wrong ADC_u8RESOLUTION confegration option 

    #endif






    /* ADC  Auto trigger */


    #if ADC_u8AUTO_TRIGGER   == ENABLE

         SET_BIT(ADCSRA,ADCSRA_ADATE);

    #elif ADC_u8AUTO_TRIGGER == DISABLE

         CLR_BIT(ADCSRA,ADCSRA_ADATE);

    #else 

        #error Wrong ADC_u8AUTO_TRIGGER confegration option 

    #endif




    /* ADC  Interrupt enable */

    #if ADC_u8INT_ENABLE   == ENABLE

         SET_BIT(ADCSRA,ADCSRA_ADIE);

    #elif ADC_u8INT_ENABLE == DISABLE

         CLR_BIT(ADCSRA,ADCSRA_ADIE);

    #else 

        #error Wrong ADC_u8INT_ENABLE confegration option 

    #endif

     





    /* Configure ADC prescaler bits */


    ADCSRA &= PRESCALER_MASK ;
    ADCSRA |= ADC_u8PRESCALER_VAL ;



    /* ADC Enable */

    SET_BIT(ADCSRA,ADCSRA_ADEN); 






}



uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel , uint16 * Copy_pu16Result)
{

    uint8 Local_ErorrState = OK;
   

    if (Copy_pu16Result != NULL)
    {

        /* Check if ADC is not busy */
        if (ADC_u8BusyFlag==IDLE)
        {
            
            uint32 Local_u32TimeOutCounter = 0u ;


            /* Make ADC BusyFlag busy */
            ADC_u8BusyFlag = BUSY ;

            
            ADMUX &= CHANNEL_MASK;
            ADMUX |= Copy_u8Channel ;



            /* Start Conversion */

            SET_BIT(ADCSRA,ADCSRA_ADSC);



            /* Wait until conversion is complete or the timeout is passed */

            while ((GET_BIT(ADCSRA,ADCSRA_ADIF)== 0) && (Local_u32TimeOutCounter<ADC_U32_TIMEOUT))
            {
                Local_u32TimeOutCounter++;
            }

            if (Local_u32TimeOutCounter >= ADC_U32_TIMEOUT)
            {
                /* Loop is broken because flag isn't raised until the timeout is passed */
                Local_ErorrState = TIMEOUT_ERR ;
            }

            else
            {
                /* Loop is broken because flag is raised before the timeout is passed */

                /* clear the conversion complete flag */
                SET_BIT(ADCSRA,ADCSRA_ADIF);


                #if ADC_u8RESOLUTION == EIGHT_BITS

                    *Copy_pu16Result =  ADCH ;


                #elif ADC_u8RESOLUTION == TEN_BITS

                    *Copy_pu16Result =  ADC ;

                #else

                    #error Wrong ADC_u8RESOLUTION confegration option 

                #endif

                /* ADC is now IDLE */
                ADC_u8BusyFlag = IDLE ;

            }
        
      
        }
        else
        {
            /* ADC was busy */
            Local_ErorrState = BUSY_STATE_ERR ;
        }
        
        
        
    }

    else
    {
        Local_ErorrState = NULL_PTR_ERR;
    }


    return Local_ErorrState ;
    
    

    

}



uint8 ADC_u8StartSingleConversionASynch(uint8 Copy_u8Channel ,uint16 * Copy_pu16Result , void (* ptrNotificationFunc)(void))
{

    uint8 Local_ErorrState = OK;
   

    if ( (Copy_pu16Result != NULL) && (ptrNotificationFunc != NULL) )
    {

         /* Check if ADC is not busy */
        if (ADC_u8BusyFlag==IDLE)
        {

            /* Make ADC BusyFlag busy */
            ADC_u8BusyFlag = BUSY ;

            /* Make ISR SRC Sigle Conversion*/
            ADC_u8IsrSrc = SIGLE_CONV_ASYNCH;

            /* Assign the values of the local pointers to the global pointers */
            ADC_pvNotificationFunc   = ptrNotificationFunc ;
            ADC_pu16ConversionResult = Copy_pu16Result ; 


            ADMUX &= CHANNEL_MASK;
            ADMUX |= Copy_u8Channel ;



            /* Start Conversion */ 
            SET_BIT(ADCSRA,ADCSRA_ADSC);


            /* Enable the ADC conversion complete interrupt */
            SET_BIT(ADCSRA,ADCSRA_ADIE);

        }
         else
        {
            /* ADC was busy */
            Local_ErorrState = BUSY_STATE_ERR ;
        }

        

    }
    else
    {
        Local_ErorrState = NULL_PTR_ERR;
    }


    return Local_ErorrState ;
    

}




uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t * Copy_pstChain)
{

    uint8 Local_ErorrState = OK;

    if ( (Copy_pstChain != NULL) &&  (Copy_pstChain->ChainArr != NULL) && (Copy_pstChain->NotificationFunc != NULL) && (Copy_pstChain->ResultArr != NULL))
    {

        /* Check if ADC is not busy */
        if (ADC_u8BusyFlag==IDLE)
        {

            /* Make ADC BusyFlag busy */
            ADC_u8BusyFlag = BUSY ;

            /* Make ISR SRC Chain Conversion*/
            ADC_u8IsrSrc = CHAIN_CONV_ASYNCH;


            /* Initialize global chain data */
            ADC_pstChainData = Copy_pstChain ;

            ADC_u8ChannelCounter = 0u ;


            /* Set first channel  */

            ADMUX &= CHANNEL_MASK;
            ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];



            /* Start the first Conversion */ 
            SET_BIT(ADCSRA,ADCSRA_ADSC);


            /* Enable the ADC conversion complete interrupt */
            SET_BIT(ADCSRA,ADCSRA_ADIE);




        }
        else
        {
            /* ADC was busy */
            Local_ErorrState = BUSY_STATE_ERR ;
        }
        


    }
    else
    {
        Local_ErorrState = NULL_PTR_ERR;
    }
    

}







/**
 * @brief ADC conversion complete ISR
 * 
 */

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{


    /* Single Conversion ISR*/

    if (ADC_u8IsrSrc == SIGLE_CONV_ASYNCH)
    {
        if ( (ADC_pu16ConversionResult != NULL) && (ADC_pvNotificationFunc != NULL) )
        {

            #if ADC_u8RESOLUTION == EIGHT_BITS

                    *ADC_pu16ConversionResult =  ADCH ;


            #elif ADC_u8RESOLUTION == TEN_BITS

                    *ADC_pu16ConversionResult =  ADC ;

            #else

                    #error Wrong ADC_u8RESOLUTION confegration option 

            #endif


                /* Disable the ADC conversion complete interrupt */
                CLR_BIT(ADCSRA,ADCSRA_ADIE);

                /* ADC is now IDLE */
                ADC_u8BusyFlag = IDLE ;

                /* Invoke the application notification func */
                ADC_pvNotificationFunc();


                

        }
        else
        {
            /* NULL Pointers  */
        }
    }






     /* Chain Conversion ISR*/

    else if (ADC_u8IsrSrc == CHAIN_CONV_ASYNCH)
    {

            #if ADC_u8RESOLUTION == EIGHT_BITS

                    ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] =  ADCH ;


            #elif ADC_u8RESOLUTION == TEN_BITS

                    ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] =  ADC ;

            #else

                    #error Wrong ADC_u8RESOLUTION confegration option 

            #endif

            /* channel counter increment */
            ADC_u8ChannelCounter++;

            /* Check the size of the chain */
            if (ADC_u8ChannelCounter < ADC_pstChainData->ChainSize)
            {
                /* chain is not finished yet */
                /* start the next conversion  */

                /* set the next channel */
                ADMUX &= CHANNEL_MASK;
                ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];



                /* Start the next Conversion */ 
                SET_BIT(ADCSRA,ADCSRA_ADSC);
            }
            else
            {
                /* chain is  finished */

                /* Disable the ADC conversion complete interrupt */
                CLR_BIT(ADCSRA,ADCSRA_ADIE);

                /* ADC is now IDLE */
                ADC_u8BusyFlag = IDLE ;

                if (ADC_pstChainData->NotificationFunc != NULL)
                {
                    ADC_pstChainData->NotificationFunc();
                }
                else
                {
                    /* do nothing  */
                }
                
            }
            
            


    }
    
    


     


     /* ADC is now IDLE */
     ADC_u8BusyFlag = IDLE ;
     
}