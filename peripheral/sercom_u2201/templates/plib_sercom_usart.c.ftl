/*******************************************************************************
  SERCOM Universal Synchronous/Asynchrnous Receiver/Transmitter PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_sercom${SERCOM_INDEX}_usart.c

  Summary
    USART peripheral library interface.

  Description
    This file defines the interface to the USART peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc. All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).
You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "plib_sercom${SERCOM_INDEX}_usart.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/* Macros to be added to the header file in the packs */
/* 5 Bits character size frame for data transfer */
#define SERCOM_USART_CTRLB_CHSIZE_5BITS                                 (0x5u)

/* 6 Bits character size frame for data transfer */
#define SERCOM_USART_CTRLB_CHSIZE_6BITS                                 (0x6u)

/* 7 Bits character size frame for data transfer */
#define SERCOM_USART_CTRLB_CHSIZE_7BITS                                 (0x7u)

/* 8 Bits character size frame for data transfer */
#define SERCOM_USART_CTRLB_CHSIZE_8BITS                                 (0x0u)

/* 9 Bits character size frame for data transfer */
#define SERCOM_USART_CTRLB_CHSIZE_9BITS                                 (0x1u)

/* 1 Stop Bit mode frame for data transfer */
#define SERCOM_USART_CTRLB_SBMODE_1BIT                                  (0x0u)

/* 2 Bits Stop mode frame for data transfer */
#define SERCOM_USART_CTRLB_SBMODE_2BITS                                 (0x1u)

/* USART Frame without Parity */
#define SERCOM_USART_FRAME_PARITY_NONE                                  (0x2u)

/* USART Frame with Odd Parity */
#define SERCOM_USART_FRAME_PARITY_ODD                                   (0x1u)

/* USART Frame with Even Parity */
#define SERCOM_USART_FRAME_PARITY_EVEN                                  (0x0u)

/* USART External Clock Mode */
#define SERCOM_USART_EXT_CLK                                            (0x0u)

/* USART Internal Clock Mode */
#define SERCOM_USART_INT_CLK                                            (0x1u)

/* USART Even Parity */
#define SERCOM_USART_CTRLB_PMODE_EVEN                                   (0x0u)

/* USART Odd Parity */
#define SERCOM_USART_CTRLB_PMODE_ODD                                    (0x1u)

/* SERCOM PAD 0 RXPO */
#define SERCOM_PAD0_RXPO                                                (0x0u)

/* SERCOM PAD 1 RXPO */
#define SERCOM_PAD1_RXPO                                                (0x1u)

/* SERCOM PAD 2 RXPO */
#define SERCOM_PAD2_RXPO                                                (0x2u)

/* SERCOM PAD 3 RXPO */
#define SERCOM_PAD3_RXPO                                                (0x3u)

/* SERCOM PAD 0 TXPO */
#define SERCOM_PAD0_TXPO                                                (0x0u)

/* SERCOM PAD 1 TXPO */
#define SERCOM_PAD2_TXPO                                                (0x1u)

/* SERCOM ERROR MASK */
#define SERCOM_USART_ERROR_Msk                                          (0x3u)

/* SERCOM BAUD MAX RANGE */
#define SERCOM_BAUD_RATE_MAX_RANGE                                (0xFFFFFFFF)

/* Baud rate arithmetic part max value */
#define SERCOM_BAUD_RATE_ARITHMETIC_PART_MAX                         (0x1FFFu)

/* Baud rate fractional part max value */
#define SERCOM_BAUD_RATE_FRACTIONAL_PART_MAX                            (0x7u)

/* Calculation for arithmetic part of baud value */
#define BAUD_VAL                         (4000000 / (16 * ${USART_BAUD_RATE}))

/* Calculation for fractional part of baud value */
#define FP_VAL            ((4000000 / ${USART_BAUD_RATE} - 16 * BAUD_VAL) / 2)

<#if USART_SERIAL_SETUP_ENABLE = true>
USART_SERIAL_SETUP sercom${SERCOM_INDEX}usartSerialConf;
</#if>

SERCOM_USART_OBJECT sercom${SERCOM_INDEX}usartObj;

<#if USART_INTERRUPT_MODE = true>
// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_ISR_ERR_Handler( void )

  Summary:
    Handles error interrupt.

  Description:
    This function reads the errors occured during transfer and after clearing
    the errors in the hardware invokes the callback.

  Remarks:
    None.
