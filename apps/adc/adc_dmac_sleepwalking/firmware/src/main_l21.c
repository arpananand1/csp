/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>
#include <string.h>
#include "definitions.h"                // SYS function prototypes

#define DMAC_TRANSFER_BYTECOUNT 32
#define RTC_COMPARE_VAL 100

#define LED_OFF     LED_Set
#define LED_ON      LED_Clear

volatile bool dma_ch0Done = false;
uint32_t myAppObj = 0;
uint8_t adc_result_array[DMAC_TRANSFER_BYTECOUNT];

void DmacCh0Cb(DMAC_TRANSFER_EVENT returned_evnt, uintptr_t MyDmacContext)
{
    if (DMAC_TRANSFER_EVENT_COMPLETE == returned_evnt)
    {
        dma_ch0Done = true;
    }
    else if (DMAC_TRANSFER_EVENT_ERROR == returned_evnt)
    {
        LED_ON();
        printf("DMAC Error \r\n");
        while(1);
    }
 }

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    LED_OFF();
    
    ADC_Enable();
    
    RTC_Timer32Start();
    RTC_Timer32CompareSet(RTC_COMPARE_VAL);
    
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, DmacCh0Cb, (uintptr_t)&myAppObj);
    DMAC_ChannelTransfer(DMAC_CHANNEL_0, (const void *)&ADC_REGS->ADC_RESULT, (const void *)adc_result_array, DMAC_TRANSFER_BYTECOUNT);
 
    printf("\n\r---------------------------------------------------------");
    printf("\n\r                    ADC DMA Sleepwalking Demo                 ");
    printf("\n\r---------------------------------------------------------\n\r");    
    printf("\r\n\r\n Wake CPU after 16 samples are taken\r\n");
    
    while ( true )
    {
        PM_StandbyModeEnter();
        if(dma_ch0Done == true)
        {
            printf("\r\nTransferred 16 results to array in SRAM\r\n");
            dma_ch0Done = false;
            /* Configure the next transfer */
            DMAC_ChannelTransfer(DMAC_CHANNEL_0, (const void *)&ADC_REGS->ADC_RESULT, (const void *)adc_result_array, DMAC_TRANSFER_BYTECOUNT);
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/
