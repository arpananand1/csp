/*******************************************************************************
  Supply Controller(${SUPC_INSTANCE_NAME}) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_${SUPC_INSTANCE_NAME?lower_case}.h

  Summary
    ${SUPC_INSTANCE_NAME} Header File.

  Description
    This file defines the interface to the SUPC peripheral library. This
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

#ifndef PLIB_${SUPC_INSTANCE_NAME}_H    // Guards against multiple inclusion
#define PLIB_${SUPC_INSTANCE_NAME}_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include <stddef.h>
#include <stdbool.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part it.
*/

// *****************************************************************************
/* Callback function structure

  Summary:
    Defines the data type and function signature for the SUPC peripheral
    callback function.

  Description:
    This data type defines the function signature for the SUPC peripheral
    callback function. The SUPC peripheral will call back the client's function
    with this signature when a Brown Out event has been detected. This function
    will be called only if the BODVDD action in the NVM user row is set to
    interrupt.

  Function:
    void (*SUPC_BODVDD_CALLBACK)( uintptr_t context )

  Precondition:
    ${SUPC_INSTANCE_NAME}_Initialize() must have been called for the given supc
    peripheral instance and ${SUPC_INSTANCE_NAME}_BODVDDCallbackRegister() must have
    been called to set the function to be called.

  Parameters:
    context - Allows the caller to provide a context value (usually a pointer to
    the callers context for multi-instance clients).

  Returns:
    None.

  Example:
    <code>
      void APP_BrownOutEventHandler( uintptr_t context )
      {
           // do something
      }

      ${SUPC_INSTANCE_NAME}_BODVDDCallbackRegister(APP_BrownOutEventHandler, 0);
    </code>

  Remarks:
    None.
*/

typedef void (*SUPC_BODVDD_CALLBACK)( uintptr_t context );

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
    void ${SUPC_INSTANCE_NAME}_Initialize( void );

  Summary:
    Initializes given instance of SUPC peripheral.

  Description:
    This function initializes given instance of SUPC peripheral of the device
    with the values configured in MHC GUI.

  Precondition:
    MHC GUI should be configured with the right values.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
      ${SUPC_INSTANCE_NAME}_Initialize();
    </code>

  Remarks:
    This function should only be called once during system initialization
    before any other SUPC function is called.
*/

void ${SUPC_INSTANCE_NAME}_Initialize( void );

// *****************************************************************************
/* Function:
    void ${SUPC_INSTANCE_NAME}_VoltageRegulatorEnable( bool enable );

  Summary:
    Enable/Disable voltage regulator.

  Description:
    This function will enable or disable the main voltage regulator.

  Precondition:
    ${SUPC_INSTANCE_NAME}_Initialize() must have been called first for the
    associated instance.

  Parameters:
    enable - if true, enable voltage regulator. If false, disable voltage
    regulator.

  Returns:
    None.

  Example:
    <code>
      bool enable = true;
      ${SUPC_INSTANCE_NAME}_Initialize();
      ${SUPC_INSTANCE_NAME}_VoltageRegulatorEnable(enable);
    </code>

  Remarks:
    This function should only be called once during system initialization
    before any other SUPC function is called.
*/

void ${SUPC_INSTANCE_NAME}_VoltageRegulatorEnable( bool enable );

// *****************************************************************************
/* Function:
    void ${SUPC_INSTANCE_NAME}_BODVDDCallbackRegister( SUPC_BODVDD_CALLBACK callback,
                                                    uintptr_t context );

  Summary:
    Registers the function to be called when a Brown Out Event has occurred.

  Description
    This function registers the callback function to be called when a Brown Out
    event has occurred. Note that the callback function will be called only if
    the BODVDD action setting in NVM User Row is configured to generate an
    interrupt and not reset the system.

  Precondition:
    ${SUPC_INSTANCE_NAME}_Initialize() must have been called first for the
    associated instance.

  Parameters:
    callback - callback function pointer.

    context  - Allows the caller to provide a context value (usually a pointer
    to the callers context for multi-instance clients).

  Returns:
    None.

  Example:
    <code>
      void SUPC_Callback_Fn( uintptr_t context )
      {
          // do something
      }

      ${SUPC_INSTANCE_NAME}_Initialize();
      ${SUPC_INSTANCE_NAME}_BODVDDCallbackRegister(SUPC_Callback_Fn, NULL);
    </code>

  Remarks:
    Context value can be set to NULL is not required.  To disable callback
    function, pass NULL for the callback parameter
*/

void ${SUPC_INSTANCE_NAME}_BODVDDCallbackRegister( SUPC_BODVDD_CALLBACK callback, uintptr_t context );

// *****************************************************************************
/* Function:
    void ${SUPC_INSTANCE_NAME}_InterruptHandler( void );

  Summary:
    SUPC interrupt handler for BODVDD event action.

  Description
    This function will trigger BODVDD callback.

  Precondition:
    ${SUPC_INSTANCE_NAME}_Initialize() must have been called first.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    </code>

  Remarks:
    This will be get called from device vector.So don't call this function
    explicitly.
*/

void ${SUPC_INSTANCE_NAME}_InterruptHandler( void );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* PLIB_${SUPC_INSTANCE_NAME}_H */