*/

void static SERCOM${SERCOM_INDEX}_USART_ISR_ERR_Handler( void )
{
    USART_ERROR errorStatus = USART_ERROR_NONE;
    uint8_t  u8dummyData = 0;

    errorStatus = (SERCOM${SERCOM_INDEX}_REGS->USART.STATUS.w &
                  (SERCOM_USART_STATUS_PERR_Msk |
                  SERCOM_USART_STATUS_FERR_Msk |
                  SERCOM_USART_STATUS_BUFOVF_Msk));

    if(errorStatus != USART_ERROR_NONE)
    {
        /* Clear all error flags */
        SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w = SERCOM_USART_INTFLAG_ERROR_Msk;

        /* Clear error statuses */
        SERCOM${SERCOM_INDEX}_REGS->USART.STATUS.w = SERCOM_USART_STATUS_Msk;

        /* Flush existing error bytes from the RX FIFO */
        while((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk)
        {
            u8dummyData = SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w;
        }

        /* Ignore the warning */
        (void)u8dummyData;

        if( sercom${SERCOM_INDEX}usartObj.rxCallback != NULL )
        {
            sercom${SERCOM_INDEX}usartObj.rxCallback(sercom${SERCOM_INDEX}usartObj.rxContext);
        }
    }
}

<#if USART_RX_ENABLE = true>
// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_ISR_RX_Handler( void )

  Summary:
    Handles USART receive interrupt.

  Description:
    This function reads the data once the receive interrupt occurs.
    Once the transaction is completed it invokes the callback.

  Remarks:
    None.
*/

void static SERCOM${SERCOM_INDEX}_USART_ISR_RX_Handler( void )
{
    if(sercom${SERCOM_INDEX}usartObj.rxBusyStatus == true)
    {
        if(sercom${SERCOM_INDEX}usartObj.rxSize >= sercom${SERCOM_INDEX}usartObj.rxProcessedSize)
        {
            if(sercom${SERCOM_INDEX}usartObj.rxSize == sercom${SERCOM_INDEX}usartObj.rxProcessedSize)
            {
                sercom${SERCOM_INDEX}usartObj.rxBusyStatus = false;
                sercom${SERCOM_INDEX}usartObj.rxSize = 0;
                SERCOM${SERCOM_INDEX}_REGS->USART.INTENCLR.w = SERCOM_USART_INTENCLR_RXC_Msk;

                if(sercom${SERCOM_INDEX}usartObj.rxCallback != NULL)
                {
                    sercom${SERCOM_INDEX}usartObj.rxCallback(sercom${SERCOM_INDEX}usartObj.rxContext);
                }
            }
            else
            {
                SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w = SERCOM_USART_INTFLAG_RXC_Msk;

                sercom${SERCOM_INDEX}usartObj.rxBuffer[sercom${SERCOM_INDEX}usartObj.rxProcessedSize++] = SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w;
            }
        }
    }
}
</#if>

<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_ISR_TX_Handler( void )

  Summary:
    Handles USART Transmit interrupt .

  Description:
    This function transmits the data once the transmit interrupt occurs.
    Once the transaction is completed it invokes the callback.

  Remarks:
    None.
*/

void static SERCOM${SERCOM_INDEX}_USART_ISR_TX_Handler( void )
{
    if(sercom${SERCOM_INDEX}usartObj.txBusyStatus == true)
    {
        if(sercom${SERCOM_INDEX}usartObj.txSize >= sercom${SERCOM_INDEX}usartObj.txProcessedSize)
        {
            if(sercom${SERCOM_INDEX}usartObj.txSize == sercom${SERCOM_INDEX}usartObj.txProcessedSize)
            {
                sercom${SERCOM_INDEX}usartObj.txBusyStatus = false;
                sercom${SERCOM_INDEX}usartObj.txSize = 0;
                SERCOM${SERCOM_INDEX}_REGS->USART.INTENCLR.w = SERCOM_USART_INTENCLR_DRE_Msk;

                if(sercom${SERCOM_INDEX}usartObj.txCallback != NULL)
                {
                    sercom${SERCOM_INDEX}usartObj.txCallback(sercom${SERCOM_INDEX}usartObj.txContext);
                }
            }
            else
            {
                SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w = SERCOM_USART_INTFLAG_DRE_Msk;

                SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w = sercom${SERCOM_INDEX}usartObj.txBuffer[sercom${SERCOM_INDEX}usartObj.txProcessedSize++];
            }
        }
    }
}
</#if>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
this interface.
*/

// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_Initialize( void )

  Summary:
    Initializes given instance of the USART peripheral.

  Description:
    This function initializes the given instance of the USART peripheral as
    configured by the user from within the MHC.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

void SERCOM${SERCOM_INDEX}_USART_Initialize( void )
{
    /* Disable the USART before configurations */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w &= ~SERCOM_USART_CTRLA_ENABLE_Msk;

    while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for sync */
    }

    /* Configures USART Clock Mode */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_MODE(${(SERCOM_MODE == "USART_EXT")?then('SERCOM_USART_EXT_CLK' , 'SERCOM_USART_INT_CLK')});

    /*
     * Configures TXPO and RXPO
     * Configures Data Order
     * Configures Standby Mode
     * Configures sampling rate
     * Configures IBON
     */
    <@compress single_line=true>SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_RXPO(${USART_RXPO}_RXPO) |
                                                                             SERCOM_USART_CTRLA_TXPO(${USART_TXPO}_TXPO) |
                                                                             SERCOM_USART_CTRLA_DORD_Msk |
                                                                             SERCOM_USART_CTRLA_SAMPR(1) |
                                                                             SERCOM_USART_CTRLA_IBON_Msk
                                                                             ${USART_RUNSTDBY?then('| SERCOM_USART_CTRLA_RUNSTDBY_Msk', '')};</@compress>

<#if USART_PARITY_MODE = "ODD">
    /* Configure Parity */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(1);
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLB.w |= SERCOM_USART_CTRLB_PMODE_Msk;
</#if>
<#if USART_PARITY_MODE = "EVEN">
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(1);
</#if>
<#if USART_PARITY_MODE = "NONE">
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(0);
</#if>

<#if USART_STOP_BIT = "2BITS">
    /* Configure Stop bits */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLB.w |= SERCOM_USART_CTRLB_SBMODE_Msk;
</#if>

    /* Configure Baud Rate */
    SERCOM${SERCOM_INDEX}_REGS->USART.BAUD.w = SERCOM_USART_BAUD_BAUD_FRAC_MODE(BAUD_VAL) | SERCOM_USART_BAUD_FP(FP_VAL);

    /* Enable transmitter and receive enable RXEN TXEN */
    <@compress single_line=true>SERCOM${SERCOM_INDEX}_REGS->USART.CTRLB.w |= SERCOM_USART_CTRLB_CHSIZE(SERCOM_USART_CTRLB_CHSIZE_${USART_CHARSIZE_BITS})
                                                                             ${USART_RX_ENABLE?then('| SERCOM_USART_CTRLB_RXEN_Msk', '')}
                                                                             ${USART_TX_ENABLE?then('| SERCOM_USART_CTRLB_TXEN_Msk', '')};</@compress>

    while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk)
    {
        /* Wait for sync */
    }

    /* Enable the UART after the configurations */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_ENABLE_Msk;

    while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for sync */
    }

