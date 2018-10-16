
#pragma config NVMCTRL_BOOTPROT = SIZE_${DEVICE_NVMCTRL_BOOTPROT}BYTES
#pragma config NVMCTRL_EEPROM_SIZE = SIZE_${DEVICE_NVMCTRL_EEPROM_SIZE}BYTES
#pragma config BODVDDUSERLEVEL = 0x${DEVICE_BODVDDUSERLEVEL} // Enter Hexadecimal value
#pragma config BODVDD_DIS = ${DEVICE_BODVDD_DISABLE}
#pragma config BODVDD_ACTION = ${DEVICE_BODVDD_ACTION}

#pragma config BODVDD_HYST = ${DEVICE_BODVDD_HYST}
#pragma config NVMCTRL_REGION_LOCKS = 0x${DEVICE_NVMCTRL_REGION_LOCK} // Enter Hexadecimal value

#pragma config WDT_ENABLE = ${DEVICE_WDT_ENABLE}
#pragma config WDT_ALWAYSON = ${DEVICE_WDT_ALWAYSON}
#pragma config WDT_PER = ${DEVICE_WDT_PER}

#pragma config WDT_WINDOW = ${DEVICE_WDT_WINDOW}
#pragma config WDT_EWOFFSET = ${DEVICE_WDT_EWOFFSET}
#pragma config WDT_WEN = ${DEVICE_WDT_WEN}