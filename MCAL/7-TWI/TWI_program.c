/*********************************************************/
/*********************************************************/
/***********		Author: Eslam Nasr     	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TWI       	**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"
#include "TWI_config.h"

void TWI_voidInitMaster(uint8 Copy_u8MasterAddress) {

	//Enable Acknowledge bit
	SET_BIT(TWCR, TWCR_TWEA);

	//Set SCL Frequency to 400kHz , with 16Mhz system frequency
	//Set TWBR to 12
	TWBR = 12u;

	//Clear the two prescalar bits
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);

	//Check if the master node will be addressed
	if (Copy_u8MasterAddress != NO_ADDRESS) {

		//Set the required Address in the 7 MSB
		TWAR = Copy_u8MasterAddress << 1;

	} else {

		/*Do nothing*/
	}

	//Enable TWI
	SET_BIT(TWCR, TWCR_TWEN);

}

void TWI_voidInitSlave(uint8 Copy_u8Address) {

	//Set the Slave Address
	TWAR = Copy_u8Address << 1u;

	//Enable Acknowledge bit
	SET_BIT(TWCR, TWCR_TWEA);

	//Enable TWI
	SET_BIT(TWCR, TWCR_TWEN);

}

TWI_ErrorStatus TWI_SendStartCondition(void) {

	TWI_ErrorStatus Local_ErrorState = NoError;

	//Send Start condition
	SET_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Polling until operation finished and flag is raised
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	//Check the Operation status
	if ((TWSR & STATUS_MASK) != START_ACK) {

		Local_ErrorState = StartConditionError;

	} else {

		/*Do nothing */
	}

	return Local_ErrorState;

}

TWI_ErrorStatus TWI_SendRepeatedStart(void) {

	TWI_ErrorStatus Local_ErrorState = NoError;

	//Send Start condition
	SET_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Polling until operation finished and flag is raised
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	//Check the Operation status
	if ((TWSR & STATUS_MASK) != REP_START_ACK) 
	{

		Local_ErrorState = RepeatedStartError;

	} 
	else 
	{

		/*Do nothing */
	}

	return Local_ErrorState;

}

TWI_ErrorStatus TWI_SendSlaveAddressWithWrite(uint8 Copu_u8SlaveAddress) {

	TWI_ErrorStatus Local_ErrorState = NoError;

		//Send the 7 bit Address to the data bus with write request
	TWDR = (Copu_u8SlaveAddress << 1u);

	//Set the request to write
	CLR_BIT(TWDR, 0u);

	//Clear the start condition bit
	CLR_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Polling until operation finished and flag is raised
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	//Check the Operation status
	if ((TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK) {

		Local_ErrorState = SlaveAddressWithWriteError;

	} else {

		/*Do nothing */
	}

	return Local_ErrorState;

}

TWI_ErrorStatus TWI_SendSlaveAddressWithRead(uint8 Copu_u8SlaveAddress) {

	TWI_ErrorStatus Local_ErrorState = NoError;



	//Send the 7 bit Address to the data bus with read request
	TWDR = (Copu_u8SlaveAddress << 1);

	//Set the request to read
	SET_BIT(TWDR, 0u);

	//Clear the start condition bit
	CLR_BIT(TWCR, TWCR_TWSTA);

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Polling until operation finished and flag is raised
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	//Check the Operation status
	if ((TWSR & STATUS_MASK) != SLAVE_ADD_AND_RD_ACK) {

		Local_ErrorState = SlaveAddressWithReadError;

	} else {

		/*Do nothing */
	}

	return Local_ErrorState;

}

TWI_ErrorStatus TWI_MasterWriteDataByte(uint8 Copy_u8DataByte) {

	TWI_ErrorStatus Local_ErrorState = NoError;

	//Write the Data Byte on the bus
	TWDR = Copy_u8DataByte;

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

	//Polling until operation finished and flag is raised
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0)
		;

	//Check the Operation status
	if ((TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK) {

		Local_ErrorState = MasterWriteByteError;

	} else {

		/*Do nothing */
	}

	return Local_ErrorState;

}

TWI_ErrorStatus TWI_MasterReadDataByte(uint8 * Copy_pu8DataByte) {

	TWI_ErrorStatus Local_ErrorState = NoError;

	if (Copy_pu8DataByte != NULL)
	{
		//Clear the interrupt flag to allow the slave to send the data
		SET_BIT(TWCR, TWCR_TWINT);

		//Polling until operation finished and flag is raised
		while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

		//Check the Operation status
		if ((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK) 
		{

			Local_ErrorState = MasterReadByteError;

		} 
		 else 
		{

			* Copy_pu8DataByte = TWDR;
		}

	}
	else
	{
		 Local_ErrorState = NULLPtrError ;
	}
	
	

	
	return Local_ErrorState;

}

void TWI_SendStopCondition(void) {

	//Send the Stop Condition on the bus
	SET_BIT(TWCR, TWCR_TWSTO);

	//Clear the interrupt flag to start the previous operation
	SET_BIT(TWCR, TWCR_TWINT);

}