<#if USART_SERIAL_SETUP_ENABLE = true>
    sercom${SERCOM_INDEX}usartSerialConf.baud = ${USART_BAUD_RATE};
    sercom${SERCOM_INDEX}usartSerialConf.charSize = SERCOM_USART_CTRLB_CHSIZE_${USART_CHARSIZE_BITS};
<#if USART_PARITY_MODE = "EVEN" | USART_PARITY_MODE = "ODD">
    sercom${SERCOM_INDEX}usartSerialConf.parityEnable = true;
    sercom${SERCOM_INDEX}usartSerialConf.parity = SERCOM_USART_CTRLB_PMODE_${USART_PARITY_MODE};
<#else>
    sercom${SERCOM_INDEX}usartSerialConf.parityEnable = false;
</#if>
    sercom${SERCOM_INDEX}usartSerialConf.stopBits = SERCOM_USART_CTRLB_SBMODE_${USART_STOP_BIT};
</#if>

<#if USART_INTERRUPT_MODE = true>
    /* Initialize instance object */
    sercom${SERCOM_INDEX}usartObj.rxBuffer = NULL;
    sercom${SERCOM_INDEX}usartObj.rxSize = 0;
    sercom${SERCOM_INDEX}usartObj.rxProcessedSize = 0;
    sercom${SERCOM_INDEX}usartObj.rxBusyStatus = false;
    sercom${SERCOM_INDEX}usartObj.rxCallback = NULL;
    sercom${SERCOM_INDEX}usartObj.txBuffer = NULL;
    sercom${SERCOM_INDEX}usartObj.txSize = 0;
    sercom${SERCOM_INDEX}usartObj.txProcessedSize = 0;
    sercom${SERCOM_INDEX}usartObj.txBusyStatus = false;
    sercom${SERCOM_INDEX}usartObj.txCallback = NULL;
