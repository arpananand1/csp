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

/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>
#include "definitions.h"                // SYS function prototypes

#define AFEC_VREF               (3.3f)
#define DAC_COUNT_INCREMENT     (124U)  // equivalent to 0.1V 
#define DAC_COUNT_MAX           (4095U)

uint16_t adc_count;
float input_voltage;
/* Initial value of dac count which is midpoint = 1.65 V*/
uint16_t dac_count = 0x800;   


void switch_handler( PIO_PIN pin, uintptr_t context )
{
    /* Write next data sample */
    dac_count = dac_count + DAC_COUNT_INCREMENT;
    
    if (dac_count > DAC_COUNT_MAX)
            dac_count=0;    
    
    DACC_DataWrite(DACC_CHANNEL_0, dac_count);
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
    
    PIO_PinInterruptCallbackRegister(PIO_PIN_PA11, &switch_handler, (uintptr_t) NULL );
    PIO_PinInterruptEnable(SWITCH_PIN);
    
    printf("\r\n\n\n");
    printf("**************** AFEC Polled Mode ******************\r\n");
    printf("Press switch to change the DAC output. \r\n");
    
    SYSTICK_TimerStart();

    DACC_DataWrite(DACC_CHANNEL_0, dac_count);
        
    while (1)
    {
        /* Start ADC conversion */
        AFEC1_ConversionStart();

        /* Wait till ADC conversion result is available */
        while(!AFEC1_ChannelResultIsReady(AFEC_CH0))
        {

        };

        /* Read the ADC result */
        adc_count = AFEC1_ChannelResultGet(AFEC_CH0);
        input_voltage = (float)adc_count * AFEC_VREF / 4095U;

        printf("ADC Count = 0x%03x, ADC Input Voltage = %0.2f V \r",adc_count, input_voltage);    
        
        SYSTICK_DelayMs(500);
    }
    
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/


