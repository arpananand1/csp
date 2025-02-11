"""*****************************************************************************
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
*****************************************************************************"""

def setXDMACDefaultSettings():
    triggerSettings = { "Software Trigger"  : ["MEM_TRAN", "PER2MEM", "HWR_CONNECTED", "INCREMENTED_AM", "INCREMENTED_AM", "AHB_IF1", "AHB_IF1", "BYTE", "CHK_1", "SINGLE"],
                        "Standard_Transmit" : ["PER_TRAN", "MEM2PER", "HWR_CONNECTED", "INCREMENTED_AM", "FIXED_AM",       "AHB_IF0", "AHB_IF1", "BYTE", "CHK_1", "SINGLE"],
                        "Standard_Receive"  : ["PER_TRAN", "PER2MEM", "HWR_CONNECTED", "FIXED_AM",       "INCREMENTED_AM", "AHB_IF1", "AHB_IF0", "BYTE", "CHK_1", "SINGLE"]}

    return triggerSettings

def updateLinkerScript(symbol, event):
    compiler_choice = event['source'].getSymbolByID("COMPILER_CHOICE")
    memory_loc  = event['source'].getSymbolByID("EXECUTION_MEMORY")
    if compiler_choice.getSelectedKey() == "XC32":
        if memory_loc.getValue()  == "DDR":
            symbol.setSourcePath("arm/templates/xc32/cortex_a/SAMA5D2/ddram.ld.ftl")
            symbol.setOutputName("ddr.ld")
        else:
            symbol.setSourcePath("arm/templates/xc32/cortex_a/SAMA5D2/sram.ld.ftl")
            symbol.setOutputName("sram.ld")
    else:
        if memory_loc.getValue() == "DDR":
            symbol.setSourcePath("arm/templates/iar/cortex_a/SAMA5D2/sam_a5_ddr.icf.ftl")
            symbol.setOutputName("ddr.icf")
        else:
            symbol.setSourcePath("arm/templates/iar/cortex_a/SAMA5D2/sram.icf.ftl")
            symbol.setOutputName("sram.icf")

def updateStartupFile(symbol, event):
    compiler_choice = event['source'].getSymbolByID("COMPILER_CHOICE")
    if compiler_choice.getSelectedKey() == "XC32":
        symbol.setSourcePath("arm/templates/xc32/cortex_a/SAMA5D2/cstartup.s.ftl")
        symbol.setOutputName("cstartup.S")
    else:
        symbol.setSourcePath("arm/templates/iar/cortex_a/SAMA5D2/sam_a5_cstartup.s.ftl")
        symbol.setOutputName("cstartup.s")

def setAppStartAddress(symbol, event):
    if event["value"] == "DDR":
        Database.setSymbolValue("core", "APP_START_ADDRESS", "0x26f00000")
    else:
        Database.setSymbolValue("core", "APP_START_ADDRESS", "0x0")

print ("Loading System Services for " + Variables.get("__PROCESSOR"))

deviceFamily = coreComponent.createStringSymbol("DeviceFamily", devCfgMenu)
deviceFamily.setLabel("Device Family")
deviceFamily.setDefaultValue("SAMA5D2")
deviceFamily.setReadOnly(True)
deviceFamily.setVisible(False)

cortexMenu = coreComponent.createMenuSymbol("CORTEX_MENU", None)
cortexMenu.setLabel("Cortex-A5 Configuration")
cortexMenu.setDescription("Configuration for Cortex A5")

freeRTOSVectors = coreComponent.createBooleanSymbol("USE_FREERTOS_VECTORS", None)
freeRTOSVectors.setVisible(False)
freeRTOSVectors.setReadOnly(True)
freeRTOSVectors.setDefaultValue(False)

#SRAM or DDR
Database.setSymbolValue("core", "APP_START_ADDRESS", "0x26f00000")
memory_loc = coreComponent.createComboSymbol("EXECUTION_MEMORY", cortexMenu, ['DDR', 'SRAM'])
memory_loc.setLabel("Execution Memory")
memory_loc.setDefaultValue("DDR")
memory_loc.setDescription("Generate image to run out of either SRAM or DDR")
memory_loc.setDependencies(setAppStartAddress, ["EXECUTION_MEMORY"])

#load MMU with default 1:1 mapping so we can use cache
execfile(Variables.get("__CORE_DIR") + "/../peripheral/mmu_v7a/config/mmu.py")

#load Matrix -- default all peripherals to non-secure
execfile(Variables.get("__CORE_DIR") + "/../peripheral/matrix_44025/config/matrix.py")

#load L2CC
execfile(Variables.get("__CORE_DIR") + "/../peripheral/l2cc_11160/config/l2cc.py")

# load clock manager information
execfile(Variables.get("__CORE_DIR") + "/../peripheral/clk_sam_a5d2/config/clk.py")
coreComponent.addPlugin("../peripheral/clk_sam_a5d2/plugin/clk_sam_a5d2.jar")