</#if>
}

<#if USART_SERIAL_SETUP_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_SerialSetup( uint32_t clkFrequency,
                                              USART_SERIAL_SETUP * serialSetup )

  Summary:
    Sets up serial configurations for usart peripheral.

  Description:
    This function sets all the serial configurations of the peripheral.
    It provides run-time interface to configure the baud, parity,
    stop bits and data character size parameters of the serial connection

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_SerialSetup( uint32_t clkFrequency, USART_SERIAL_SETUP * serialSetup )
{
    bool bretVal          = false;
    uint32_t u32baudVal   = 0;
    uint32_t u32fpVal     = 0;
    uint32_t u32confVal   = 0;

    u32baudVal = (clkFrequency / (16 * serialSetup->baud));
    u32fpVal = ((clkFrequency / serialSetup->baud - 16 * u32baudVal) / 2);

    /* Disable the UART before configurations */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w &= ~SERCOM_USART_CTRLA_ENABLE_Msk;

    while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for sync */
    }

    if((serialSetup != NULL) && (serialSetup->baud < SERCOM_BAUD_RATE_MAX_RANGE))
    {
        /* Configure Baud Rate */
        SERCOM${SERCOM_INDEX}_REGS->USART.BAUD.w = SERCOM_USART_BAUD_BAUD_FRAC_MODE(u32baudVal) | SERCOM_USART_BAUD_FP(u32fpVal);

        /* Configure Character Size */
        u32confVal |= SERCOM_USART_CTRLB_CHSIZE(serialSetup->charSize);

        /* Configure Stop bits */
        if(serialSetup->stopBits == SERCOM_USART_CTRLB_SBMODE_2BITS)
        {
            u32confVal |= SERCOM_USART_CTRLB_SBMODE_2BITS;
        }
        else
        {
            u32confVal |= SERCOM_USART_CTRLB_SBMODE_1BIT;
        }

        /* Configure Parity Options */
        if((serialSetup->parityEnable == true) && (serialSetup->parity == SERCOM_USART_CTRLB_PMODE_ODD))
        {
            SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(1);

            u32confVal |= SERCOM_USART_CTRLB_PMODE_ODD;
        }
        else if((serialSetup->parityEnable == true) && (serialSetup->parity == SERCOM_USART_CTRLB_PMODE_EVEN))
        {
            SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(1);

            u32confVal |= SERCOM_USART_CTRLB_PMODE_EVEN;
        }
        else
        {
            /* If No Parity Selected */
            SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_FORM(0);
        }

        /* Writing the configurations to register */
        SERCOM${SERCOM_INDEX}_REGS->USART.CTRLB.w |= u32confVal;

        while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk)
        {
            /* Wait for sync */
        }

        bretVal = true;
    }

    /* Enable the UART after the configurations */
    SERCOM${SERCOM_INDEX}_REGS->USART.CTRLA.w |= SERCOM_USART_CTRLA_ENABLE_Msk;

    while((SERCOM${SERCOM_INDEX}_REGS->USART.SYNCBUSY.w & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for sync */
    }

    return bretVal;
}
</#if>

