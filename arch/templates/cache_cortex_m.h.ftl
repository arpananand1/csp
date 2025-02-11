/*******************************************************************************
  Cortex-M L1 Cache Header

  File Name:
    device_cache.h

  Summary:
    Preprocessor definitions to provide L1 Cache control.

  Description:
    An MPLAB PLIB or Project can include this header to perform cache cleans,
    invalidates etc. For the DCache and ICache.

  Remarks:
    This header should not define any prototypes or data definitions, or 
    include any files that do.  The file only provides macro definitions for 
    build-time.

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

#ifndef DEVICE_CACHE_H
#define DEVICE_CACHE_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: L1 Cache Configuration
// *****************************************************************************
// *****************************************************************************
<#if CoreArchitecture != "CORTEX-M4" && INSTRUCTION_CACHE_ENABLE?? && INSTRUCTION_CACHE_ENABLE == true>
    <#lt>#define ICACHE_ENABLE()                                SCB_EnableICache()
    <#lt>#define ICACHE_DISABLE()                               SCB_DisableICache()
    <#lt>#define ICACHE_INVALIDATE()                            SCB_InvalidateICache()
    <#lt>#define INSTRUCTION_CACHE_ENABLED                      true
<#else>
    <#lt>#define ICACHE_ENABLE()
    <#lt>#define ICACHE_DISABLE()
    <#lt>#define ICACHE_INVALIDATE()
    <#lt>#define INSTRUCTION_CACHE_ENABLED                      false
</#if>

<#if CoreArchitecture != "CORTEX-M4" && DATA_CACHE_ENABLE?? && DATA_CACHE_ENABLE == true >
    <#lt>#define DCACHE_ENABLE()                                SCB_EnableDCache()
    <#lt>#define DCACHE_DISABLE()                               SCB_DisableDCache()
    <#lt>#define DCACHE_INVALIDATE()                            SCB_InvalidateDCache()
    <#lt>#define DCACHE_CLEAN()                                 SCB_CleanDCache()
    <#lt>#define DCACHE_CLEAN_INVALIDATE()                      SCB_CleanInvalidateDCache()
    <#lt>#define DCACHE_CLEAN_BY_ADDR(addr,sz)                  SCB_CleanDCache_by_Addr(addr,sz)
    <#lt>#define DCACHE_INVALIDATE_BY_ADDR(addr,sz)             SCB_InvalidateDCache_by_Addr(addr,sz)
    <#lt>#define DCACHE_CLEAN_INVALIDATE_BY_ADDR(addr,sz)       SCB_CleanInvalidateDCache_by_Addr(addr,sz)
    <#lt>#define DATA_CACHE_ENABLED                             true
<#else>
    <#lt>#define DCACHE_ENABLE()
    <#lt>#define DCACHE_DISABLE()
    <#lt>#define DCACHE_INVALIDATE()
    <#lt>#define DCACHE_CLEAN()
    <#lt>#define DCACHE_CLEAN_INVALIDATE()
    <#lt>#define DCACHE_CLEAN_BY_ADDR(addr,sz)
    <#lt>#define DCACHE_INVALIDATE_BY_ADDR(addr,sz)
    <#lt>#define DCACHE_CLEAN_INVALIDATE_BY_ADDR(addr,sz)
    <#lt>#define DATA_CACHE_ENABLED                             false
</#if>

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // #ifndef DEVICE_CACHE_H
