/*******************************************************************************
* File Name: `$INSTANCE_NAME`_BOOT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the bootloader communication APIs for the
*  I2C component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BOOTLOADER_INTERFACE_ENABLED)


/***************************************
*    Bootloader Internal Variables
***************************************/

/* I2C write buffer - The host writes commands here */
static uint8 XDATA `$INSTANCE_NAME`_slReadBuf[`$INSTANCE_NAME`_BTLDR_SIZEOF_READ_BUFFER];

/* I2C read buffer - The host reads responses from it */
static uint8 XDATA `$INSTANCE_NAME`_slWriteBuf[`$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER];


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the communication component and enables the interrupt.
*  The read buffer initial state is full and the read always is 0xFFu.
*  The write buffer is clear and ready to receive a commmand.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function enables the component interrupt. If I2C is enabled
*  without the interrupt enabled, it can lock up the I2C bus.
*
* Global variables:
*  `$INSTANCE_NAME`_slWriteBuf - The global variable used to store a received
*                                command.
*  `$INSTANCE_NAME`_slReadBuf -  The global variable used to store a response.
*  `$INSTANCE_NAME`_slRdBufIndex - The global variable used to store a current
*                                  index within the slave read buffer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStart(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`
{
    /* Read returns 0xFF when buffer is zero. Write transaction is expected. */
    `$INSTANCE_NAME`_SlaveInitWriteBuf(`$INSTANCE_NAME`_slWriteBuf, `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER);
    `$INSTANCE_NAME`_SlaveInitReadBuf (`$INSTANCE_NAME`_slReadBuf, 0u);

    `$INSTANCE_NAME`_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the communication component and disables the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStop(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`
{
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Set buffers to the initial state and reset the statuses.
*  The read buffer initial state is full and the read always is 0xFFu.
*  The write buffer is clear and ready to receive a command.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_slRdBufIndex - The global variable used to store a current
*                                  index within the slave read buffer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommReset(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`
{
    /* Make Read buffer full */
    `$INSTANCE_NAME`_slRdBufSize = 0u;

    /* Reset Write buffer and Read buffer */
    `$INSTANCE_NAME`_slRdBufIndex = 0u;
    `$INSTANCE_NAME`_slWrBufIndex = 0u;

    /* Clear read and write status */
    `$INSTANCE_NAME`_slStatus = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Transmits the status of executed command to the Host.
*  The function updates the I2C read buffer with response and realeases it to
*  the host. All reads return 0xFF till the buffer will be released. All bytes
*  are transfered by the I2C ISR.
*  The function waits with timeout till all bytes will be read.
*  After exist this function the reads return 0xFF.
*
* Parameters:
*  pData:    pointer to data buffer with response command.
*  size:     number of bytes required to be transmitted.
*  count:    actual size of data was transmitted.
*  timeOut:  timeout value in tries of 10uS.
*
* Return:
*  The status of transmit operation.
*
* Global variables:
*  `$INSTANCE_NAME`_slReadBuf - The global variable used to store a response.
*  `$INSTANCE_NAME`_slRdBufIndex - The global variable used to store a current
*                                  index within the slave read buffer.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
         `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`
{
    cystatus status;
    uint16 timeoutMs;

    status = CYRET_BAD_PARAM;

    if((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS check to 1mS checks */

        /* Copy pData to component buffer */
        (void) memcpy((void *) `$INSTANCE_NAME`_slReadBuf, (void *) pData, size);
        *count = size;  /* Buffer was copied to I2C buffer */

        /* Buffer is free to be read */
        `$INSTANCE_NAME`_slRdBufSize = ((uint8) size);

        while(0u != timeoutMs)  /* Wait till response is read */
        {
            /* Check if host complete read */
            if(`$INSTANCE_NAME`_slRdBufIndex == ((uint8) size))
            {
                `$INSTANCE_NAME`_slRdBufSize  = 0u;
                `$INSTANCE_NAME`_slRdBufIndex = 0u;

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(`$INSTANCE_NAME`_WAIT_1_MS);
            timeoutMs--;
        }
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Receives the command from the Host.
*  All bytes are received by the I2C ISR and stored in internal I2C buffer. The
*  function checks status with timeout to detemine the end of transfer and
*  then copy data to bootloader buffer.
*  After exist this function the I2C ISR is able to receive more data.
*
* Parameters:
*  pData:    pointer to data buffer to store command.
*  size:     maximum number of bytes which could to be passed back.
*  count:    actual size of data was received.
*  timeOut:  timeout value in tries of 10uS.
*
* Return:
*  The status of receive operation.
*
* Global variables:
*  `$INSTANCE_NAME`_slWriteBuf - The global variable used to store a
*                                received command.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
         `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`
{
    cystatus status;
    uint16 timeoutMs;
    uint8 byteCount;

    status = CYRET_BAD_PARAM;

    if((NULL != pData) && (size > 0u))
    {
        status = CYRET_TIMEOUT;
        timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS checks to 1mS checks */

        while(0u != timeoutMs)  /* Wait for command from host */
        {
            /* Check if host completes write */
            if(0u != (`$INSTANCE_NAME`_slStatus & `$INSTANCE_NAME`_SSTAT_WR_CMPLT))
            {
                /* Define how many bytes host has been written */
                byteCount = `$INSTANCE_NAME`_slWrBufIndex;
                *count = (uint16) byteCount;

                /* Copy command to pData buffer */
                (void) memcpy((void *) pData, (void *) `$INSTANCE_NAME`_slWriteBuf,
                              `$INSTANCE_NAME`_MIN_UNT16(byteCount, size));

                /* Clear I2C write buffer and status */
                `$INSTANCE_NAME`_slStatus     = 0u;
                `$INSTANCE_NAME`_slWrBufIndex = 0u;

                status = CYRET_SUCCESS;
                break;
            }

            CyDelay(`$INSTANCE_NAME`_WAIT_1_MS);
            timeoutMs--;
        }
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BOOTLOADER_INTERFACE_ENABLED) */


/* [] END OF FILE */
