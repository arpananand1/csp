/*******************************************************************************
  Analog Comparator Controller(ACC) Peripheral Library Interface Header File

  Company
    Microchip Technology Inc.

  File Name
    acc.h

  Summary
    ACC peripheral library interface.

  Description
    This file defines the interface to the ACC peripheral library.  This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    This header is for documentation only.  The actual acc<x> headers will be
    generated as required by the MCC (where <x> is the peripheral instance
    number).
    Every interface symbol has a lower-case 'x' in it following the "ACC"
    abbreviation.  This 'x' will be replaced by the peripheral instance number
    in the generated headers.  These are the actual functions that should be
    used.
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc.  All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third-party product
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
// DOM-IGNORE-END

#ifndef PLIB_ACCx_H    // Guards against multiple inclusion
#define PLIB_ACCx_H

#include <stddef.h>
#include <stdbool.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/*  The following data type definitions are used by the functions in this
    interface.
*/

// *****************************************************************************
/* ACC comparison status
   Summary:
    Identifies the ACC Comparison status

   Description:
    This data type identifies the ACC Comparison status

   Remarks:
    Refer to the specific device data sheet to determine availability.
*/
typedef enum
{
    /*ACC Output*/
    ACC_STATUS_SOURCE_COMPARATOR_OUTPUT = ACC_ISR_SCO_Msk,      

    /*ACC Interrupt*/
    ACC_STATUS_SOURCE_COMPARISON_EDGE = ACC_ISR_CE_Msk,

} ACC_STATUS_SOURCE;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void ACCx_Initialize(void)

   Summary:
     Initializes given instance of the ACC peripheral.

   Description:
     This function initializes the given instance of the ACC peripheral as
     configured by the user from within the MCC. 

   Precondition:
     None.

   Parameters:
    None.

   Returns:
    None.

   Example:
    <code>
    ACC1_Initialize();
    </code>

   Remarks:
    This function must be called before any other ACC function is called and it
    should be called only once.
*/

void ACCx_Initialize (void);

// *****************************************************************************
/* Function:
    bool ACCx_StatusGet(ACC_STATUS_SOURCE status)

  Summary:
    Gets the current comparison status of the ACC module.

  Description:
    This routine provides the current comparison status of the ACC  module.

  Precondition:
    Function ACCx_Initialize should have been called before calling this
    function.

  Parameters:
    status - ACC_STATUS_SOURCE_COMPARATOR_OUTPUT, To know the comparator output 
             status
             ACC_STATUS_SOURCE_COMPARISON_EDGE, To know a selected egde occurred
             on comparator output or not
             
  Returns:
   Returns the comparison status.

  Example:
    <code>
    bool status;
    status = ACC1_StatusGet(ACC_STATUS_SOURCE_COMPARATOR_OUTPUT);
    if (status)
    {
        // Application related tasks     
    }
    </code>

  Remarks:
    None.

*/
bool ACCx_StatusGet (ACC_STATUS_SOURCE status);

// *****************************************************************************
/* ACC Callback Function pointer
   typedef void (*ACC_CALLBACK) (uintptr_t context)

  Summary:
    Pointer to a ACC callback function

  Description:
    This data type defines the required function signature for the ACC Callback 
    function.
    A client must register a pointer to a callback function whose function
    signature (parameter and return value types) match the types specified by
    this function pointer in order to receive event callback.
    The parameters and return values and are described here and a partial
    example implementation is provided.

  Parameters:
    context - Value identifying the context of the application that registered
              the callback function.

  Returns:
    None.

   Example:
    Refer to the ACCx_CallbackRegister( ) function code example.

  Remarks:
    None
*/
typedef void (*ACC_CALLBACK) (uintptr_t context);

// *****************************************************************************
/* Function:
    void ACCx_CallbackRegister (ACC_CALLBACK callback, uintptr_t context);
  Summary:
    Allows a client to identify a callback function.

  Description:
    This routine allows a client to identify a callback function.

  Precondition:
    Function ACCx_Initialize should have been called before calling this
    function.

  Parameters:
    callback - Pointer to the callback function.
    context  - The value of parameter will be passed back to the client
               unchanged, when the callback function is called.  It can be 
               used to identify any client specific data object that identifies
               the instance of the client module (for example, it may be a
               pointer to the client module's state structure).   

  Returns:
   None.

  Example:
    <code>
    MY_APP_OBJ myAppObj;
    
    void APP_ACC_CallbackFunction (uintptr_t context)
    {  
        // The context was set to an application specific object.
        // It is now retrievable easily in Callback function.
           MY_APP_OBJ myAppObj = (MY_APP_OBJ *) context;
        //Application related tasks
    }
                  
    ACC1_CallbackRegister (APP_ACC_CallbackFunction, (uintptr_t)&myAppObj);  
    </code>

  Remarks:
    None.

*/
void ACCx_CallbackRegister (ACC_CALLBACK callback, uintptr_t context);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
// DOM-IGNORE-END
#endif // PLIB_ACCx_H
