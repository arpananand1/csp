/*******************************************************************************
  Real Time Counter (${RTC_INSTANCE_NAME}) PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_${RTC_INSTANCE_NAME?lower_case}_clock.c

  Summary:
    ${RTC_INSTANCE_NAME} PLIB Implementation file

  Description:
    This file defines the interface to the RTC peripheral library. This
    library provides access to and control of the associated peripheral
    instance in clock/calendar mode.

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

#include "plib_${RTC_INSTANCE_NAME?lower_case}.h"
#include <stdlib.h>

/* Reference Year */
#define REFERENCE_YEAR              (${RTC_MODE2_REFERENCE_YEAR}U)

/* Refernce Year in tm structure year (C standard) */
#define TM_STRUCT_REFERENCE_YEAR    (1900U)

/* Adjust user year with respect to tm structure year (C Standard) */
#define ADJUST_TM_YEAR(year)        (year + TM_STRUCT_REFERENCE_YEAR)

/* Adjust user month */
#define ADJUST_MONTH(month)         (month + 1)

/* Adjust to tm structure month */
#define ADJUST_TM_STRUCT_MONTH(mon) (mon - 1)

<#if RTC_MODE2_INTERRUPT = true >
    <#lt>RTC_OBJECT ${RTC_INSTANCE_NAME?lower_case}Obj;
</#if>

