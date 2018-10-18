/*******************************************************************************
  Peripheral Access Controller (PAC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_${PAC_INSTANCE_NAME?lower_case}.c

  Summary
    Source for PAC peripheral library interface Implementation.

  Description
    This file defines the interface to the PAC peripheral library. This
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

#include "plib_${PAC_INSTANCE_NAME?lower_case}.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

<#if PAC_INTERRRUPT_MODE = true>
PAC_CALLBACK_OBJ ${PAC_INSTANCE_NAME?lower_case}CallbackObject;
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: ${PAC_INSTANCE_NAME} Interface Implementations
// *****************************************************************************
// *****************************************************************************

void ${PAC_INSTANCE_NAME}_Initialize( void )
{
<#if PAC_INTERRRUPT_MODE == true>
    /* Enable PAC interrupt */
    ${PAC_INSTANCE_NAME}_REGS->PAC_INTENSET = PAC_INTENSET_ERR_Msk;

</#if>
<#if PAC_ERROR_EVENT == true>
    /* Enable PAC Error Event Output */
    ${PAC_INSTANCE_NAME}_REGS->PAC_EVCTRL |= PAC_EVCTRL_ERREO_Msk;
</#if>
}

void ${PAC_INSTANCE_NAME}_PeripheralProtectSetup( PAC_PERIPHERAL peripheral, PAC_PROTECTION operation )
{
    /* Set Peripheral Access Control */
    ${PAC_INSTANCE_NAME}_REGS->PAC_WRCTRL |= PAC_WRCTRL_PERID(peripheral) | PAC_WRCTRL_KEY(operation);
}

<#if PAC_INTERRRUPT_MODE = true>
void ${PAC_INSTANCE_NAME}_CallbackRegister( PAC_CALLBACK callback, uintptr_t context )
{
    ${PAC_INSTANCE_NAME?lower_case}CallbackObject.callback = callback;

    ${PAC_INSTANCE_NAME?lower_case}CallbackObject.context = context;
}

void ${PAC_INSTANCE_NAME}_InterruptHandler( void )
{
    if (${PAC_INSTANCE_NAME?lower_case}CallbackObject.callback != NULL)
    {
        ${PAC_INSTANCE_NAME?lower_case}CallbackObject.callback(${PAC_INSTANCE_NAME?lower_case}CallbackObject.context);
    }
}
</#if>