# load device specific pin manager information
execfile(Variables.get("__CORE_DIR") + "/../peripheral/pio_11264/config/pio.py")
coreComponent.addPlugin("../peripheral/pio_11264/plugin/pio_11264.jar")

# load AIC
execfile(Variables.get("__CORE_DIR") + "/../peripheral/aic_11051/config/aic.py")
coreComponent.addPlugin("../peripheral/aic_11051/plugin/aic_11051.jar")

# load dma manager information
execfile(Variables.get("__CORE_DIR") + "/../peripheral/xdmac_11161/config/xdmac.py")
coreComponent.addPlugin("../peripheral/xdmac_11161/plugin/dmamanager.jar")

# load wdt
execfile(Variables.get("__CORE_DIR") + "/../peripheral/wdt_6080/config/wdt.py")

# load ADC manager information
coreComponent.addPlugin("../peripheral/adc_44073/plugin/adc_44073.jar")
# load AIC manager information
coreComponent.addPlugin("../peripheral/aic_11051/plugin/aic_11051.jar")

compiler_choice = deviceFamily.getComponent().getSymbolByID("COMPILER_CHOICE")
if compiler_choice.getSelectedKey() == "XC32":
    armSysStartSourceFile = coreComponent.createFileSymbol("STARTUP_C", None)
    armSysStartSourceFile.setSourcePath("arm/templates/xc32/cortex_a/SAMA5D2/cstartup.s.ftl")
    armSysStartSourceFile.setOutputName("cstartup.S")
    armSysStartSourceFile.setMarkup(True)
    armSysStartSourceFile.setOverwrite(True)
    armSysStartSourceFile.setDestPath("")
    armSysStartSourceFile.setProjectPath("config/" + configName + "/")
    armSysStartSourceFile.setType("SOURCE")
    armSysStartSourceFile.setDependencies(updateStartupFile, ["COMPILER_CHOICE"])

    linkerFile = coreComponent.createFileSymbol("LINKER_SCRIPT", None)
    linkerFile.setSourcePath("arm/templates/xc32/cortex_a/SAMA5D2/ddram.ld.ftl")
    linkerFile.setOutputName("ddr.ld")
    linkerFile.setMarkup(True)
    linkerFile.setOverwrite(True)
    linkerFile.setDestPath("")
    linkerFile.setProjectPath("config/" + configName + "/")
    linkerFile.setType("LINKER")
    linkerFile.setDependencies(updateLinkerScript, ["EXECUTION_MEMORY", "COMPILER_CHOICE"])

    sym = coreComponent.createSettingSymbol(None, None)
    sym.setCategory("C32")
    sym.setKey("preprocessor-macros")
    sym.setValue("__FPU_PRESENT=1")
    sym.setAppend(True, ";")

    sym = coreComponent.createSettingSymbol(None, None)
    sym.setCategory("C32")
    sym.setKey("appendMe")
    sym.setValue("-marm -cpu=cortex-a5 -mfpu=neon-vfpv4")
    sym.setAppend(True, ";")

elif compiler_choice.getSelectedKey() == "IAR":
    armSysStartSourceFile = coreComponent.createFileSymbol("STARTUP_C", None)
    armSysStartSourceFile.setSourcePath("arm/templates/iar/cortex_a/SAMA5D2/sam_a5_cstartup.s.ftl")
    armSysStartSourceFile.setOutputName("cstartup.s")
    armSysStartSourceFile.setMarkup(True)
    armSysStartSourceFile.setOverwrite(True)
    armSysStartSourceFile.setDestPath("")
    armSysStartSourceFile.setProjectPath("config/" + configName + "/")
    armSysStartSourceFile.setType("SOURCE")
    armSysStartSourceFile.setDependencies(updateStartupFile, ["COMPILER_CHOICE"])

    linkerFile = coreComponent.createFileSymbol("LINKER_SCRIPT", None)
    linkerFile.setSourcePath("arm/templates/iar/cortex_a/SAMA5D2/sam_a5_ddr.icf.ftl")
    linkerFile.setOutputName("ddr.icf")
    linkerFile.setMarkup(True)
    linkerFile.setOverwrite(True)
    linkerFile.setDestPath("")
    linkerFile.setProjectPath("config/" + configName + "/")
    linkerFile.setType("LINKER")
    linkerFile.setDependencies(updateLinkerScript, ["EXECUTION_MEMORY", "COMPILER_CHOICE"])

#default exception handlers.
faultSourceFile = coreComponent.createFileSymbol("DFLT_FAULT_HANDLER_C", None)
faultSourceFile.setSourcePath("arm/templates/common/mpu_handlers/fault_handlers.c")
faultSourceFile.setOutputName("fault_handlers.c")
faultSourceFile.setMarkup(True)
faultSourceFile.setOverwrite(True)
faultSourceFile.setDestPath("")
faultSourceFile.setProjectPath("config/" + configName + "/")
faultSourceFile.setType("SOURCE")
