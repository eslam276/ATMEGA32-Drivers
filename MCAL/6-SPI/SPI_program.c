
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_interface.h"
#include "SPI_reg.h"
#include "SPI_cfg.h"


void SPI_voidInit(void)
{
    

   

    #if SPI_MODE == MASTER_MODE

        SET_BIT(DDRB,SPI_SS);
        SET_BIT(SPCR,SPCR_MSTR);


    #elif SPI_MODE == SLAVE_MODE

        CLR_BIT(DDRB,SPI_SS);
        CLR_BIT(SPCR,SPCR_MSTR);

    #else
    #error Wrong configration for SPI_MODE
    #endif



    /* set prescaler */

     #if SPI_MODE == MASTER_MODE

        CLR_BIT(SPSR,SPSR_SPI2X);
        SET_BIT(SPCR,SPCR_SPR0);
        SET_BIT(SPCR,SPCR_SPR1);

    #endif




    /* SPI Enable */
    SET_BIT(SPCR,SPCR_SPE);




}

uint8 SPI_u8Transceive(uint8 Copy_u8Data)
{
    

     SPDR = Copy_u8Data ;
     while ((GET_BIT(SPSR,SPSR_SPIF))== 0);
     
     return SPDR ;


}