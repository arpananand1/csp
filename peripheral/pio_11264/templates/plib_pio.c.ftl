/*******************************************************************************
  SYS PORTS Static Functions for PORTS System Service

  Company:
    Microchip Technology Inc.

  File Name:
    plib_pio.c

  Summary:
    PIO function implementations for the PIO PLIB.

  Description:
    The PIO PLIB provides a simple interface to manage peripheral
    input-output controller.

*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#include "plib_pio.h"

<#macro PIO_INT_CALLBACK PIO_PORT PORT_NUM_INT_PINS PIO_INTERRUPT>
    <#if PIO_INTERRUPT == true>
		<#assign PORT_PINS = PORT_NUM_INT_PINS?number + 1>
		
        <#lt>/* port ${PIO_PORT} current number of callbacks */
        <#lt>uint8_t port${PIO_PORT}CurNumCb = 0;

        <#lt>/* port ${PIO_PORT} maximum number of callbacks */
        <#lt>uint8_t port${PIO_PORT}MaxNumCb = ${PORT_PINS};

        <#lt>/* port ${PIO_PORT} callback objects */
        <#lt>PIO_PIN_CALLBACK_OBJ port${PIO_PORT}PinCbObj[${PORT_PINS}];
    </#if>
</#macro>


<@PIO_INT_CALLBACK
    PIO_PORT = "A"
    PORT_NUM_INT_PINS = "${PORT_A_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_A_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "B"
    PORT_NUM_INT_PINS = "${PORT_B_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_B_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "C"
    PORT_NUM_INT_PINS = "${PORT_C_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_C_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "D"
    PORT_NUM_INT_PINS = "${PORT_D_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_D_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "E"
    PORT_NUM_INT_PINS = "${PORT_E_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_E_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "F"
    PORT_NUM_INT_PINS = "${PORT_F_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_F_INTERRUPT_USED
/>
<@PIO_INT_CALLBACK
    PIO_PORT = "G"
    PORT_NUM_INT_PINS = "${PORT_G_NUM_INT_PINS}"
    PIO_INTERRUPT = PORT_G_INTERRUPT_USED
/>


/******************************************************************************
  Function:
    PIO_Initialize ( void )

  Summary:
    Initialize the PIO library.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_Initialize ( void )
{
<#assign PORT = ['A', 'B', 'C', 'D', 'E', 'F', 'G'] >
<#assign PERFUNC = ['A', 'B', 'C', 'D', 'E', 'F', 'G', "GPIO"] >
<#list PORT as port>
	<#list PERFUNC as func>
	<#assign PORT_MSKR = "PORT_" + port + "_MSKR_Value" + func >
	<#assign PORT_CFGR = "FUNC_" + func + "_CFGR_Value">  
	<#if .vars[PORT_MSKR] != '0x0' && .vars[PORT_MSKR] != '0x0L'>
	<#lt> /* Port ${port} Peripheral function ${func} configuration */
	<#lt>	PIO${port}_REGS->PIO_MSKR = ${.vars[PORT_MSKR]};
	<#lt>	PIO${port}_REGS->PIO_CFGR = ${.vars[PORT_CFGR]};
	
	</#if>   
	</#list>
	<#list 0..31 as pin>
	<#assign PORT_MSKR = "PORT_" + port + "_MSKR_Value" + pin >
	<#assign PORT_CFGR = "PORT_" + port + "_CFGR_Value" + pin > 
	<#if .vars[PORT_CFGR] != '0x0'>
	<#lt> /* Port ${port} Pin ${pin} configuration */
	<#lt>	PIO${port}_REGS->PIO_MSKR = ${.vars[PORT_MSKR]};
	<#lt>	PIO${port}_REGS->PIO_CFGR = (PIO${port}_REGS->PIO_CFGR & (PIO_CFGR_FUNC_Msk)) | ${.vars[PORT_CFGR]};
	
	</#if>   
	</#list>
	<#assign PORT_LATCH = "PORT_" + port + "_LATCH" >
	<#if .vars[PORT_LATCH] != '0x0'>
	<#lt> /* Port ${port} Latch configuration */
	<#lt>	PIO${port}_REGS->PIO_SODR = ${.vars[PORT_LATCH]};
	
	</#if>
	<#assign PORT_SLCK = "PORT_" + port + "_SCLK_DIV" >
	<#if .vars[PORT_SLCK] != 0>
	<#lt> /* Port ${port} Slow clock Divider configuration */
	<#lt>	PIO${port}_REGS->PIO_SCDR = ${.vars[PORT_SLCK]};
	
	</#if>	
</#list>
}

