/*******************************************************************************
  SPI PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_spi3.h

  Summary:
    SPI3 PLIB Header File

  Description:
    This file has prototype of all the interfaces provided for particular
    SPI peripheral.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_SPI3_H
#define PLIB_SPI3_H

#include "device.h"
#include "plib_spi_common.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus

    extern "C" {

#endif



/****************************** SPI3 Interface *********************************/

void SPI3_Initialize ( void );

bool SPI3_WriteRead (void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize);

static inline bool SPI3_Write(void* pTransmitData, size_t txSize)
{
    return(SPI3_WriteRead(pTransmitData, txSize, NULL, 0));
}

static inline bool SPI3_Read(void* pReceiveData, size_t rxSize)
{
    return(SPI3_WriteRead(NULL, 0, pReceiveData, rxSize));
}

bool SPI3_TransferSetup (SPI_TRANSFER_SETUP *setup, uint32_t spiSourceClock);

bool SPI3_IsBusy(void);

SPI_ERROR SPI3_ErrorGet( void );

void SPI3_FaultCallbackRegister(const SPI_CALLBACK callback, uintptr_t context);

void SPI3_FAULT_Tasks (void);

void SPI3_RxCallbackRegister(const SPI_CALLBACK callback, uintptr_t context);

void SPI3_RX_Tasks (void);

void SPI3_TxCallbackRegister(const SPI_CALLBACK callback, uintptr_t context);

void SPI3_TX_Tasks (void);


/* Provide C++ Compatibility */
#ifdef __cplusplus

    }

#endif

#endif // PLIB_SPI3_H

/*******************************************************************************
 End of File
*/
