/*******************************************************************************
  Analog-to-Digital Converter(ADC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_adc.c

  Summary
    ADC PLIB Implementation File.

  Description
    This file defines the interface to the ADC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
/* This section lists the other files that are included in this file.
*/

#include "plib_adc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************
ADC_CALLBACK_OBJ ADC_CallbackObject;

#define ADC_LINEARITY0_POS  (27)
#define ADC_LINEARITY0_Msk   ((0x1F << ADC_LINEARITY0_POS))

#define ADC_LINEARITY1_POS  (0)
#define ADC_LINEARITY1_Msk   ((0x7 << ADC_LINEARITY1_POS))

#define ADC_BIASCAL_POS  (3)
#define ADC_BIASCAL_Msk   ((0x7 << ADC_BIASCAL_POS))

// *****************************************************************************
// *****************************************************************************
// Section: ADC Implementation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Initialize ADC module */
void ADC_Initialize( void )
{
    /* Reset ADC */
    ADC_REGS->ADC_CTRLA = ADC_CTRLA_SWRST_Msk;

    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }

    uint32_t adc_linearity0 = (((*(uint64_t*)OTP4_ADDR) & ADC_LINEARITY0_Msk) >> ADC_LINEARITY0_POS);
    uint32_t adc_linearity1 = (((*(uint64_t*)OTP4_ADDR) & ADC_LINEARITY0_Msk) >> ADC_LINEARITY0_POS);

    /* Write linearity calibration and bias calibration */
    ADC_REGS->ADC_CALIB = (uint32_t)(ADC_CALIB_LINEARITY_CAL(adc_linearity0 | (adc_linearity1 << 5))) \
        | ADC_CALIB_BIAS_CAL((((*(uint64_t*)OTP4_ADDR + 1) & ADC_BIASCAL_Msk) >> ADC_BIASCAL_POS));

    /* Sampling length */
    ADC_REGS->ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(3U);

    /* reference */
    ADC_REGS->ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC1;

    /* positive and negative input pins */
    ADC_REGS->ADC_INPUTCTRL = ADC_POSINPUT_PIN2 | ADC_NEGINPUT_GND \
        | ADC_INPUTCTRL_INPUTSCAN(0) | ADC_INPUTCTRL_INPUTOFFSET(0) | ADC_INPUTCTRL_GAIN_1X;

    /* Prescaler, Resolution & Operation Mode */
    ADC_REGS->ADC_CTRLB = ADC_CTRLB_PRESCALER_DIV128 | ADC_CTRLB_RESSEL_12BIT ;


    /* Window mode configurations */
    ADC_REGS->ADC_WINCTRL = ADC_WINCTRL_WINMODE_MODE2;
    /* Upper threshold for window mode  */
    ADC_REGS->ADC_WINUT = 1024;
    /* Lower threshold for window mode  */
    ADC_REGS->ADC_WINLT = 0;
    /* Clear all interrupt flags */
    ADC_REGS->ADC_INTFLAG = ADC_INTFLAG_Msk;
    /* Enable interrupts */
    ADC_REGS->ADC_INTENSET = ADC_INTENSET_WINMON_Msk;
    /* Events configuration  */
    ADC_REGS->ADC_EVCTRL = ADC_EVCTRL_STARTEI_Msk;

    ADC_REGS->ADC_CTRLA |= ADC_CTRLA_RUNSTDBY_Msk;
    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Enable ADC module */
void ADC_Enable( void )
{
    ADC_REGS->ADC_CTRLA |= ADC_CTRLA_ENABLE_Msk;
    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Disable ADC module */
void ADC_Disable( void )
{
    ADC_REGS->ADC_CTRLA &= ~ADC_CTRLA_ENABLE_Msk;
    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Configure channel input */
void ADC_ChannelSelect( ADC_POSINPUT positiveInput, ADC_NEGINPUT negativeInput )
{
    /* Configure pin scan mode and positive and negative input pins */
    ADC_REGS->ADC_INPUTCTRL = positiveInput | negativeInput;

    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Start the ADC conversion by SW */
void ADC_ConversionStart( void )
{
    /* Start conversion */
    ADC_REGS->ADC_SWTRIG |= ADC_SWTRIG_START_Msk;

    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Configure window comparison threshold values */
void ADC_ComparisonWindowSet(uint16_t low_threshold, uint16_t high_threshold)
{
    ADC_REGS->ADC_WINLT = low_threshold;
    ADC_REGS->ADC_WINUT = high_threshold;
    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}

void ADC_WindowModeSet(ADC_WINMODE mode)
{
    ADC_REGS->ADC_WINCTRL = mode << ADC_WINCTRL_WINMODE_Pos;
    while(ADC_REGS->ADC_STATUS & ADC_STATUS_SYNCBUSY_Msk)
    {
        /* Wait for Synchronization */
    }
}


/* Read the conversion result */
uint16_t ADC_ConversionResultGet( void )
{
    return (uint16_t)ADC_REGS->ADC_RESULT;
}

/* Register callback function */
void ADC_CallbackRegister( ADC_CALLBACK callback, uintptr_t context )
{
    ADC_CallbackObject.callback = callback;

    ADC_CallbackObject.context = context;
}


void ADC_InterruptHandler( void )
{
    volatile ADC_STATUS status;
    status = ADC_REGS->ADC_INTFLAG;
    /* Clear interrupt flag */
    ADC_REGS->ADC_INTFLAG =  ADC_INTENSET_WINMON_Msk;
    if (ADC_CallbackObject.callback != NULL)
    {
        ADC_CallbackObject.callback(status, ADC_CallbackObject.context);
    }
}

/* Check whether result is ready */
bool ADC_ConversionStatusGet( void )
{
    bool status;
    status =  (bool)((ADC_REGS->ADC_INTFLAG & ADC_INTFLAG_RESRDY_Msk) >> ADC_INTFLAG_RESRDY_Pos);
    if (status == true)
    {
        ADC_REGS->ADC_INTFLAG = ADC_INTFLAG_RESRDY_Msk;
    }
    return status;
}