void ${RTC_INSTANCE_NAME}_Initialize(void)
{
    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_CTRLA |= RTC_MODE2_CTRLA_SWRST_Msk;

    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_SWRST_Msk) == RTC_MODE2_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for synchronization after Software Reset */
    }

    <#if TAMP_DETECTION_SUPPORTED??>
        <#if TAMP_DETECTION_SUPPORTED>
            <#if (TAMP_DEBOUNCE_MAJ != "0") || (TAMP_DEBOUNCE_ASYNCH != "0") || TAMP_OUT || TAMP_DMA || (TAMP_DEBOUNCE_FREQUENCY != "0x0") || (TAMP_ACTIVE_FREQUENCY != "0x0")>
                <#lt>    <@compress single_line=true>${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_CTRLB = RTC_MODE2_CTRLB_DEBF(${TAMP_DEBOUNCE_FREQUENCY})|
                <#lt>                                                        RTC_MODE2_CTRLB_ACTF(${TAMP_ACTIVE_FREQUENCY})
                <#lt>                                                        ${TAMP_OUT?then("| RTC_MODE2_CTRLB_RTCOUT_Msk", "")}
                <#lt>                                                        ${TAMP_DMA?then("| RTC_MODE2_CTRLB_DMAEN_Msk", "")}
                <#lt>                                                        ${(TAMP_DEBOUNCE_ASYNCH != "0")?then("| RTC_MODE2_CTRLB_DEBASYNC_Msk", "")}
                <#lt>                                                        ${(TAMP_DEBOUNCE_MAJ != "0")?then("| RTC_MODE2_CTRLB_DEBMAJ_Msk", "")};</@compress>
              </#if>
            <#if TAMP_CHANNEL4_ACTION??>
                 <#if (TAMP_CHANNEL0_ACTION != '0x0') || (TAMP_CHANNEL1_ACTION != '0x0') ||(TAMP_CHANNEL2_ACTION != '0x0') ||(TAMP_CHANNEL3_ACTION != '0x0') ||(TAMP_CHANNEL4_ACTION != '0x0')>
                    <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_TAMPCTRL = RTC_TAMPCTRL_IN0ACT(${TAMP_CHANNEL0_ACTION}) ${(TAMP_CHANNEL0_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL0_Msk", "")} ${(TAMP_CHANNEL0_DEBNC)?then("| RTC_TAMPCTRL_DEBNC0_Msk", "")} | \
                    <#lt>                                   RTC_TAMPCTRL_IN1ACT(${TAMP_CHANNEL1_ACTION}) <#if TAMP_CHANNEL1_LEVEL??>${(TAMP_CHANNEL1_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL1_Msk", "")}${(TAMP_CHANNEL1_DEBNC)?then("| RTC_TAMPCTRL_DEBNC1_Msk", "")} </#if>| \
                    <#lt>                                   RTC_TAMPCTRL_IN2ACT(${TAMP_CHANNEL2_ACTION}) ${(TAMP_CHANNEL2_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL2_Msk", "")}${(TAMP_CHANNEL2_DEBNC)?then("| RTC_TAMPCTRL_DEBNC2_Msk", "")} | \
                    <#lt>                                   RTC_TAMPCTRL_IN3ACT(${TAMP_CHANNEL3_ACTION}) ${(TAMP_CHANNEL3_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL3_Msk", "")}${(TAMP_CHANNEL3_DEBNC)?then("| RTC_TAMPCTRL_DEBNC3_Msk", "")} | \
                    <#lt>                                   RTC_TAMPCTRL_IN4ACT(${TAMP_CHANNEL4_ACTION}) ${(TAMP_CHANNEL4_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL4_Msk", "")}${(TAMP_CHANNEL4_DEBNC)?then("| RTC_TAMPCTRL_DEBNC4_Msk", "")};
                </#if>
            <#else>
                 <#if (TAMP_CHANNEL0_ACTION != '0x0') || (TAMP_CHANNEL1_ACTION != '0x0') ||(TAMP_CHANNEL2_ACTION != '0x0') ||(TAMP_CHANNEL3_ACTION != '0x0')>
                    <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_TAMPCTRL = RTC_TAMPCTRL_IN0ACT(${TAMP_CHANNEL0_ACTION}) ${(TAMP_CHANNEL0_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL0_Msk", "")} ${(TAMP_CHANNEL0_DEBNC)?then("| RTC_TAMPCTRL_DEBNC0_Msk", "")} | \
                    <#lt>                                   RTC_TAMPCTRL_IN1ACT(${TAMP_CHANNEL1_ACTION}) <#if TAMP_CHANNEL1_LEVEL??>${(TAMP_CHANNEL1_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL1_Msk", "")}${(TAMP_CHANNEL1_DEBNC)?then("| RTC_TAMPCTRL_DEBNC1_Msk", "")} </#if> | \
                    <#lt>                                   RTC_TAMPCTRL_IN2ACT(${TAMP_CHANNEL2_ACTION}) ${(TAMP_CHANNEL2_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL2_Msk", "")}${(TAMP_CHANNEL2_DEBNC)?then("| RTC_TAMPCTRL_DEBNC2_Msk", "")} | \
                    <#lt>                                   RTC_TAMPCTRL_IN3ACT(${TAMP_CHANNEL3_ACTION}) ${(TAMP_CHANNEL3_LEVEL != "0")?then("| RTC_TAMPCTRL_TAMLVL3_Msk", "")}${(TAMP_CHANNEL3_DEBNC)?then("| RTC_TAMPCTRL_DEBNC3_Msk", "")};
                </#if>
            </#if>
        </#if>
    </#if>

    <@compress single_line=true>${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_CTRLA = RTC_MODE2_CTRLA_MODE(2) |
                                                            RTC_MODE2_CTRLA_PRESCALER(${RTC_MODE2_PRESCALER}) |
                                                            RTC_MODE2_CTRLA_CLOCKSYNC_Msk |
                                                            RTC_MODE2_CTRLA_ENABLE_Msk
                                                            <#if TAMP_DETECTION_SUPPORTED??>
                                                                <#if TAMP_DETECTION_SUPPORTED>
                                                                    ${TAMP_RESET_GP?then("| RTC_MODE2_CTRLA_GPTRST_Msk", "")}
                                                                    <#if TAMP_RESET_BACKUP??>
                                                                    ${TAMP_RESET_BACKUP?then("| RTC_MODE2_CTRLA_BKTRST_Msk", "")}
                                                                    </#if>
                                                                </#if>
                                                            </#if>;</@compress>


    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_ENABLE_Msk) == RTC_MODE2_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Synchronization after Enabling RTC */
    }

    <#if (RTC_MODE2_INTERRUPT = true) && (RTC_MODE2_INTENSET != "0")>
        <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTENSET = 0x${RTC_MODE2_INTENSET};

    </#if>
    <#if RTC_MODE2_EVCTRL != "0">
        <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_EVCTRL = 0x${RTC_MODE2_EVCTRL};
    </#if>
}
<#if RTC_FREQCORR = true >

    <#lt>void ${RTC_INSTANCE_NAME}_FrequencyCorrect (int8_t correction)
    <#lt>{
    <#lt>    uint32_t newCorrectionValue = 0;
    <#lt>
    <#lt>    newCorrectionValue = abs(correction);
    <#lt>
    <#lt>    /* Convert to positive value and adjust Register sign bit. */
    <#lt>    if (correction < 0)
    <#lt>    {
    <#lt>        newCorrectionValue |= RTC_FREQCORR_SIGN_Msk;
    <#lt>    }

    <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_FREQCORR = newCorrectionValue;

    <#lt>    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_FREQCORR_Msk) == RTC_MODE2_SYNCBUSY_FREQCORR_Msk)
    <#lt>    {
    <#lt>        /* Wait for synchronization after writing value to FREQCORR */
    <#lt>    }
    <#lt>}
