"""*****************************************************************************
* Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
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

################################################################################
#### Register Information ####
################################################################################
tmr1BitField_T1CON_SIDL = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="T1CON"]/bitfield@[name="SIDL"]')
tmr1ValGrp_T1CON_SIDL = ATDF.getNode("/avr-tools-device-file/modules/module@[name=\"TMR1\"]/value-group@[name=\"T1CON__SIDL\"]")

tmr1BitField_T1CON_ON = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="T1CON"]/bitfield@[name="ON"]')
tmr1ValGrp_T1CON_ON = ATDF.getNode("/avr-tools-device-file/modules/module@[name=\"TMR1\"]/value-group@[name=\"T1CON__ON\"]")

tmr1BitField_T1CON_PRESCALER = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="T1CON"]/bitfield@[name="TCKPS"]')
tmr1ValGrp_T1CON_PRESCALER = ATDF.getNode("/avr-tools-device-file/modules/module@[name=\"TMR1\"]/value-group@[name=\"T1CON__TCKPS\"]")

tmr1BitField_T1CON_TCS = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="T1CON"]/bitfield@[name="TCS"]')
tmr1ValGrp_T1CON_TCS = ATDF.getNode("/avr-tools-device-file/modules/module@[name=\"TMR1\"]/value-group@[name=\"T1CON__TCS\"]")

tmr1BitField_PR1_BITS = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="PR1"]')

tmr1BitField_T1CON_TSYNC = ATDF.getNode('/avr-tools-device-file/modules/module@[name="TMR1"]/register-group@[name="TMR1"]/register@[name="T1CON"]/bitfield@[name="TSYNC"]')
tmr1ValGrp_T1CON_TSYNC = ATDF.getNode("/avr-tools-device-file/modules/module@[name=\"TMR1\"]/value-group@[name=\"T1CON__TSYNC\"]")

#######################################
###### Business Logic ####
#########################################
def enableMenu(menu, event):
	menu.setVisible(event["value"])
    
def _get_enblReg_parms(vectorNumber):
    # This takes in vector index for interrupt, and returns the IECx register name as well as
    # mask and bit location within it for given interrupt
    if(("PIC32MZ" in Variables.get("__PROCESSOR")) and ("EF" in Variables.get("__PROCESSOR"))):
        index = int(vectorNumber/32)
        bitPosn = int(vectorNumber%32)
        bitMask = hex(1<<bitPosn)
        regName = "IEC"+str(index)
        return regName, str(bitPosn), str(bitMask)
        
def _get_statReg_parms(vectorNumber):
    # This takes in vector index for interrupt, and returns the IFSx register name as well as
    # mask and bit location within it for given interrupt
    if(("PIC32MZ" in Variables.get("__PROCESSOR")) and ("EF" in Variables.get("__PROCESSOR"))):
        index = int(vectorNumber/32)
        bitPosn = int(vectorNumber%32)
        bitMask = hex(1<<bitPosn)
        regName = "IFS"+str(index)
        return regName, str(bitPosn), str(bitMask)        

def _get_sub_priority_parms(vectorNumber):
    # This returns the IPCx register name, priority bit shift, priority mask, subpriority bit shift, 
    # and subpriority bitmask for input vector number
    if(("PIC32MZ" in Variables.get("__PROCESSOR")) and ("EF" in Variables.get("__PROCESSOR"))):
        index = int(vectorNumber/4)
        subPrioBit = 8*(vectorNumber & 0x3)
        subPrioMask = 0x3  # always 2 bits
        prioMask = 0x7
        prioBit = subPrioBit + 2
        regName = "IPC"+str(index)
    return regName, str(prioBit), str(prioMask), str(subPrioBit), str(subPrioMask)
    
def _get_bitfield_names(node, outputList):
    valueNodes = node.getChildren()
    for ii in valueNodes:   # do this for all <value > entries for this bitfield
        dict = {}
        if(ii.getAttribute('caption').lower() != "reserved"):  # skip (unused) reserved fields
            dict['desc'] = ii.getAttribute('caption')
            dict['key'] = ii.getAttribute('caption')
            
            # Get rid of leading '0x', and convert to int if was hex
            value = ii.getAttribute('value')
            if(value[:2]=='0x'):
                temp = value[2:]
                tempint = int(temp,16)
            else:
                tempint = int(value)
            dict['value'] = str(tempint)
            outputList.append(dict)

def getIRQnumber(string):
    interrupts = ATDF.getNode('/avr-tools-device-file/devices/device/interrupts')
    interruptsChildren = interrupts.getChildren()
    for param in interruptsChildren:  
        modInst = param.getAttribute('module-instance')
        if(string == modInst):
            irq_index = param.getAttribute('index')
            break
    return irq_index
    
###################################################################################################
########################################## Callbacks  #############################################
###################################################################################################

def dependencyStatus(symbol, event):
    if (event["value"] == False):
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)
        
def dependencyInterrupt(symbol, event):
    if (event["value"] == False):
        symbol.setValue(0,1)
    else:
        symbol.setValue(1,1)

def updateIntPSValues(symbol, event):
    psvalue = int(event["value"])
    symbol.setValue(psvalue, 1)

def updateHandlerName(symbol, event):
    handlername = str(event["value"])
    symbol.setValue(handlername, 1)     

def combinetmr1IPC_Values(symbol, event):
    global tmr1VectorNum
    pr, ps, pm, sps, spm = _get_sub_priority_parms(tmr1VectorNum)
    ipc = symbol.getValue()
    if(event["id"] == "TMR1_IPC_PRI_VALUE"):
        ipcPriValue = int(event["symbol"].getValue())
        ipc = ipc & ~((int(pm))<< (int(ps)))
        ipc = ipc | (ipcPriValue<<(int (ps)))

    if(event["id"] == "TMR1_IPC_SUBPRI_VALUE"):
        ipcSPriValue = int(event["symbol"].getValue())
        ipc = ipc & ~((int(spm))<< (int(sps)))
        ipc = ipc | (ipcSPriValue<<(int (sps)))
    symbol.setValue(ipc, 2)

def timerModeMax(symbol,event):
    if ((int(event["symbol"].getKeyValue(event["value"]))) == 1):
        symbol.setMax(4294967295)
    else:
        symbol.setMax(65535)

def T1CONcombineValues(symbol, event):
    t1conValue = symbol.getValue()
    if(event["id"] == "TIMER1_SIDL"):
        sidlValue = int(event["symbol"].getKeyValue(event["value"]))
        maskvalue = tmr1BitField_T1CON_SIDL.getAttribute("mask")
        t1conValue = t1conValue & (~int (maskvalue,0))
        t1conValue = t1conValue | (sidlValue<<13)
    if(event["id"] == "TIMER1_PRE_SCALER"):
        prescalerValue = int(event["symbol"].getKeyValue(event["value"])) 
        maskvalue = tmr1BitField_T1CON_PRESCALER.getAttribute("mask")
        t1conValue = t1conValue & (~int (maskvalue,0))
        t1conValue = t1conValue | (prescalerValue<<4) 
    if(event["id"] == "TIMER1_TSYNC_SEL"):
        tsyncValue = int(event["symbol"].getKeyValue(event["value"])) 
        maskvalue = tmr1BitField_T1CON_TSYNC.getAttribute("mask")
        t1conValue = t1conValue & (~int (maskvalue,0)) 
        t1conValue  =  t1conValue | (tsyncValue<<3)    
    if(event["id"] == "TIMER1_SRC_SEL"):
        tmr1SrcSelValue = int(event["symbol"].getKeyValue(event["value"]))
        maskvalue = tmr1BitField_T1CON_TCS.getAttribute("mask")
        t1conValue = t1conValue & (~int (maskvalue,0))
        t1conValue  = t1conValue | (tmr1SrcSelValue <<1) 
    symbol.setValue(t1conValue, 2)

global PrescalerDict
PrescalerDict = {
                    "1:256 prescale value": 256,
                    "1:64 prescale value" : 64,
                    "1:8 prescale value"  : 8,
                    "1:1 prescale value"  : 1,
                }

def PreScaler_ValueUpdate(symbol, event):
    symbol.setValue(PrescalerDict[event["symbol"].getKey(event["value"])],1)
   # symbol.setMax(PrescalerDict[event["symbol"].getKey(event["value"])])

###################################################################################################
########################################## Component  #############################################
###################################################################################################

def instantiateComponent(tmr1Component):

    global tmr1VectorNum
    tmr1InstanceName = tmr1Component.createStringSymbol("TMR1_INSTANCE_NAME", None)
    tmr1InstanceName.setVisible(False)
    tmr1InstanceName.setDefaultValue(tmr1Component.getID().upper())
    Log.writeInfoMessage("Running " + tmr1InstanceName.getValue())
    
    tmr1InstanceNum = tmr1Component.createStringSymbol("TMR1_INSTANCE_NUM", None)
    tmr1InstanceNum.setVisible(False)
    instanceNum = filter(str.isdigit,str(tmr1Component.getID()))
    tmr1InstanceNum.setDefaultValue(instanceNum)
    
    tmr1Irq = "TIMER_" + str(instanceNum)
    tmr1VectorNum = int(getIRQnumber(tmr1Irq))
    enblRegName, enblBitPosn, enblMask = _get_enblReg_parms(tmr1VectorNum)
    statRegName, statBitPosn, statMask = _get_statReg_parms(tmr1VectorNum)
    prioRegName, prioShift, prioMask, subprioShift, subprioMask = _get_sub_priority_parms(tmr1VectorNum)

    #IEC REG
    tmr1IEC = tmr1Component.createStringSymbol("TMR1_IEC_REG", None)
    tmr1IEC.setDefaultValue(enblRegName)
    tmr1IEC.setVisible(False)

    #IFS REG
    tmr1IFS = tmr1Component.createStringSymbol("TMR1_IFS_REG", None)
    tmr1IFS.setDefaultValue(statRegName)
    tmr1IFS.setVisible(False)

    #IPC REG
    tmr1IPC = tmr1Component.createStringSymbol("TMR1_IPC_REG", None)
    tmr1IPC.setDefaultValue(prioRegName)
    tmr1IPC.setVisible(False)

    #PRIORITY VALUE
    tmr1VectorPriSym = "NVIC_" + str(tmr1VectorNum) + "_0_PRIORITY"
    tmr1priValue = Database.getSymbolValue("core",tmr1VectorPriSym)
    tmr1IPC_PriValue = tmr1Component.createHexSymbol("TMR1_IPC_PRI_VALUE", None)
    tmr1IPC_PriValue.setDefaultValue(int(tmr1priValue))
    tmr1IPC_PriValue.setVisible(False)
    tmr1IPC_PriValue.setDependencies(updateIntPSValues, ["core." + tmr1VectorPriSym])

    #SUBPRIORITY VALUE

    tmr1VectorSubPriSym = "TIMER_" + str(instanceNum) + "_SUBPRIORITY"
    tmr1subpriValue = Database.getSymbolValue("core",tmr1VectorSubPriSym)
    tmr1IPC_SubpriValue = tmr1Component.createHexSymbol("TMR1_IPC_SUBPRI_VALUE", None)
    tmr1IPC_SubpriValue.setDefaultValue(int(tmr1subpriValue))
    tmr1IPC_SubpriValue.setVisible(False)
    tmr1IPC_SubpriValue.setDependencies(updateIntPSValues, [ tmr1VectorSubPriSym])

    #IPC REG VALUE
    tmr1IPC_Val = tmr1Component.createHexSymbol("TMR1_IPC_VALUE", None)
    tmr1IPC_Val.setDefaultValue((int (tmr1IPC_PriValue.getDefaultValue()) << int(prioShift)) + (int (tmr1IPC_SubpriValue.getDefaultValue()) << int(subprioShift)))
    tmr1IPC_Val.setVisible(False)    
    tmr1IPC_Val.setDependencies(combinetmr1IPC_Values, ["TMR1_IPC_PRI_VALUE"])
    tmr1IPC_Val.setDependencies(combinetmr1IPC_Values, ["TMR1_IPC_SUBPRI_VALUE"])

    #HANDLER NAME
    tmr1VectorHandlerSym = "NVIC_" + str(tmr1VectorNum) + "_0_HANDLER"
    tmr1handlerValue = Database.getSymbolValue("core",tmr1VectorHandlerSym)
    tmr1IPC_handlerStr = tmr1Component.createStringSymbol("TMR1_ISR_HANDLER_NAME", None)
    tmr1IPC_handlerStr.setDefaultValue(tmr1handlerValue)
    tmr1IPC_handlerStr.setVisible(False)
    tmr1IPC_handlerStr.setDependencies(updateHandlerName, ["core." + tmr1VectorHandlerSym])   

    #timer SIDL configuration      
    sidl_names = []
    _get_bitfield_names(tmr1ValGrp_T1CON_SIDL, sidl_names)
    tmr1SymField_T1CON_SIDL = tmr1Component.createKeyValueSetSymbol( "TIMER1_SIDL",None)  
    tmr1SymField_T1CON_SIDL.setLabel(tmr1BitField_T1CON_SIDL.getAttribute("caption"))
    tmr1SymField_T1CON_SIDL.setOutputMode( "Value" )
    tmr1SymField_T1CON_SIDL.setDisplayMode( "Description" )
    for ii in sidl_names:
        tmr1SymField_T1CON_SIDL.addKey( ii['key'],ii['value'], ii['desc'] )
    tmr1SymField_T1CON_SIDL.setDefaultValue(1)
    tmr1SymField_T1CON_SIDL.setVisible(True)

    #timer on off configuration      
    on_names = []
    _get_bitfield_names(tmr1ValGrp_T1CON_ON, on_names)
    tmr1Sym_T1CON_ON = tmr1Component.createKeyValueSetSymbol( "TIMER1_START",None)  
    tmr1Sym_T1CON_ON.setLabel(tmr1BitField_T1CON_ON.getAttribute("caption"))
    tmr1Sym_T1CON_ON.setOutputMode( "Value" )
    tmr1Sym_T1CON_ON.setDisplayMode( "Description" )
    for ii in on_names:
        tmr1Sym_T1CON_ON.addKey( ii['key'],ii['value'], ii['desc'] )
    tmr1Sym_T1CON_ON.setDefaultValue(1)
    tmr1Sym_T1CON_ON.setVisible(False)
        
    #prescaler configuration
    prescale_names = []
    _get_bitfield_names(tmr1ValGrp_T1CON_PRESCALER, prescale_names)
    tmr1Sym_T1CON_PRESCALER = tmr1Component.createKeyValueSetSymbol("TIMER1_PRE_SCALER", None)
    tmr1Sym_T1CON_PRESCALER.setLabel(tmr1BitField_T1CON_PRESCALER.getAttribute("caption"))   
    tmr1Sym_T1CON_PRESCALER.setOutputMode("Value")
    tmr1Sym_T1CON_PRESCALER.setDisplayMode("Description")
    for ii in prescale_names:
        tmr1Sym_T1CON_PRESCALER.addKey( ii['desc'], ii['value'], ii['key'] )
    tmr1Sym_T1CON_PRESCALER.setDefaultValue(0)
    tmr1Sym_T1CON_PRESCALER.setVisible(False)

    #Prescaler Value
    tmr1PrescalerValue = tmr1Component.createIntegerSymbol("TMR1_PRESCALER_VALUE", None)
    tmr1PrescalerValue.setVisible(False)
    tmr1PrescalerValue.setLabel("Prescaler Value")
    tmr1PrescalerValue.setDescription("Timer1 Prescaler value")
    tmr1PrescalerValue.setDefaultValue(256)
    tmr1PrescalerValue.setMin(1)
    tmr1PrescalerValue.setDependencies(PreScaler_ValueUpdate, ["TIMER1_PRE_SCALER"])

     #Timer External sync selection bits
    tsync_names = []
    _get_bitfield_names(tmr1ValGrp_T1CON_TSYNC, tsync_names)
    tmr1Sym_T1CON_SYNC_SEL = tmr1Component.createKeyValueSetSymbol("TIMER1_TSYNC_SEL", None)
    tmr1Sym_T1CON_SYNC_SEL.setLabel(tmr1BitField_T1CON_TSYNC.getAttribute("caption")) 
    tmr1Sym_T1CON_SYNC_SEL.setOutputMode("Value")
    tmr1Sym_T1CON_SYNC_SEL.setDisplayMode("Description")
    for ii in tsync_names:
        tmr1Sym_T1CON_SYNC_SEL.addKey( ii['desc'], ii['value'], ii['key'] )
    tmr1Sym_T1CON_SYNC_SEL.setDefaultValue(0)
    tmr1Sym_T1CON_SYNC_SEL.setVisible(True)

    #Timer1 clock Source Slection configuration
    tcs_names = []
    _get_bitfield_names(tmr1ValGrp_T1CON_TCS, tcs_names)
    tmr1Sym_T1CON_SOURCE_SEL = tmr1Component.createKeyValueSetSymbol("TIMER1_SRC_SEL", None)
    tmr1Sym_T1CON_SOURCE_SEL.setLabel(tmr1BitField_T1CON_TCS.getAttribute("caption"))    
    tmr1Sym_T1CON_SOURCE_SEL.setOutputMode("Value")
    tmr1Sym_T1CON_SOURCE_SEL.setDisplayMode("Description")
    for ii in tcs_names:
        tmr1Sym_T1CON_SOURCE_SEL.addKey( ii['desc'], ii['value'], ii['key'] )
    tmr1Sym_T1CON_SOURCE_SEL.setDefaultValue(1)
    tmr1Sym_T1CON_SOURCE_SEL.setVisible(True)

    #Timer1 TxCON Reg Value
    tmr1Sym_T1CON_Value = tmr1Component.createHexSymbol("TCON_REG_VALUE",None)
    tmr1Sym_T1CON_Value.setDefaultValue((int(tmr1SymField_T1CON_SIDL.getSelectedValue())<<13) | (int (tmr1Sym_T1CON_PRESCALER.getSelectedValue())<<4) \
    | (int(tmr1Sym_T1CON_SYNC_SEL.getSelectedValue())<<3) | (int(tmr1Sym_T1CON_SOURCE_SEL.getSelectedValue())<<1))
    tmr1Sym_T1CON_Value.setVisible(False)
    tmr1Sym_T1CON_Value.setDependencies(T1CONcombineValues,["TIMER1_SIDL"])
    tmr1Sym_T1CON_Value.setDependencies(T1CONcombineValues,["TIMER1_PRE_SCALER"])
    tmr1Sym_T1CON_Value.setDependencies(T1CONcombineValues,["TIMER1_TSYNC_SEL"])
    tmr1Sym_T1CON_Value.setDependencies(T1CONcombineValues,["TIMER1_SRC_SEL"]) 
 
   #Timer1 Period Register
    tmr1Sym_PR1 = tmr1Component.createLongSymbol("TIMER1_PERIOD", None)
    tmr1Sym_PR1.setLabel(tmr1BitField_PR1_BITS.getAttribute("caption"))
    # 16 bit mode
    if((tmr1Sym_T1CON_SYNC_SEL.getSelectedValue) == 0):
        tmr1Sym_PR1.setDefaultValue(64000)
        tmr1Sym_PR1.setMin(0)
        tmr1Sym_PR1.setMax(65535)  
        tmr1Sym_PR1.setVisible(True)
    #32 bit mode
    else:
        tmr1Sym_PR1.setDefaultValue(64000) 
        tmr1Sym_PR1.setMin(0)
        tmr1Sym_PR1.setMax(4294967295) 
        tmr1Sym_PR1.setVisible(True)
    tmr1Sym_PR1.setDependencies(timerModeMax,["TIMER1_32BIT_MODE_SEL"])
    # ############################################################################
    # #### Dependency ####
    # ############################################################################
    ## MIPS Interrupt Dynamic settings
    tmr1interruptEnable = tmr1Component.createBooleanSymbol("TMR1_INTERRUPT_ENABLE", None)
    tmr1interruptEnable.setVisible(False)
    
    ## Fault Default Values
    tmr1VectorEnableSym = "NVIC_" + str(tmr1VectorNum) + "_0_ENABLE"
    tmr1SymIntEnComment = tmr1Component.createCommentSymbol("TMR1_INTR_ENABLE_COMMENT", None)
    if(Database.getSymbolValue("core", tmr1VectorEnableSym) == False):
        tmr1SymIntEnComment.setVisible(True)
        tmr1interruptEnable.setDefaultValue(False)
    else:    
        tmr1SymIntEnComment.setVisible(False)
        tmr1interruptEnable.setDefaultValue(True) 

      ## Fault Dependency   
    tmr1SymIntEnComment.setLabel("Warning!!! TIMER" + str(instanceNum) + " Interrupt is Disabled in Interrupt Manager")
    tmr1interruptEnable.setDependencies(dependencyInterrupt, ["core." + tmr1VectorEnableSym])
    tmr1SymIntEnComment.setDependencies(dependencyStatus, ["core." + tmr1VectorEnableSym])
  
    # ###################################################################################################
    # ####################################### Code Generation  ##########################################
    # ###################################################################################################

    configName = Variables.get("__CONFIGURATION_NAME")
    
    tmr1HeaderFile = tmr1Component.createFileSymbol("TMR1_COMMON_HEADER", None)
    tmr1HeaderFile.setSourcePath("../peripheral/tmr1_00687/templates/plib_tmr1_common.h")
    tmr1HeaderFile.setOutputName("plib_tmr1_common.h")
    tmr1HeaderFile.setDestPath("peripheral/tmr1/")
    tmr1HeaderFile.setProjectPath("config/" + configName + "/peripheral/tmr1/")
    tmr1HeaderFile.setType("HEADER")
    tmr1HeaderFile.setMarkup(False)
    tmr1HeaderFile.setOverwrite(True)   
    
    # Instance Header File
    tmr1HeaderFile = tmr1Component.createFileSymbol("TMR1_HEADER", None)
    tmr1HeaderFile.setSourcePath("../peripheral/tmr1_00687/templates/plib_tmr1.h.ftl")
    tmr1HeaderFile.setOutputName("plib_"+tmr1InstanceName.getValue().lower()+".h")
    tmr1HeaderFile.setDestPath("/peripheral/tmr1/")
    tmr1HeaderFile.setProjectPath("config/" + configName + "/peripheral/tmr1/")
    tmr1HeaderFile.setType("HEADER")
    tmr1HeaderFile.setMarkup(True)
    tmr1HeaderFile.setOverwrite(True)
    
    # Instance Source File
    tmr1SourceFile = tmr1Component.createFileSymbol("TMR1_SOURCE", None)
    tmr1SourceFile.setSourcePath("../peripheral/tmr1_00687/templates/plib_tmr1.c.ftl")
    tmr1SourceFile.setOutputName("plib_"+tmr1InstanceName.getValue().lower()+".c")
    tmr1SourceFile.setDestPath("/peripheral/tmr1/")
    tmr1SourceFile.setProjectPath("config/" + configName + "/peripheral/tmr1/")
    tmr1SourceFile.setType("SOURCE")
    tmr1SourceFile.setMarkup(True)
    tmr1SourceFile.setOverwrite(True)
    
    
    tmr1Sym_SystemInitFile = tmr1Component.createFileSymbol("TMR1_SYS_INT", None)
    tmr1Sym_SystemInitFile.setType("STRING")
    tmr1Sym_SystemInitFile.setOutputName("core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_PERIPHERALS")
    tmr1Sym_SystemInitFile.setSourcePath("../peripheral/tmr1_00687/templates/system/system_initialize.c.ftl")
    tmr1Sym_SystemInitFile.setMarkup(True)

    tmr1Sym_SystemDefFile = tmr1Component.createFileSymbol("TMR1_SYS_DEF", None)
    tmr1Sym_SystemDefFile.setType("STRING")
    tmr1Sym_SystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    tmr1Sym_SystemDefFile.setSourcePath("../peripheral/tmr1_00687/templates/system/system_definitions.h.ftl")
    tmr1Sym_SystemDefFile.setMarkup(True)
