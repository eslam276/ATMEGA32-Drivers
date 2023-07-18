/*********************************************************/
/***********		Author: Eslam Nasr  	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_



void SPI_voidInit(void);
uint8 SPI_u8Transceive(uint8 Copy_u8Data);

#endif