// *****************************************************************************
// *****************************************************************************
// Section: PIO APIs which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    uint32_t PIO_PortRead ( PIO_PORT port )

  Summary:
    Read all the I/O lines of the selected port.

  Description:
    This function reads the live data values on all the I/O lines of the
    selected port.  Bit values returned in each position indicate corresponding
    pin levels.
    1 = Pin is high.
    0 = Pin is low.

    This function reads the value regardless of pin configuration, whether it is
    set as as an input, driven by the PIO Controller, or driven by a peripheral.

  Remarks:
    If the port has less than 32-bits, unimplemented pins will read as
    low (0).
    Implemented pins are Right aligned in the 32-bit return value.
*/
uint32_t PIO_PortRead(PIO_PORT port)
{
    return ((pio_registers_t*)port)->PIO_PDSR;
}

// *****************************************************************************
/* Function:
    void PIO_PortWrite (PIO_PORT port, uint32_t mask, uint32_t value);

  Summary:
    Write the value on the masked I/O lines of the selected port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortWrite(PIO_PORT port, uint32_t mask, uint32_t value)
{
    ((pio_registers_t*)port)->PIO_MSKR = mask;
    ((pio_registers_t*)port)->PIO_ODSR = value;
}

// *****************************************************************************
/* Function:
    uint32_t PIO_PortLatchRead ( PIO_PORT port )

  Summary:
    Read the latched value on all the I/O lines of the selected port.

  Remarks:
    See plib_pio.h for more details.
*/
uint32_t PIO_PortLatchRead(PIO_PORT port)
{
    return ((pio_registers_t*)port)->PIO_ODSR;
}

// *****************************************************************************
/* Function:
    void PIO_PortSet ( PIO_PORT port, uint32_t mask )

  Summary:
    Set the selected IO pins of a port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortSet(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_SODR = mask;
}

// *****************************************************************************
/* Function:
    void PIO_PortClear ( PIO_PORT port, uint32_t mask )

  Summary:
    Clear the selected IO pins of a port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortClear(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_CODR = mask;
}

// *****************************************************************************
/* Function:
    void PIO_PortToggle ( PIO_PORT port, uint32_t mask )

  Summary:
    Toggles the selected IO pins of a port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortToggle(PIO_PORT port, uint32_t mask)
{
    /* Write into Clr and Set registers */
    ((pio_registers_t*)port)->PIO_MSKR = mask;
    ((pio_registers_t*)port)->PIO_ODSR ^= mask;
}