</#if>

<#if RTC_MODE2_INTERRUPT = false>

    <#lt>bool ${RTC_INSTANCE_NAME}_PeriodicIntervalHasCompleted (RTC_PERIODIC_INT_MASK period)
    <#lt>{
    <#lt>    bool periodIntervalComplete = false;

    <#lt>    if( (${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTFLAG & period) == period )
    <#lt>    {
    <#lt>        periodIntervalComplete = true;

    <#lt>        /* Clear Periodic Interval Interrupt */
    <#lt>        ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTFLAG = period;
    <#lt>    }

    <#lt>    return periodIntervalComplete;
    <#lt>}
</#if>

bool ${RTC_INSTANCE_NAME}_RTCCTimeSet (struct tm * initialTime )
{
    /*
     * Add 1900 to the tm_year member and the adjust for the RTC reference year
     * Set YEAR(according to Reference Year), MONTH and DAY
     *set Hour Minute and Second
     */
    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_CLOCK = ((TM_STRUCT_REFERENCE_YEAR + initialTime->tm_year) - REFERENCE_YEAR) << RTC_MODE2_CLOCK_YEAR_Pos |
                    ((ADJUST_MONTH(initialTime->tm_mon)) << RTC_MODE2_CLOCK_MONTH_Pos) |
                    (initialTime->tm_mday << RTC_MODE2_CLOCK_DAY_Pos) |
                    (initialTime->tm_hour << RTC_MODE2_CLOCK_HOUR_Pos) |
                    (initialTime->tm_min << RTC_MODE2_CLOCK_MINUTE_Pos) |
                    (initialTime->tm_sec << RTC_MODE2_CLOCK_SECOND_Pos);

    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_CLOCK_Msk) == RTC_MODE2_SYNCBUSY_CLOCK_Msk)
    {
        /* Synchronization after writing value to CLOCK Register */
    }
    return true;
}

