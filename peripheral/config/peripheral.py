"""*****************************************************************************
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
*****************************************************************************"""

import os.path

# Capability of different peripherals that higher level layers depends on
peripherals = {
                "EFC_6450"      : ["MEMORY"],
                "NVMCTRL_U2409" : ["MEMORY"],
                "NVMCTRL_U2207" : ["MEMORY"],
                "NVMCTRL_U2802" : ["MEMORY"],
                "FLEXCOM_11268" : ["UART", "SPI", "I2C"],
                "FLEXCOM_11277" : ["UART", "SPI", "I2C"],
                "SERCOM_U2201"  : ["UART", "SPI", "I2C"],
                "SPI_6088"      : ["SPI"],
                "TWI_6212"      : ["I2C"],
                "TWI_11280"     : ["I2C"],
                "TWIHS_11210"   : ["I2C"],
                "I2C_01441"     : ["I2C"],
                "I2C_00774"     : ["I2C"],
                "UART_02478"    : ["UART"],
                "UART_6418"     : ["UART"],
                "USART_6089"    : ["UART"],
                "USART_11278"   : ["UART"],
                "QSPI_U2008"    : ["SQI"],
                "QSPI_11171"    : ["SQI"],
                "SQI_00206"     : ["SQI"],
                "TC_U2212"      : ["TMR"],
                "TC_U2249"      : ["TMR"],
                "TC_6082"       : ["TMR"],
                "TC_44162"      : ["TMR"],
                "PIT_6079"      : ["TMR"],
                "RTT_6081"      : ["TMR"],
                "RTC_U2250"     : ["TMR"],
                "RTC_U2202"     : ["TMR"],
                "TMR_02815"     : ["TMR"],
                "TMR_00745"     : ["TMR"],
                "LCDC_11062"    : ["LCDC"],
                "SPI_01329"     : ["SPI"],
                "SPI_00753"     : ["SPI"],
                "UART_00734"    : ["UART"],
                "NVM_02819"     : ["MEMORY"],
                "NVM_01390"     : ["MEMORY"],
                "NVM_02629"     : ["MEMORY"],
                "NVM_00761"     : ["MEMORY"],
                "HEFC_44123"    : ["MEMORY"],
                "SDMMC_44002"   : ["SDHC"],
                "SDHC_U2011"    : ["SDHC"],
                "HSMCI_6449"    : ["SDHC"],
                "SDHC_00187"    : ["SDHC"],
                "DBGU_6059"     : ["UART"],
                "PMP_00751"     : ["PMP"],
                "TMR1_00687"    : ["TMR"],
                "TMR1_02141"    : ["TMR"]
}

if ("PIC32M" in Variables.get("__PROCESSOR")):
    coreTimerComponent = Module.CreateComponent("core_timer", "CORE TIMER", "/Peripherals/CORE TIMER/", "../peripheral/coretimer/config/coretimer.py")
    coreTimerComponent.addCapability("CORE_TIMER_TMR", "TMR")
    coreTimerComponent.setDisplayType("Peripheral Library")

periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
modules = periphNode.getChildren()

for module in range (0, len(modules)):

    periphName = str(modules[module].getAttribute("name"))
    periphID = str(modules[module].getAttribute("id"))
    periphScript = "/peripheral/" + periphName.lower() + "_" + periphID.lower() + \
                    "/config/" + periphName.lower() + ".py"

    # Don't load system services. They will be loaded by family specific script
    if any(x in periphName for x in ["PORT", "PIO", "AIC", "NVIC", "XDMAC", "DMAC", "OSCILLATOR", "PMC", "WDT", "DMT", "PAC", "MATRIX", "L2CC", "CMCC"]):
        print("CSP: System Peripheral [" + periphName + " id=" + periphID + "]")
        continue

    # Check if peripheral has implementation
    if (os.path.isfile(Variables.get("__CSP_DIR") + periphScript)):

        instances = modules[module].getChildren()
        for instance in range (0, len(instances)):

            periphInstanceName = str(instances[instance].getAttribute("name"))
            print("CSP: create component: Peripheral " + periphInstanceName + " (ID = " + periphID + ")")

            periphComponent = Module.CreateComponent(periphInstanceName.lower(), periphInstanceName.upper(), "/Peripherals/" +
                            periphName.upper() + "/", ".." + periphScript)

            periphComponent.setDisplayType("Peripheral Library")

            key = periphName + "_" + periphID

            if key in peripherals:
                for capablity in peripherals[key]:
                    capablityId = periphInstanceName + "_" + capablity
                    periphComponent.addCapability(capablityId, capablity)
            else:
                if periphName == "SMC":
                    smcRegGroup = ATDF.getNode( '/avr-tools-device-file/modules/module@[name="SMC"]/register-group@[name="SMC"]/register-group@[name="SMC_CS_NUMBER"]' )
                    smcChipSelCount = int( smcRegGroup.getAttribute( "count" ) )
                    for smcChipSel in range(0, smcChipSelCount):
                        periphComponent.addCapability("smc_cs"  + str(smcChipSel), "SMC_CS", "SMC_CS"  + str(smcChipSel), False)
                if periphName == "EBI":
                    ebiRegGroup = ATDF.getNode('/avr-tools-device-file/modules/module@[name="EBI"]/register-group@[name="EBI"]').getChildren()
                    ebiChipSelCount = 0
                    for csregister in ebiRegGroup:
                        if("EBICS" in csregister.getAttribute("name")):
                            ebiChipSelCount += 1
                    for ebiChipSel in range(0, ebiChipSelCount):
                        periphComponent.addCapability("ebi_cs"  + str(ebiChipSel), "EBI_CS", "EBI_CS"  + str(ebiChipSel), False)
    else:
        print("CSP: Peripheral [" + periphName + " id=" + periphID + "] is not supported in MCC")