// *****************************************************************************
/* Function:
    void PIO_PortInputEnable ( PIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as input.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortInputEnable(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_MSKR = mask;
    ((pio_registers_t*)port)->PIO_CFGR &= ~(1 << PIO_CFGR_DIR_Pos);	
}

// *****************************************************************************
/* Function:
    void PIO_PortOutputEnable ( PIO_PORT port, uint32_t mask )

  Summary:
    Enables selected IO pins of a port as output(s).

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortOutputEnable(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_MSKR = mask;
    ((pio_registers_t*)port)->PIO_CFGR |= (1 << PIO_CFGR_DIR_Pos);
}

// *****************************************************************************
/* Function:
    void PIO_PortInterruptEnable(PIO_PORT port, uint32_t mask)

  Summary:
    Enables IO interrupt on selected IO pins of a port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortInterruptEnable(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_IER = mask;
}

// *****************************************************************************
/* Function:
    void PIO_PortInterruptDisable(PIO_PORT port, uint32_t mask)

  Summary:
    Disables IO interrupt on selected IO pins of a port.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PortInterruptDisable(PIO_PORT port, uint32_t mask)
{
    ((pio_registers_t*)port)->PIO_IDR = mask;
}

<#if PORT_A_INTERRUPT_USED == true ||
     PORT_B_INTERRUPT_USED == true ||
     PORT_C_INTERRUPT_USED == true ||
     PORT_D_INTERRUPT_USED == true ||
     PORT_E_INTERRUPT_USED == true ||
     PORT_F_INTERRUPT_USED == true ||
     PORT_G_INTERRUPT_USED == true >
// *****************************************************************************
// *****************************************************************************
// Section: PIO APIs which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void PIO_PinInterruptCallbackRegister(
        PIO_PIN pin,
        const PIO_PIN_CALLBACK callback,
        uintptr_t context
    );

  Summary:
    Allows application to register callback for every pin.

  Remarks:
    See plib_pio.h for more details.
*/
void PIO_PinInterruptCallbackRegister(
    PIO_PIN pin,
    const PIO_PIN_CALLBACK callback,
    uintptr_t context
)
{
    uint8_t portIndex;
    portIndex = pin >> 5;

    switch( portIndex )
    {
    <#if PORT_A_INTERRUPT_USED == true>
        case 0:
        {
            if( portACurNumCb < portAMaxNumCb )
            {
                portAPinCbObj[ portACurNumCb ].pin   = pin;
                portAPinCbObj[ portACurNumCb ].callback = callback;
                portAPinCbObj[ portACurNumCb ].context  = context;
                portACurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_B_INTERRUPT_USED == true>
        case 1:
        {
            if( portBCurNumCb < portBMaxNumCb )
            {
                portBPinCbObj[ portBCurNumCb ].pin   = pin;
                portBPinCbObj[ portBCurNumCb ].callback = callback;
                portBPinCbObj[ portBCurNumCb ].context  = context;
                portBCurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_C_INTERRUPT_USED == true>
        case 2:
        {
            if( portCCurNumCb < portCMaxNumCb )
            {
                portCPinCbObj[ portCCurNumCb ].pin   = pin;
                portCPinCbObj[ portCCurNumCb ].callback = callback;
                portCPinCbObj[ portCCurNumCb ].context  = context;
                portCCurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_D_INTERRUPT_USED == true>
        case 3:
        {
            if( portDCurNumCb < portDMaxNumCb )
            {
                portDPinCbObj[ portDCurNumCb ].pin   = pin;
                portDPinCbObj[ portDCurNumCb ].callback = callback;
                portDPinCbObj[ portDCurNumCb ].context  = context;
                portDCurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_E_INTERRUPT_USED == true>
        case 4:
        {
            if( portECurNumCb < portEMaxNumCb )
            {
                portEPinCbObj[ portECurNumCb ].pin   = pin;
                portEPinCbObj[ portECurNumCb ].callback = callback;
                portEPinCbObj[ portECurNumCb ].context  = context;
                portECurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_F_INTERRUPT_USED == true>
        case 5:
        {
            if( portFCurNumCb < portFMaxNumCb )
            {
                portFPinCbObj[ portFCurNumCb ].pin   = pin;
                portFPinCbObj[ portFCurNumCb ].callback = callback;
                portFPinCbObj[ portFCurNumCb ].context  = context;
                portFCurNumCb++;
            }
            break;
        }
    </#if>
    <#if PORT_G_INTERRUPT_USED == true>
        case 6:
        {
            if( portGCurNumCb < portGMaxNumCb )
            {
                portGPinCbObj[ portGCurNumCb ].pin   = pin;
                portGPinCbObj[ portGCurNumCb ].callback = callback;
                portGPinCbObj[ portGCurNumCb ].context  = context;
                portGCurNumCb++;
            }
            break;
        }
    </#if>
        default:
        {
            break;
        }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine (ISR) Implementation(s)
// *****************************************************************************
// *****************************************************************************
</#if>

<#if PORT_A_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="A"
    />
</#if>
<#if PORT_B_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="B"
    />
</#if>
<#if PORT_C_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="C"
    />
</#if>
<#if PORT_D_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="D"
    />
</#if>
<#if PORT_E_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="E"
    />
</#if>
<#if PORT_F_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="F"
    />
</#if>
<#if PORT_G_INTERRUPT_USED == true>
    <@PIO_ISR_HANDLER
        PIO_CHANNEL="G"
    />
</#if>

<#macro PIO_ISR_HANDLER PIO_CHANNEL>
// *****************************************************************************
/* Function:
    void PIO${PIO_CHANNEL}_InterruptHandler (void)

  Summary:
    Interrupt handler for PORT${PIO_CHANNEL}.

  Description:
    This function defines the Interrupt service routine for PORT${PIO_CHANNEL}.
    This is the function which by default gets into Interrupt Vector Table.

  Remarks:
    User should not call this function.
*/
void PIO${PIO_CHANNEL}_InterruptHandler(void)
{
    uint32_t status;
    uint8_t i;

    status  = PIO${PIO_CHANNEL}_REGS->PIO_ISR;
    status &= PIO${PIO_CHANNEL}_REGS->PIO_IMR;
	
	for( i = 0; i < port${PIO_CHANNEL}CurNumCb; i++ )
	{
		if( ( status & ( 1 << (port${PIO_CHANNEL}PinCbObj[i].pin & 0x1F) ) ) &&
			port${PIO_CHANNEL}PinCbObj[i].callback != NULL )
		{
			port${PIO_CHANNEL}PinCbObj[i].callback ( port${PIO_CHANNEL}PinCbObj[i].pin, port${PIO_CHANNEL}PinCbObj[i].context );
		}
	}
}
</#macro>


/*******************************************************************************
 End of File
*/