void ${RTC_INSTANCE_NAME}_RTCCTimeGet ( struct tm * currentTime )
{
    uint32_t dataClockCalendar = 0;

    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk) == RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk)
    {
        /* Synchronization before reading value from CLOCK Register */
    }

    dataClockCalendar = ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_CLOCK;

    currentTime->tm_hour =  (dataClockCalendar & RTC_MODE2_CLOCK_HOUR_Msk) >> RTC_MODE2_CLOCK_HOUR_Pos;
    currentTime->tm_min  =  (dataClockCalendar & RTC_MODE2_CLOCK_MINUTE_Msk) >> RTC_MODE2_CLOCK_MINUTE_Pos;
    currentTime->tm_sec  =  (dataClockCalendar & RTC_MODE2_CLOCK_SECOND_Msk) >> RTC_MODE2_CLOCK_SECOND_Pos;

    currentTime->tm_mon  =  ADJUST_TM_STRUCT_MONTH(((dataClockCalendar & RTC_MODE2_CLOCK_MONTH_Msk) >> RTC_MODE2_CLOCK_MONTH_Pos));
    currentTime->tm_year =  (((dataClockCalendar & RTC_MODE2_CLOCK_YEAR_Msk)>> RTC_MODE2_CLOCK_YEAR_Pos) + REFERENCE_YEAR) - TM_STRUCT_REFERENCE_YEAR;
    currentTime->tm_mday =  (dataClockCalendar & RTC_MODE2_CLOCK_DAY_Msk) >> RTC_MODE2_CLOCK_DAY_Pos;
}
<#if TAMP_DETECTION_SUPPORTED??>
    <#if TAMP_DETECTION_SUPPORTED>
        <#if RTC_BKUP_SUPPORTED??>
            <#lt>void ${RTC_INSTANCE_NAME}_BackupRegisterSet( BACKUP_REGISTER reg, uint32_t value )
            <#lt>{
            <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_BKUP[reg] = value;
            <#lt>}

            <#lt>uint32_t ${RTC_INSTANCE_NAME}_BackupRegisterGet( BACKUP_REGISTER reg )
            <#lt>{
            <#lt>    return(${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_BKUP[reg]);
            <#lt>}
        </#if>
        <#lt> TAMPER_CHANNEL ${RTC_INSTANCE_NAME}_TamperSourceGet( void )
        <#lt>{
        <#lt>    return((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_TAMPID) & (0xFF));
        <#lt>}

        <#lt>void ${RTC_INSTANCE_NAME}_RTCCTimeStampGet(  struct tm * timeStamp  )
        <#lt>{
        <#lt>    uint32_t dataClockCalendar = 0;

        <#lt>    dataClockCalendar = ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_TIMESTAMP;

        <#lt>    timeStamp->tm_hour =  (dataClockCalendar & RTC_MODE2_TIMESTAMP_HOUR_Msk) >> RTC_MODE2_TIMESTAMP_HOUR_Pos;
        <#lt>    timeStamp->tm_min  =  (dataClockCalendar & RTC_MODE2_TIMESTAMP_MINUTE_Msk) >> RTC_MODE2_TIMESTAMP_MINUTE_Pos;
        <#lt>    timeStamp->tm_sec  =  (dataClockCalendar & RTC_MODE2_TIMESTAMP_SECOND_Msk) >> RTC_MODE2_TIMESTAMP_SECOND_Pos;

        <#lt>    timeStamp->tm_mon  =  ADJUST_TM_STRUCT_MONTH(((dataClockCalendar & RTC_MODE2_TIMESTAMP_MONTH_Msk) >> RTC_MODE2_TIMESTAMP_MONTH_Pos));
        <#lt>    timeStamp->tm_year =  (((dataClockCalendar & RTC_MODE2_TIMESTAMP_YEAR_Msk)>> RTC_MODE2_TIMESTAMP_YEAR_Pos) + REFERENCE_YEAR) - TM_STRUCT_REFERENCE_YEAR;
        <#lt>    timeStamp->tm_mday =  (dataClockCalendar & RTC_MODE2_TIMESTAMP_DAY_Msk) >> RTC_MODE2_TIMESTAMP_DAY_Pos;
        <#lt>}
    </#if>
</#if>