<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_Write( void *buffer, const size_t size )

  Summary:
    Submits a write buffer to the given USART peripheral to transfer.

  Description
    This function submits a write buffer to the USART peripheral to transfer.
    The behavior of this function call will vary based on the mode
    selected within MHC.

    If the peripheral is configured for the interrupt mode, this function call
    is always non-blocking. Call to this function submits the buffer and the
    size to the peripheral library and returns immediately. User can check the
    transfer status either through callback mechanism or by calling
    USARTx_TransferStatusGet.

    If the peripheral is configured for the non-interrupt mode, this
    function call returns only after requested size is transferred.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_Write( void *buffer, const size_t size )
{
<#if USART_INTERRUPT_MODE = false>
    uint32_t u32Length    = size;
    uint32_t u32TxPos     = 0;
</#if>
    uint8_t *pu8Data     = (uint8_t*)buffer;
    bool bReturnVal      = false;

    if(pu8Data != NULL)
    {
<#if USART_INTERRUPT_MODE = false>
        /* Blocks while buffer is being transferred */
        while (u32Length--)
        {
            while ((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_DRE_Msk) != SERCOM_USART_INTFLAG_DRE_Msk)
            {
                /* Check if USART is ready for new data */
            }

            /* Write data to USART module */
            SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w = pu8Data[u32TxPos++];
        }

        bReturnVal = true;
<#else>
        if(sercom${SERCOM_INDEX}usartObj.txBusyStatus == false)
        {
            sercom${SERCOM_INDEX}usartObj.txBuffer = pu8Data;
            sercom${SERCOM_INDEX}usartObj.txSize = size;
            sercom${SERCOM_INDEX}usartObj.txProcessedSize = 0;
            sercom${SERCOM_INDEX}usartObj.txBusyStatus = true;

            if(size == 0)
            {
                bReturnVal = true;
            }
            else
            {
                /* Initiate the transfer by sending first byte */
                if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_DRE_Msk) == SERCOM_USART_INTFLAG_DRE_Msk)
                {
                    SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w = sercom${SERCOM_INDEX}usartObj.txBuffer[sercom${SERCOM_INDEX}usartObj.txProcessedSize++];
                }

                bReturnVal = true;

                SERCOM${SERCOM_INDEX}_REGS->USART.INTENSET.w = SERCOM_USART_INTFLAG_DRE_Msk ;
            }
        }
</#if>
    }

    return bReturnVal;
}
</#if>

