################################################################################
#### Global Variables ####
################################################################################
global instance
global sdramcSym_CR__NR
global sdramcSym_BURST_TYPE
global sdramcSym_BURST_LENGTH
global sdramcSym_CR_CAS
global sdramcSym_LPR_PASR
global sdramcSym_LPR_TCSR
global sdramcSym_LPR_DS

################################################################################
#### Register Information ####
################################################################################
sdramcRegModule = Register.getRegisterModule("SDRAMC")
ValGrp_MDR__MD = sdramcRegModule.getValueGroup("SDRAMC_MDR__MD")
ValGrp_CR__NC  = sdramcRegModule.getValueGroup("SDRAMC_CR__NC")
ValGrp_CR__NR  = sdramcRegModule.getValueGroup("SDRAMC_CR__NR")
ValGrp_CR__NB  = sdramcRegModule.getValueGroup("SDRAMC_CR__NB")
ComboVal_CR_DBW = ["16-bits", "32-bits"]
ComboVal_BURST_TYPE = ["SEQUENTIAL", "INTERLEAVED"]

################################################################################
#### Default values and constants ####
################################################################################
# Burst Length
SDRAMC_DEFAULT_MIN_VALUE                = 0
SDRAMC_BURST_LENGHT_MAX_VALUE           = 7

# SDRAM Timing parameters default values
SDRAMC_CR_CAS_DEFAULT_VALUE             = 3
SDARMC_CR_TWR_DEFAULT_VALUE             = 2
SDRAMC_CR_TRC_TRFC_DEFAULT_VALUE        = 9
SDRAMC_CR_TRP_DEFAULT_VALUE             = 3
SDRAMC_CR_TRCD_DEFAULT_VALUE            = 3
SDRAMC_CR_TRAS_DEFAULT_VALUE            = 6
SDARMC_CR_TXSR_DEFAULT_VALUE            = 10

SDARMC_CFR1_TMRD_DEFAULT_VALUE          = 2
SDRAMC_REFRESH_TIME_IN_MS_DEFAULT_VALUE = 32

################################################################################
#### Business Logic ####
################################################################################

# Function to Enable/Disable SDRAM Low-Power Configurations
def lowPowerVisibility(symbol, event) :
    symObj=event["symbol"]

    if(symObj.getSelectedKey()== "LPSDRAM"):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def calcRefreshCount(time, rowlines, clk):
    rowlines = rowlines[-2:]
    rowlines = int(rowlines)
    rows=2**rowlines
    count=time*(clk/rows)/1000
    return count

# Function to set label based on the Refresh time in ms as selected in Combo Symbol SDRAMC_CR_NR
def calcRefreshCount_CB(symbol, event) :
    global instance
    global sdramcSym_CR__NR
    clk = int(Database.getSymbolValue("core", "MASTERCLK_FREQ"))
    time = Database.getSymbolValue("sdramc" + str(instance), "SDRAMC_REFRESH_TIME_IN_MS")
    rowlines = sdramcSym_CR__NR.getSelectedKey()
    count=calcRefreshCount(time, rowlines, clk)
    symbol.clearValue()
    symbol.setValue(count, 1)

# MRS<2:0>  -> Burst Length
# MRS<3>    -> Burst Type
# MRS<6:4>  -> CAS Latency
def calcMRS(symbol, event) :
    type=sdramcSym_BURST_TYPE.getValue()
    length=sdramcSym_BURST_LENGTH.getValue()
    cas=sdramcSym_CR_CAS.getValue()
    if(type=="INTERLEAVED"):
        mrs=8+(16 * cas) + length
    else:
        mrs=(16 * cas) + length
    symbol.setValue(mrs,1)

# EMRS<2:0> -> PASR
# EMRS<4:3> -> TCSR
# EMRS<6:5> -> DS
def calcEMRS(symbol, event) :
    pasr=sdramcSym_LPR_PASR.getValue()
    tcsr=sdramcSym_LPR_TCSR.getValue()
    ds=sdramcSym_LPR_DS.getValue()
    emrs = pasr + (8*tcsr)+(ds*32)
    symbol.setValue(emrs,1)

