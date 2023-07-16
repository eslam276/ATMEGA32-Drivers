/*
 * UART_reg.h
 *
 *       Author: Eslam Nasr
 */

#ifndef UART_REG_H_
#define UART_REG_H_

#define UDR           *((volatile uint16*)0x2C) /*USART data register read/ write*/


#define UCSRA            *((volatile uint8*)0x26)   /*USART control and status register*/
#define UCSRA_RXC       7						   	 /* receive complete*/
#define UCSRA_TXC       6							 /*Transmit complete*/
#define UCSRA_UDRE      5							 /*Data register empty*/
#define UCSRA_FE        4							 /*Frame error*/
#define UCSRA_DOR       3							 /*Data over run*/
#define UCSRA_PE        2							 /*Parity error*/
#define UCSRA_U2X       1							 /*Double USART transmission speed*/
#define UCSRA_MPCM      0							 /*Multi process transmission mode*/


#define UCSRB            *((volatile uint8*)0x2A)   /*USART control and status register*/
#define UCSRB_RXCIE       7						   	 /*RX Complete Interrupt Enable*/
#define UCSRB_TXCIE      6							 /*TX Complete Interrupt Enable*/
#define UCSRB_UDRIE     5							 /*Data Register Empty Interrupt Enable*/
#define UCSRB_RXEN        4							 /*Receiver Enable*/
#define UCSRB_TXEN       3							 /*Transmitter Enable*/
#define UCSRB_UCSZ2        2						 /*Character Size*/
#define UCSRB_RXB8       1							 /*Receive Data Bit 8*/
#define UCSRB_TXB8      0							 /*Transmit Data Bit 8 */


#define UCSRC            *((volatile uint8*)0x40)    /*USART control and status register*/
#define UCSRC_Register Select       7			     /*RX Complete Interrupt Enable*/
#define UCSRC_UMSEL      6							 /*USART Mode Select*/
#define UCSRC_UPM1     5							 /*Parity Mode*/
#define UCSRC_UPM0     4							 /*Parity Mode*/
#define UCSRC_USBS       3							 /*Stop Bit Select*/
#define UCSRC_UCSZ1        2						 /*Character Size*/
#define UCSRC_UCSZ0       1							 /*Character Size*/
#define UCSRC_UCPOL      0							 /*Clock Polarity */


#define UBRRL             *((volatile uint8*)0x29)	 /*USART Baud Rate Registers*/
#define UBRRH             *((volatile uint8*)0x40)	 /*USART Baud Rate Registers*/
#define UBRRL_URSEL      15							 /*Clock Polarity */


#endif /* UART_REG_H_ */