<#if RTC_MODE2_INTERRUPT = true>
    <#if RTC_MODE2_NUM_ALARM == 1>
        <#lt>bool ${RTC_INSTANCE_NAME}_RTCCAlarmSet (struct tm * alarmTime, RTC_ALARM_MASK mask)
        <#lt>{
        <#lt>    /*
        <#lt>     * Add 1900 to the tm_year member and the adjust for the RTC reference year
        <#lt>     * Set YEAR(according to Reference Year), MONTH and DAY
        <#lt>     * Set Hour, Minute and second
        <#lt>     */
        <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_ALARM = ((TM_STRUCT_REFERENCE_YEAR + alarmTime->tm_year) - REFERENCE_YEAR) << RTC_MODE2_CLOCK_YEAR_Pos |
        <#lt>                    (ADJUST_MONTH(alarmTime->tm_mon) << RTC_MODE2_CLOCK_MONTH_Pos) |
        <#lt>                    (alarmTime->tm_mday << RTC_MODE2_CLOCK_DAY_Pos) |
        <#lt>                    (alarmTime->tm_hour << RTC_MODE2_CLOCK_HOUR_Pos) |
        <#lt>                     (alarmTime->tm_min << RTC_MODE2_CLOCK_MINUTE_Pos) |
        <#lt>                     (alarmTime->tm_sec << RTC_MODE2_CLOCK_SECOND_Pos);

        <#lt>    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_ALARM0_Msk) == RTC_MODE2_SYNCBUSY_ALARM0_Msk)
        <#lt>    {
        <#lt>        /* Synchronization after writing to ALARM register */
        <#lt>    }

        <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_MASK = mask;

        <#lt>    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_MASK0_Msk) == RTC_MODE2_SYNCBUSY_MASK0_Msk)
        <#lt>    {
        <#lt>        /* Synchronization after writing value to MASK Register */
        <#lt>    }

        <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTENSET = RTC_MODE2_INTENSET_ALARM0_Msk;

        <#lt>    return true;
        <#lt>}
    <#else>
        <#list 0..(RTC_MODE2_NUM_ALARM - 1) as i>
            <#lt>bool ${RTC_INSTANCE_NAME}_RTCCAlarm${i}Set (struct tm * alarmTime, RTC_ALARM_MASK mask)
            <#lt>{
            <#lt>    /*
            <#lt>     * Add 1900 to the tm_year member and the adjust for the RTC reference year
            <#lt>     * Set YEAR(according to Reference Year), MONTH and DAY
            <#lt>     * Set Hour, Minute and second
            <#lt>     */
            <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_ALARM${i} = ((TM_STRUCT_REFERENCE_YEAR + alarmTime->tm_year) - REFERENCE_YEAR) << RTC_MODE2_CLOCK_YEAR_Pos |
            <#lt>                    (ADJUST_MONTH(alarmTime->tm_mon) << RTC_MODE2_CLOCK_MONTH_Pos) |
            <#lt>                    (alarmTime->tm_mday << RTC_MODE2_CLOCK_DAY_Pos) |
            <#lt>                    (alarmTime->tm_hour << RTC_MODE2_CLOCK_HOUR_Pos) |
            <#lt>                     (alarmTime->tm_min << RTC_MODE2_CLOCK_MINUTE_Pos) |
            <#lt>                     (alarmTime->tm_sec << RTC_MODE2_CLOCK_SECOND_Pos);

            <#lt>    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_ALARM${i}_Msk) == RTC_MODE2_SYNCBUSY_ALARM${i}_Msk)
            <#lt>    {
            <#lt>        /* Synchronization after writing to ALARM register */
            <#lt>    }

            <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_MASK${i} = mask;

            <#lt>    while((${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_MASK${i}_Msk) == RTC_MODE2_SYNCBUSY_MASK${i}_Msk)
            <#lt>    {
            <#lt>        /* Synchronization after writing value to MASK Register */
            <#lt>    }

            <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTENSET = RTC_MODE2_INTENSET_ALARM${i}_Msk;

            <#lt>    return true;
            <#lt>}
        </#list>
    </#if>

    <#lt>void ${RTC_INSTANCE_NAME}_RTCCCallbackRegister ( RTC_CALLBACK callback, uintptr_t context)
    <#lt>{
    <#lt>    ${RTC_INSTANCE_NAME?lower_case}Obj.alarmCallback = callback;
    <#lt>    ${RTC_INSTANCE_NAME?lower_case}Obj.context       = context;
    <#lt>}

    <#lt>void ${RTC_INSTANCE_NAME}_InterruptHandler(void)
    <#lt>{
    <#lt>    ${RTC_INSTANCE_NAME?lower_case}Obj.intCause = ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTFLAG;

    <#lt>    /* Clear All Interrupts */
    <#lt>    ${RTC_INSTANCE_NAME}_REGS->MODE2.RTC_INTFLAG = RTC_MODE2_INTFLAG_Msk;
    
    <#lt>    if(${RTC_INSTANCE_NAME?lower_case}Obj.alarmCallback != NULL)
    <#lt>    {
    <#lt>        ${RTC_INSTANCE_NAME?lower_case}Obj.alarmCallback(${RTC_INSTANCE_NAME?lower_case}Obj.intCause, ${RTC_INSTANCE_NAME?lower_case}Obj.context);
    <#lt>    }
    <#lt>}
</#if>