################################################################################
#### Component ####
################################################################################
def instantiateComponent(sdramcComponent):
    global instance
    global sdramcSym_CR__NR
    global sdramcSym_BURST_TYPE
    global sdramcSym_BURST_LENGTH
    global sdramcSym_CR_CAS
    global sdramcSym_LPR_PASR
    global sdramcSym_LPR_TCSR
    global sdramcSym_LPR_DS

    instance = sdramcComponent.getID()[-1:]

    sdramcIndex = sdramcComponent.createIntegerSymbol("INDEX", None)
    sdramcIndex.setVisible(False)
    sdramcIndex.setDefaultValue(int(instance))

    cpuclk = Database.getSymbolValue("core", "PROCESSORCLK_FREQ")
    cpuclk = int(cpuclk)

    sdramcSymClkFreq = sdramcComponent.createIntegerSymbol("SDRAMC_CPU_CLK_FREQ", None)
    sdramcSymClkFreq.setLabel("Get Core Clock Frequency")
    sdramcSymClkFreq.setVisible(False)
    sdramcSymClkFreq.setDefaultValue(cpuclk)

    # SDRAMC Features
    sdramcSymMenu_features = sdramcComponent.createMenuSymbol("SDRAMC_FEATURE_MENU", None)
    sdramcSymMenu_features.setLabel("Configure SDRAM features")

    sdramcSym_MDR__MD = sdramcComponent.createKeyValueSetSymbol("SDRAMC_MDR_MD", sdramcSymMenu_features)
    sdramcSym_MDR__MD.setOutputMode("Key")
    sdramcSym_MDR__MD.setDisplayMode("Description")
    sdramcSym_MDR__MD.setLabel("SDRAM Type")
    count = ValGrp_MDR__MD.getValueCount()
    for id in range(0,count):
        valueName = ValGrp_MDR__MD.getValueNames()[id]
        sdramcSym_MDR__MD.addKey(valueName, ValGrp_MDR__MD.getValue(valueName).getValue(), ValGrp_MDR__MD.getValue(valueName).getDescription())
    sdramcSym_MDR__MD.setSelectedKey("SDRAM",2)

    sdramcSym_CR__NR = sdramcComponent.createKeyValueSetSymbol("SDRAMC_CR__NR", sdramcSymMenu_features)
    sdramcSym_CR__NR.setOutputMode("Key")
    sdramcSym_CR__NR.setDisplayMode("Description")
    sdramcSym_CR__NR.setLabel("Number of Row Bits")
    count = ValGrp_CR__NR.getValueCount()
    for id in range(0,count):
        valueName = ValGrp_CR__NR.getValueNames()[id]
        sdramcSym_CR__NR.addKey(valueName, ValGrp_CR__NR.getValue(valueName).getValue(), ValGrp_CR__NR.getValue(valueName).getDescription())
    sdramcSym_CR__NR.setSelectedKey("ROW11",2)

    sdramcSym_CR__NC = sdramcComponent.createKeyValueSetSymbol("SDRAMC_CR__NC", sdramcSymMenu_features)
    sdramcSym_CR__NC.setOutputMode("Key")
    sdramcSym_CR__NC.setDisplayMode("Description")
    sdramcSym_CR__NC.setLabel("Number of Column Bits")
    count = ValGrp_CR__NC.getValueCount()
    for id in range(0,count):
        valueName = ValGrp_CR__NC.getValueNames()[id]
        sdramcSym_CR__NC.addKey(valueName, ValGrp_CR__NC.getValue(valueName).getValue(), ValGrp_CR__NC.getValue(valueName).getDescription())
    sdramcSym_CR__NC.setSelectedKey("COL8",2)

    sdramcSym_CR__NB = sdramcComponent.createKeyValueSetSymbol("SDRAMC_CR__NB", sdramcSymMenu_features)
    sdramcSym_CR__NB.setOutputMode("Key")
    sdramcSym_CR__NB.setDisplayMode("Description")
    sdramcSym_CR__NB.setLabel("Number of Banks")
    count = ValGrp_CR__NB.getValueCount()
    for id in range(0,count):
        valueName = ValGrp_CR__NB.getValueNames()[id]
        sdramcSym_CR__NB.addKey(valueName, ValGrp_CR__NB.getValue(valueName).getValue(), ValGrp_CR__NB.getValue(valueName).getDescription())
    sdramcSym_CR__NB.setSelectedKey("BANK2",2)

    sdramcSym_CR_DBW = sdramcComponent.createComboSymbol("SDRAMC_CR_DBW", sdramcSymMenu_features,ComboVal_CR_DBW)
    sdramcSym_CR_DBW.setLabel("Data Bus Width")
    sdramcSym_CR_DBW.setDefaultValue("16-bits")
    sdramcSym_CR_DBW.setReadOnly(True)

    # SDRAMC Timing Parameters
    sdramcSymMenu_TIMING_MENU = sdramcComponent.createMenuSymbol("SDRAMC_TIMING_MENU", None)
    sdramcSymMenu_TIMING_MENU.setLabel("Configure SDRAM Timing Parameters")

    sdramcSym_CR_TRCD = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TRCD", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_TRCD.setLabel("Row Active to Column Read/Write Delay (TRCD)")
    sdramcSym_CR_TRCD.setMin(0)
    sdramcSym_CR_TRCD.setMax(15)
    sdramcSym_CR_TRCD.setDefaultValue(SDRAMC_CR_TRCD_DEFAULT_VALUE)

    sdramcSym_CR_CAS = sdramcComponent.createIntegerSymbol("SDRAMC_CR_CAS", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_CAS.setLabel("CAS Latency (TCAS)")
    sdramcSym_CR_CAS.setMin(1)
    sdramcSym_CR_CAS.setMax(3)
    sdramcSym_CR_CAS.setDefaultValue(SDRAMC_CR_CAS_DEFAULT_VALUE)

    sdramcSym_CR_TRAS = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TRAS", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_TRAS.setLabel("Row Active to Precharge Delay(RAS)")
    sdramcSym_CR_TRAS.setMin(0)
    sdramcSym_CR_TRAS.setMax(15)
    sdramcSym_CR_TRAS.setDefaultValue(SDRAMC_CR_TRAS_DEFAULT_VALUE)

    sdramcSym_CR_TRP = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TRP", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_TRP.setLabel("Row Precharge Delay (TRP)")
    sdramcSym_CR_TRP.setMin(0)
    sdramcSym_CR_TRP.setMax(15)
    sdramcSym_CR_TRP.setDefaultValue(SDRAMC_CR_TRP_DEFAULT_VALUE)

    sdramcSym_CR_TRC_TRFC = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TRC_TRFC", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_TRC_TRFC.setLabel("Row Cycle Delay/Row Refresh Cycle(TRC_TRFC)")
    sdramcSym_CR_TRC_TRFC.setMin(0)
    sdramcSym_CR_TRC_TRFC.setMax(15)
    sdramcSym_CR_TRC_TRFC.setDefaultValue(SDRAMC_CR_TRC_TRFC_DEFAULT_VALUE)

    sdramcSym_CR_TWR = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TWR", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CR_TWR.setLabel("Write Recovery Delay (TWR)")
    sdramcSym_CR_TWR.setMin(0)
    sdramcSym_CR_TWR.setMax(15)
    sdramcSym_CR_TWR.setDefaultValue(SDARMC_CR_TWR_DEFAULT_VALUE)

    sdramcSym_CFR1_TMRD = sdramcComponent.createIntegerSymbol("SDRAMC_CFR1_TMRD", sdramcSymMenu_TIMING_MENU)
    sdramcSym_CFR1_TMRD.setLabel("Mode Register Set to Command Delay Time(TMRD)")
    sdramcSym_CFR1_TMRD.setMin(0)
    sdramcSym_CFR1_TMRD.setMax(15)
    sdramcSym_CFR1_TMRD.setDefaultValue(SDARMC_CFR1_TMRD_DEFAULT_VALUE)

    sdramcSym_REFRESH_TIME_IN_MS = sdramcComponent.createIntegerSymbol("SDRAMC_REFRESH_TIME_IN_MS", sdramcSymMenu_TIMING_MENU)
    sdramcSym_REFRESH_TIME_IN_MS.setLabel("Refresh time in ms")
    sdramcSym_REFRESH_TIME_IN_MS.setDefaultValue(SDRAMC_REFRESH_TIME_IN_MS_DEFAULT_VALUE)

    clk = int(Database.getSymbolValue("core", "MASTERCLK_FREQ"))
    count=calcRefreshCount(SDRAMC_REFRESH_TIME_IN_MS_DEFAULT_VALUE, "ROW11", clk)

    sdramcSym_SDRAMC_TR_COUNT = sdramcComponent.createIntegerSymbol("SDRAMC_TR_COUNT", sdramcSymMenu_TIMING_MENU)
    sdramcSym_SDRAMC_TR_COUNT.setDependencies(calcRefreshCount_CB, ["SDRAMC_REFRESH_TIME_IN_MS","core.MASTERCLK_FREQ"])
    sdramcSym_SDRAMC_TR_COUNT.setDefaultValue(count)
    sdramcSym_SDRAMC_TR_COUNT.setVisible(False)

    # SDRAMC Mode Configuration
    sdramcSymMenu_MR_MENU = sdramcComponent.createMenuSymbol("SDRAMC_MR_MENU", None)
    sdramcSymMenu_MR_MENU.setLabel("SDRAMC Mode Register Configurations")

    sdramcSym_BURST_LENGTH = sdramcComponent.createIntegerSymbol("SDRAMC_BURST_LENGTH", sdramcSymMenu_MR_MENU)
    sdramcSym_BURST_LENGTH.setLabel("Burst Length")
    sdramcSym_BURST_LENGTH.setMin(SDRAMC_DEFAULT_MIN_VALUE)
    sdramcSym_BURST_LENGTH.setMax(SDRAMC_BURST_LENGHT_MAX_VALUE)
    sdramcSym_BURST_LENGTH.setDefaultValue(SDRAMC_DEFAULT_MIN_VALUE)

    sdramcSym_BURST_TYPE = sdramcComponent.createComboSymbol("SDRAMC_BURST_TYPE", sdramcSymMenu_MR_MENU, ComboVal_BURST_TYPE)
    sdramcSym_BURST_TYPE.setLabel("Burst Type")
    sdramcSym_BURST_TYPE.setDefaultValue("SEQUENTIAL")

    sdramcSym_MRS = sdramcComponent.createHexSymbol("SDRAMC_MRS_VALUE", sdramcSymMenu_MR_MENU)
    sdramcSym_MRS.setDependencies(calcMRS, ["SDRAMC_BURST_TYPE", "SDRAMC_BURST_LENGTH", "SDRAMC_CR_CAS"])
    sdramcSym_MRS.setVisible(False)

    sdramcSym_EMRS = sdramcComponent.createHexSymbol("SDRAMC_EMRS_VALUE", sdramcSymMenu_MR_MENU)
    sdramcSym_EMRS.setDependencies(calcEMRS, ["SDRAMC_LPR_PASR", "SDRAMC_LPR_TCSR", "SDRAMC_LPR_DS"])
    sdramcSym_EMRS.setVisible(False)

    # Low-power configuration options.
    sdramcSymMenu_LOW_POW_MENU = sdramcComponent.createMenuSymbol("SDRAMC_LOW_POW_MENU", None)
    sdramcSymMenu_LOW_POW_MENU.setLabel("SDRAMC Low-Power Configurations")
    sdramcSymMenu_LOW_POW_MENU.setVisible(False)
    sdramcSymMenu_LOW_POW_MENU.setDependencies(lowPowerVisibility, ["SDRAMC_MDR_MD"])

    sdramcSym_CR_TXSR = sdramcComponent.createIntegerSymbol("SDRAMC_CR_TXSR", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_CR_TXSR.setLabel("Exit Self Refresh to Active Time (TXSR)")
    sdramcSym_CR_TXSR.setMin(0)
    sdramcSym_CR_TXSR.setMax(15)
    sdramcSym_CR_TXSR.setDefaultValue(SDARMC_CR_TXSR_DEFAULT_VALUE)

    sdramcSym_LPR_LPCB = sdramcComponent.createKeyValueSetSymbol("SDRAMC_LPR_LPCB", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_LPR_LPCB.setOutputMode("Key")
    sdramcSym_LPR_LPCB.setDisplayMode("Description")
    sdramcSym_LPR_LPCB.setLabel("Low Power Configuration")
    sdramcSym_LPR_LPCB.addKey("DISABLED", "0", "Low Power mode is disabled")
    sdramcSym_LPR_LPCB.addKey("SELF_REFRESH", "1", "Self Refresh")
    sdramcSym_LPR_LPCB.addKey("POWER_DOWN", "2", "Power down")
    sdramcSym_LPR_LPCB.addKey("DEEP_POWER_DOWN", "3", "Deep Power-Down")
    sdramcSym_LPR_LPCB.setSelectedKey("DISABLED",2)

    sdramcSym_LPR_TIMEOUT = sdramcComponent.createKeyValueSetSymbol("SDRAMC_LPR_TIMEOUT", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_LPR_TIMEOUT.setOutputMode("Key")
    sdramcSym_LPR_TIMEOUT.setDisplayMode("Description")
    sdramcSym_LPR_TIMEOUT.setLabel("Select Low Power Entry")
    sdramcSym_LPR_TIMEOUT.addKey("LP_LAST_XFER", "0", "After the end of the last transfer")
    sdramcSym_LPR_TIMEOUT.addKey("LP_LAST_XFER_64", "1", "64 clock cycles after the end of the last transfer")
    sdramcSym_LPR_TIMEOUT.addKey("LP_LAST_XFER_128", "2", "128 clock cycles after the end of the last transfer")

    sdramcSym_LPR_PASR = sdramcComponent.createIntegerSymbol("SDRAMC_LPR_PASR", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_LPR_PASR.setLabel("Partial Array Self-Refresh (PACR)")
    sdramcSym_LPR_PASR.setMin(0)
    sdramcSym_LPR_PASR.setMax(7)
    sdramcSym_LPR_PASR.setDefaultValue(0)

    sdramcSym_LPR_TCSR = sdramcComponent.createIntegerSymbol("SDRAMC_LPR_TCSR", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_LPR_TCSR.setLabel("Temperature Compensated Self-Refresh (TCSR)")
    sdramcSym_LPR_TCSR.setMin(0)
    sdramcSym_LPR_TCSR.setMax(3)
    sdramcSym_LPR_TCSR.setDefaultValue(0)

    sdramcSym_LPR_DS = sdramcComponent.createIntegerSymbol("SDRAMC_LPR_DS", sdramcSymMenu_LOW_POW_MENU)
    sdramcSym_LPR_DS.setLabel("Drive Strength (DS)")
    sdramcSym_LPR_DS.setMin(0)
    sdramcSym_LPR_DS.setMax(3)
    sdramcSym_LPR_DS.setDefaultValue(0)

    ############################################################################
    #### Dependency ####
    ############################################################################

    # Enable Peripheral Clock in Clock manager
    Database.clearSymbolValue("core", "PMC_ID_SDRAMC")
    Database.setSymbolValue("core", "PMC_ID_SDRAMC", True, 2)

############################################################################
#### Code Generation ####
############################################################################

    configName = Variables.get("__CONFIGURATION_NAME")

    sdramcHeader1File = sdramcComponent.createFileSymbol("SDRAMC_H", None)
    sdramcHeader1File.setSourcePath("../peripheral/sdramc_" + sdramcRegModule.getID() + "/templates/plib_sdramc.h.ftl")
    sdramcHeader1File.setOutputName("plib_sdramc" + str(instance) + ".h")
    sdramcHeader1File.setDestPath("/peripheral/sdramc/")
    sdramcHeader1File.setProjectPath("config/" + configName + "/peripheral/sdramc/")
    sdramcHeader1File.setType("HEADER")
    sdramcHeader1File.setMarkup(True)

    sdramcSource1File = sdramcComponent.createFileSymbol("SDRAMC_C", None)
    sdramcSource1File.setSourcePath("../peripheral/sdramc_" + sdramcRegModule.getID() + "/templates/plib_sdramc.c.ftl")
    sdramcSource1File.setOutputName("plib_sdramc" + str(instance) + ".c")
    sdramcSource1File.setDestPath("/peripheral/sdramc/")
    sdramcSource1File.setProjectPath("config/" + configName + "/peripheral/sdramc/")
    sdramcSource1File.setType("SOURCE")
    sdramcSource1File.setMarkup(True)

    #Add SDRAMC related code to common files
    sdramcHeader1FileEntry = sdramcComponent.createFileSymbol("SDRAMC_SYSTEM_DEFINITIONS_H", None)
    sdramcHeader1FileEntry.setType("STRING")
    sdramcHeader1FileEntry.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    sdramcHeader1FileEntry.setSourcePath("../peripheral/sdramc_" + sdramcRegModule.getID() + "/templates/system/system_definitions.h.ftl")
    sdramcHeader1FileEntry.setMarkup(True)

    sdramSystemInitFile = sdramcComponent.createFileSymbol("SDRAMC_SYSTEM_INITIALIZE_C", None)
    sdramSystemInitFile.setType("STRING")
    sdramSystemInitFile.setOutputName("core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_CORE")
    sdramSystemInitFile.setSourcePath("../peripheral/sdramc_" + sdramcRegModule.getID() + "/templates/system/system_initialize.c.ftl")
    sdramSystemInitFile.setMarkup(True)
