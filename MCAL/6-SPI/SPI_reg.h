/*********************************************************/
/*********************************************************/
/***********		Author: Eslam Nasr  	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/


#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_


#define SPCR   			*((volatile uint8*)0x2D)			//SPI Control Register
#define SPCR_SPIE		7								//SPI Interrupt Enable
#define SPCR_SPE		6								//SPI Enable
#define SPCR_DORD		5 								//Data Order
#define SPCR_MSTR		4								//Master/Slave mode select
#define SPCR_CPOL		3 								//Clock Polarity Select
#define SPCR_CPHA		2 								//Clock Phase Select
#define SPCR_SPR1		1								//CLock Rate Select bit 1
#define SPCR_SPR0   	0 								//Clock Rate Select bit 0


#define SPSR   			*((volatile uint8*)0x2E)			//SPI Status Register
#define SPSR_SPIF		7								//SPI Interrupt Flag
#define sPSR_WCOL		6								//SPI Write Collision Flag
#define SPSR_SPI2X		0								//Clock Rate Select bit 2

#define SPDR   			*((volatile uint8*)0x2F)			//SPI Data Register

#define DDRB	    	*((volatile uint8*)0x37)
#define SPI_SS          4




#endif