<#if USART_RX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_Read( void *buffer, const size_t size )

  Summary:
    Submits a read buffer to the given USART peripheral to process.

  Description:
    This function submits a read buffer to the USART peripheral to process.
    The behavior of this function call will vary based on the mode
    selected within MHC.

    If the peripheral is configured for the interrupt mode, this function call
    is always non-blocking. Call to this function submits the buffer and the
    size to the peripheral library and returns immediately. User can check the
    transfer status either through callback mechanism or by calling
    USARTx_TransferStatusGet.

    If the peripheral is configured for the non-interrupt mode, this
    function call returns only after requested size is processed.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_Read( void *buffer, const size_t size )
{
<#if USART_INTERRUPT_MODE = false>
    uint32_t u32Length    = size;
    uint32_t u32RxPos     = 0;
</#if>
    bool bReturnVal       = false;
    uint8_t *pu8Data      = (uint8_t*)buffer;
    uint8_t u8dummyData   = 0;

    if(pu8Data != NULL)
    {
<#if USART_INTERRUPT_MODE = false>
        /* Checks for error before receiving */
        if(SERCOM${SERCOM_INDEX}_USART_ErrorGet() != USART_ERROR_NONE)
        {
            /* Clear all error flags */
            SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w = SERCOM_USART_INTFLAG_ERROR_Msk;

            /* Clear error statuses */
            SERCOM${SERCOM_INDEX}_REGS->USART.STATUS.w = SERCOM_USART_STATUS_Msk;

            /* Flush existing error bytes from the RX FIFO */
            while((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk)
            {
                u8dummyData = SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w;
            }

            /* Ignore the warning */
            (void)u8dummyData;
        }

        while(u32Length--)
        {
            while((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) != SERCOM_USART_INTFLAG_RXC_Msk)
            {
                /* Check if USART has new data */
            }

            /* Read data from USART module */
            *pu8Data++ = SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w;
            u32RxPos++;

            if(SERCOM${SERCOM_INDEX}_USART_ErrorGet() != USART_ERROR_NONE)
            {
                break;
            }
            else
            {
                bReturnVal = true;
            }
        }
<#else>
        if(sercom${SERCOM_INDEX}usartObj.rxBusyStatus == false)
        {
            /* Checks for error before receiving */
            if(SERCOM${SERCOM_INDEX}_USART_ErrorGet() != USART_ERROR_NONE)
            {
                /* Clear all error flags */
                SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w = SERCOM_USART_INTFLAG_ERROR_Msk;

                /* Clear error statuses */
                SERCOM${SERCOM_INDEX}_REGS->USART.STATUS.w = SERCOM_USART_STATUS_Msk;

                /* Flush existing error bytes from the RX FIFO */
                while((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk)
                {
                    u8dummyData = SERCOM${SERCOM_INDEX}_REGS->USART.DATA.w;
                }

                /* Ignore the warning */
                (void)u8dummyData;
            }

            sercom${SERCOM_INDEX}usartObj.rxBuffer = pu8Data;
            sercom${SERCOM_INDEX}usartObj.rxSize = size;
            sercom${SERCOM_INDEX}usartObj.rxProcessedSize = 0;
            sercom${SERCOM_INDEX}usartObj.rxBusyStatus = true;
            bReturnVal = true;

            /* Enable error interrupts */
            SERCOM${SERCOM_INDEX}_REGS->USART.INTENSET.w |= SERCOM_USART_INTENSET_ERROR_Msk;

            /* Enable Receive Complete interrupt */
            SERCOM${SERCOM_INDEX}_REGS->USART.INTENSET.w = SERCOM_USART_INTENSET_RXC_Msk;
        }
</#if>
    }

    return bReturnVal;
}
</#if>

<#if USART_INTERRUPT_MODE = true>
<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_WriteIsBusy( void )

  Summary:
    Returns the write request status associated with the given USART peripheral
    instance.

  Description:
    This function returns the write request status associated with the given
    USART peripheral instance.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_WriteIsBusy ( void )
{
    return sercom${SERCOM_INDEX}usartObj.txBusyStatus;
}
</#if>

<#if USART_RX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_ReadIsBusy( void )

  Summary:
    Returns the read request status associated with the given USART peripheral
    instance.

  Description:
    This function returns the read request status associated with the given
    USART peripheral instance.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_ReadIsBusy ( void )
{
    return sercom${SERCOM_INDEX}usartObj.rxBusyStatus;
}
</#if>
</#if>

<#if USART_INTERRUPT_MODE = true>
<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    size_t SERCOM${SERCOM_INDEX}_USART_WriteCountGet( void )

  Summary:
    Gets the count of number of bytes processed for a given USART write
    operation.

  Description:
    This function gets the count of number of bytes processed for a given
    USART write operation.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

size_t SERCOM${SERCOM_INDEX}_USART_WriteCountGet( void )
{
    return sercom${SERCOM_INDEX}usartObj.txProcessedSize;
}
</#if>

<#if USART_RX_ENABLE = true>
// *****************************************************************************
/* Function:
    size_t SERCOM${SERCOM_INDEX}_USART_ReadCountGet( void )

  Summary:
    Gets the count of number of bytes processed for a given USART read
    operation.

  Description:
    This function gets the count of number of bytes processed for a given
    USART read operation.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

size_t SERCOM${SERCOM_INDEX}_USART_ReadCountGet( void )
{
    return sercom${SERCOM_INDEX}usartObj.rxProcessedSize;
}
</#if>
</#if>

<#if USART_INTERRUPT_MODE = false>
<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_TransmitterIsReady( void )

  Summary:
    Returns the hardware status of the USART Transmitter.

  Description:
    This function returns the hardware status associated with the Transmit
    hardware FIFO of the given USART peripheral instance.

    When Transmitter is ready, user can submit data to transmit.

    This function is available only in non-interrupt mode of operation. And can
    be used to achieve non-blocking behavior of write request. User has to check
    the Transmit ready status by calling this function and can submit write
    request for the buffer size of 1.

  Remarks:
   Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_TransmitterIsReady ( void )
{
    bool bstatus = false;

    if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_DRE_Msk) == SERCOM_USART_INTFLAG_DRE_Msk)
    {
        bstatus = true;
    }

    return bstatus;
}
</#if>
<#if USART_RX_ENABLE = true>
// *****************************************************************************
/* Function:
    bool SERCOM${SERCOM_INDEX}_USART_ReceiverIsReady( void )

  Summary:
    Returns the hardware status of the USART Receiver.

  Description:
    This function returns the hardware status associated with the Receive
    hardware FIFO of the given USART peripheral instance.

    When Receiver is ready, user can read the available data.

    This function is available only in non-interrupt mode of operation. And can
    be used to achieve non-blocking behavior of read request. User has to check
    the Receiver ready status by calling this function and can submit a read
    request for the buffer size of 1.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

bool SERCOM${SERCOM_INDEX}_USART_ReceiverIsReady ( void )
{
    bool bstatus = false;

    if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk)
    {
        bstatus = true;
    }

    return bstatus;
}
</#if>
</#if>

// *****************************************************************************
/* Function:
    USART_ERROR SERCOM${SERCOM_INDEX}_USART_ErrorGet( void )

  Summary:
    Gets the error of the given USART peripheral instance.

  Description:
    This function returns the errors associated with the given USART peripheral
    instance. The call to this function also clears all the associated errors.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

USART_ERROR SERCOM${SERCOM_INDEX}_USART_ErrorGet( void )
{
    uint32_t u32status = 0;

    u32status = SERCOM${SERCOM_INDEX}_REGS->USART.STATUS.w & SERCOM_USART_STATUS_Msk;

    return (USART_ERROR) u32status;
}

<#if USART_INTERRUPT_MODE = true>
// *****************************************************************************
// *****************************************************************************
// Section: Callback Interface
// *****************************************************************************
// *****************************************************************************

<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_WriteCallbackRegister
                          ( SERCOM_USART_CALLBACK callback, uintptr_t context )

  Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given USART's write events occur.

  Description:
    This function sets the pointer to a client function to be called "back"
    when the given USART's write events occur. It also passes a context value
    (usually a pointer to a context structure) that is passed into the
    function when it is called.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

void SERCOM${SERCOM_INDEX}_USART_WriteCallbackRegister( SERCOM_USART_CALLBACK callback, uintptr_t context )
{
    sercom${SERCOM_INDEX}usartObj.txCallback = callback;

    sercom${SERCOM_INDEX}usartObj.txContext = context;
}
</#if>
<#if USART_TX_ENABLE = true>
// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_ReadCallbackRegister
                          ( SERCOM_USART_CALLBACK callback, uintptr_t context )

  Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given USART's read events occur.

  Description:
    This function sets the pointer to a client function to be called "back"
    when the given USART's read events occur. It also passes a context value
    (usually a pointer to a context structure) that is passed into the
    function when it is called.

    This function is available only in interrupt or non-blocking mode of
    operation.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

void SERCOM${SERCOM_INDEX}_USART_ReadCallbackRegister( SERCOM_USART_CALLBACK callback, uintptr_t context )
{
    sercom${SERCOM_INDEX}usartObj.rxCallback = callback;

    sercom${SERCOM_INDEX}usartObj.rxContext = context;
}
</#if>
</#if>

<#if USART_INTERRUPT_MODE = true>
// *****************************************************************************
/* Function:
    void SERCOM${SERCOM_INDEX}_USART_InterruptHandler( void )

  Summary:
    Sercom Handler, handles all sercom interrupt.

  Description:
    This function handles all the operations post interrupt for
    all sercom USART interrupts.

  Remarks:
    Refer plib_sercom${SERCOM_INDEX}_usart.h file for more information.
*/

void SERCOM${SERCOM_INDEX}_USART_InterruptHandler( void )
{
    /* Checks for data register empty flag */
    if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_DRE_Msk) == SERCOM_USART_INTFLAG_DRE_Msk)
    {
        SERCOM${SERCOM_INDEX}_USART_ISR_TX_Handler();
    }

    /* Checks for receive complete empty flag */
    if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk)
    {
        SERCOM${SERCOM_INDEX}_USART_ISR_RX_Handler();
    }

    /* Checks for error flag */
    if((SERCOM${SERCOM_INDEX}_REGS->USART.INTFLAG.w & SERCOM_USART_INTFLAG_ERROR_Msk) == SERCOM_USART_INTFLAG_ERROR_Msk)
    {
        SERCOM${SERCOM_INDEX}_USART_ISR_ERR_Handler();
    }
}
</#if>
