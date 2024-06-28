/* ADPD1080.c */

/* Include Files */
#include "project.h" // Include PSoC project header
#include "ADPD1080.h"
//#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Initialize data slot arrays */
volatile uint16_t au16DataSlotA[4] = {0,0,0,0};
volatile uint16_t au16DataSlotB[4] = {0,0,0,0};

/* Function definitions */
/**
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2cAddr
 *            The I2C address to be used.
 *    @param  sensorId
 *            The unique ID to differentiate the sensors from others
 *    @return True if initialization was successful, otherwise false.
 */
bool ADPD1080_Begin(uint8_t i2cAddr, int32_t sensorId) {
    (void) i2cAddr;
    (void) sensorId;
    
    uint16_t deviceID = ADPD1080_ReadReg(0x08);  // Device ID register
    printf("%d",deviceID);
    return true;
}

/**
 * @brief Writes a register from the ADPD1080 using I2C bus.
 * 
 * @param regAddr - register address
 * @param regValue - register data to write
 * 
 * @return true if successful - false if failure 
 */
bool ADPD1080_WriteReg(uint8_t regAddr, uint16_t regValue) {
    //uint8_t err;
    I2C_MasterSendStart(ADPD1080_ADDRESS, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(regAddr);
    I2C_MasterWriteByte((regValue >> 8) & 0xFF);
    I2C_MasterWriteByte(regValue & 0xFF);
    I2C_MasterSendStop();
    return true;
}

/**
 * @brief Reads a register from the ADPD1080 using I2C bus.
 * 
 * @param regAddr - register address
 * 
 * @return uint16_t - register value
 */
uint16_t ADPD1080_ReadReg(uint8_t regAddr) {
    uint8_t buffer[2] = {0};
    I2C_MasterSendStart(ADPD1080_ADDRESS, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(regAddr);
    I2C_MasterSendRestart(ADPD1080_ADDRESS, I2C_READ_XFER_MODE);
    buffer[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    buffer[1] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    return (buffer[0] << 8) | buffer[1];
}

/**
 * @brief Sets the operation mode of the ADPD1080
 * 
 * @param enMode = STANDBY, PROGRAM or NORMAL_OPERATION.
 * 
 * @return true if successful - false if failure
 */
bool ADPD1080_SetOperationMode(ADPD1080_OperationMode enMode) {
    uint16_t regValue = ADPD1080_ReadReg(0x10);
    bool success = false;
    if(enMode == 0){
        regValue = (regValue & 0xFFFC);//!!!!!!!!!!!!!!!!!!!!!1101
        success = ADPD1080_WriteReg(0x10, regValue);
    }
    else if(enMode == 1) {
        regValue = (regValue & 0xFFFC) | 0x01;//!!!!!!!!!!!!!!!!!!!!!1101
        success = ADPD1080_WriteReg(0x10, regValue);
    }
    else if(enMode == 2) {
        regValue = (regValue & 0xFFFC) | 0x02;//!!!!!!!!!!!!!!!!!!!!!1101
        success = ADPD1080_WriteReg(0x10, regValue);
    }
    return success;
}
/**
 * @brief Configure the Time Slot Switch register.
 *
 * @param u8SlotASel - SlotA input
 * 
 * @param u8SlotBSel - SlotB input
 * 
 * @return true if successful - false if failure 
 */
bool ADPD1080_SetTimeSlotSwitch(ADPD1080_TimeSlotPD u8SlotASel, ADPD1080_TimeSlotPD u8SlotBSel){
    uint16_t select_value = ADPD1080_ReadReg(0x14);
    select_value &= ~(0x0F << 4);        // Clear bits 4-7
    select_value |= (u8SlotASel << 4); // Set the new value for bits 4-7
    select_value &= ~(0x0F << 8);        // Clear bits 8-11
    select_value |= (u8SlotBSel << 8); // Set the new value for bits 8-11
    
    // Write the updated value back to the ADPD1080_PD_LED_SELECT register
    return ADPD1080_WriteReg(0x14, select_value);
}

/**
 * @brief Enable the internal 32kHz internal clock from ADPD105 via I2C.
 * 
 * @param enableSampleClk - enables/disables 32kHz clock
 *  
 * @return true if successful - false if failure 
 */
bool ADPD1080_Set32KCLK(bool enableSampleClk){
    uint16_t origin = ADPD1080_ReadReg(0x4B);
    uint16_t mask = (enableSampleClk << 7);
    uint16_t new = origin | mask;
    return ADPD1080_WriteReg(0x4B, new);
}

/**
 * @brief Setup FIFO for data reading
 * 
 * @param 
 *  
 * @return none
 * 
 * @remarks INT_MASK settings are a bit weird ... (see ADPD_1Sensor.ino code)
 */
void ADPD1080_SetFIFO(void) {
    // TODO
    ADPD1080_WriteReg(ADPD1080_SLOT_EN, 0x1021);
    ADPD1080_WriteReg(ADPD1080_FIFO_THRESH, 0x1F00);
    ADPD1080_WriteReg(ADPD1080_INT_MASK, 0xC0FF);
    ADPD1080_WriteReg(ADPD1080_GPIO_CTRL, 0x101);
    ADPD1080_WriteReg(ADPD1080_GPIO_DRV, 0x05);
}

/* Configure the Time Slot Switch register */
bool ADPD1080_SelectLED(ADPD1080_LED enLEDNumber, ADPD1080_TimeSlot enSlot) {
    (void) enLEDNumber;
    (void) enSlot;
    uint16_t regValue = ADPD1080_ReadReg(ADPD1080_PD_LED_SELECT);
    //if (enSlot == 0) { // SLOTA
        //regValue = regValue & (0xFFFD | enLEDNumber);//!!!!!!!!!!!!!!!!!!!!!1101
    //} else { // SLOTB
        //regValue = regValue & (0xFFFB | enLEDNumber << 2);//!!!!!!!!!!!!!!!!!!!!!1011
    //}
    regValue = (regValue & 0xFFF0) | 0x0009;//!!!!!!!!!!!!!!!!!!!!!1101
    return ADPD1080_WriteReg(ADPD1080_PD_LED_SELECT, regValue);
}

/* Set the width and offset for LED pulse */
bool ADPD1080_SetLEDWidthOffset(uint8_t enSlot, uint8_t u8Width, uint8_t u8Offset) {
    uint16_t regValue = u8Offset + ((u8Width & 0x1F) << 8);
    if (enSlot == 0) { // SLOTA
        return ADPD1080_WriteReg(ADPD1080_SLOTA_LED_PULSE, regValue);
    } else { // SLOTB
        return ADPD1080_WriteReg(ADPD1080_SLOTB_LED_PULSE, regValue);
    }
}

/* Set the transimpedance amplifier gain */
bool ADPD1080_SetTIAGain(uint8_t enSlot, uint16_t enTIAGain) {
    if (enSlot == 0) { // SLOTA
        return ADPD1080_WriteReg(ADPD1080_SLOTA_TIA_CFG, enTIAGain);
    } else { // SLOTB
        return ADPD1080_WriteReg(ADPD1080_SLOTB_TIA_CFG, enTIAGain);
    }
}

/* Set the sampling frequency */
bool ADPD1080_SetSamplingFrequency(uint16_t u16Frequency) {
    uint16_t u16FValue = 32000 / u16Frequency / 4;

    return ADPD1080_WriteReg(ADPD1080_FSAMPLE, u16FValue);
}

/* Set the average factor */
bool ADPD1080_SetAverageFactor(uint8_t enAverage) {
    uint16_t regValue = (enAverage << 4) | (enAverage << 8);

    return ADPD1080_WriteReg(ADPD1080_NUM_AVG, regValue);
}

/* Enable the digital clock */
bool ADPD1080_SetDigitalClock(void) {
    uint16_t origin = ADPD1080_ReadReg(0x4B);
    uint16_t new = origin | 0x1;
    ADPD1080_WriteReg(0x5F, new);
}

/* Software reset of the ADPD1080 */
bool ADPD1080_Reset(void) {
    return ADPD1080_WriteReg(ADPD1080_SW_RESET, 1);
}

/* Set channel offset */
void ADPD1080_SetOffset(uint8_t enSlot, uint16_t ch1Offset, uint16_t ch2Offset, uint16_t ch3Offset, uint16_t ch4Offset) {
    if (enSlot == 0) { // SLOTA
        ADPD1080_WriteReg(ADPD1080_SLOTA_CH1_OFFSET, ch1Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTA_CH2_OFFSET, ch2Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTA_CH3_OFFSET, ch3Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTA_CH4_OFFSET, ch4Offset);
    } else { // SLOTB
        ADPD1080_WriteReg(ADPD1080_SLOTB_CH1_OFFSET, ch1Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTB_CH2_OFFSET, ch2Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTB_CH3_OFFSET, ch3Offset);
        ADPD1080_WriteReg(ADPD1080_SLOTB_CH4_OFFSET, ch4Offset);
    }
}

/* Disable the LEDs */
bool ADPD1080_DisableLed(uint8_t enSlot) {
    uint16_t regValue = ADPD1080_ReadReg(ADPD1080_LED_DISABLE);
    (void) enSlot;
    //if (enSlot == 0) { // SLOTA
        //regValue = regValue & (0xFCFF | (0x01 << 8));//!!!!!!!!!!!!!!!!!!!!! 8 bit 1
        //return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
    //} else { // SLOTB
        //regValue = regValue & (0xFCFF | (0x01 << 9));//!!!!!!!!!!!!!!!!!!!!!9 bit 1
        //return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
    //}
    regValue = (regValue & 0xFCFF) | (0x0300);//!!!!!!!!!!!!!!!!!!!!! 8 bit 1
    return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
}

/* Enable the LEDs */
bool ADPD1080_EnableLed(uint8_t enSlot) {
    (void) enSlot;
    uint16_t regValue = ADPD1080_ReadReg(ADPD1080_LED_DISABLE);
    //if (enSlot == 0) { // SLOTA
        //regValue = regValue & (0xFCFF | (0x00 << 8));//!!!!!!!!!!!!!!!!!!!!!8 bit 0
        //return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
    //} else { // SLOTB
        //regValue = regValue & (0xFCFF | (0x00 << 9));//!!!!!!!!!!!!!!!!!!!!!9 bit 0
        //return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
    //}
    regValue = (regValue & 0xFCFF);//!!!!!!!!!!!!!!!!!!!!! 8 bit 1
    return ADPD1080_WriteReg(ADPD1080_LED_DISABLE, regValue);
}

/* Set the pulse number and period */
bool ADPD1080_SetPulseNumberPeriod(uint8_t enSlot, uint8_t u8PulseCount, uint8_t u8PulsePeriod) {
    uint16_t u16Value = ((uint16_t)u8PulseCount << 8) | u8PulsePeriod;

    if (enSlot == 0) { // SLOTA
        return ADPD1080_WriteReg(ADPD1080_SLOTA_NUMPULSES, u16Value);
    } else { // SLOTB
        return ADPD1080_WriteReg(ADPD1080_SLOTB_NUMPULSES, u16Value);
    }
}

void ADPD1080_ReadData(volatile uint16_t *data_Slot_A, volatile uint16_t *data_Slot_B, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        data_Slot_A[i] = ADPD1080_ReadReg(0x64 + i);
        data_Slot_B[i] = ADPD1080_ReadReg(0x68 + i);
    }
}

void turbidity_init(void) {
    
    ADPD1080_SetOperationMode(0x01);  // Set to program mode
    ADPD1080_WriteReg(0x0,0xFF);
    ADPD1080_WriteReg(0x0F, 0x01);    // Reset
    
    ADPD1080_SetOperationMode(0x01);  // Set to program mode
    ADPD1080_Set32KCLK(1);            // Enable 32K clock
    ADPD1080_SetTimeSlotSwitch(0x5, 0x5);
  /* Select LEDs for each time slot */
    ADPD1080_SelectLED(0x02, 0x0);
    //ADPD1080_SelectLED(0x01, 0x1);
    
    ADPD1080_WriteReg(0x24, 0x1004);  // LED configuration
    ADPD1080_WriteReg(0x23, 0x1000);  // LED configuration
    ADPD1080_WriteReg(0x25, 0x67DF);  // LED fine

    ADPD1080_WriteReg(0x31, 0x1019);  // Pulse number and period
    ADPD1080_WriteReg(0x36, 0x1019);  // Pulse number and period

    ADPD1080_WriteReg(0x30, 0x0220);  // LED width and offset
    ADPD1080_WriteReg(0x35, 0x0220);  // LED width and offset

    ADPD1080_WriteReg(0x39, 0x1AE0);  // AFE width and offset
    ADPD1080_WriteReg(0x3B, 0x1AE0);  // AFE width and offset

    //ADPD1080_WriteReg(0x4E, 0x40);  // ADC clock
    //ADPD1080_WriteReg(0x58, 0x01);    // Digital clock

    ADPD1080_WriteReg(0x12, 0x5);     // Sampling frequency
    
    ADPD1080_WriteReg(0x42, 0x1C37);  // TIA gain
    ADPD1080_WriteReg(0x44, 0x1C37);  // TIA gain

    ADPD1080_WriteReg(0x4B, 0x2695);  // Sample clock
    ADPD1080_WriteReg(0x4D, 0x0098);  // Adjust clock
    ADPD1080_WriteReg(0x4F, 0x2090);  // External sync
    ADPD1080_WriteReg(0x50, 0x0000);  // Calibration

    ADPD1080_WriteReg(0x3C, 0x7006);  // AFE power configuration
    // FIFO setup
    ADPD1080_WriteReg(0x11, 0x3131); 
    ADPD1080_WriteReg(0x06, 0x1F00);
    ADPD1080_WriteReg(0x01, 0xC0FF);
    ADPD1080_WriteReg(0x0B, 0x101);
    ADPD1080_WriteReg(0x02, 0x05);
    
    ADPD1080_SetOperationMode(0x02);  // Set to normal operation
}

void turbidity_ChannelOffsetCalibration(void) {
    ADPD1080_SetOperationMode(0x01);  // Set to program mode
    // ADPD1080_WriteReg(0x34, 0x0100);  // Disable LED
    // ADPD1080_WriteReg(0x34, 0x0100);  // Disable LED/////////
    //uint16_t reg34Value = ADPD1080_ReadReg(0x34);
    //reg34Value |= 0x0300;
    //ADPD1080_WriteReg(0x34, reg34Value);  // Disable LED/////////
    ADPD1080_DisableLed(0);
    //ADPD1080_DisableLed(1);

    //ADPD1080_WriteReg(0x18, 0x2078);  // Channel offset////////////////
    //ADPD1080_WriteReg(0x19, 0x0000);  // Channel offset
    //ADPD1080_WriteReg(0x1A, 0x0000);  // Channel offset
    //ADPD1080_WriteReg(0x1B, 0x0000);  // Channel offset

    //ADPD1080_WriteReg(0x1E, 0x2078);  // Channel offset
    //ADPD1080_WriteReg(0x1F, 0x0000);  // Channel offset
    //ADPD1080_WriteReg(0x20, 0x0000);  // Channel offset
    //ADPD1080_WriteReg(0x21, 0x0000);  // Channel offset

    ADPD1080_WriteReg(0x31, 0x1019);  // Pulse number and period/////////////////
    ADPD1080_WriteReg(0x36, 0x1019);  // Pulse number and period////////////////////

    ADPD1080_SetOperationMode(0x02);  // Set to normal operation
    CyDelay(1000);

    ADPD1080_ReadData(au16DataSlotA, au16DataSlotB, 4);////////////////

    ADPD1080_SetOperationMode(0x01);  // Set to program mode
    //ADPD1080_WriteReg(0x18, au16DataSlotA[0] - 100);  // Set offset for slot A
    //ADPD1080_WriteReg(0x1E, au16DataSlotB[0] - 100);  // Set offset for slot B
    
    ADPD1080_EnableLed(0);
    //ADPD1080_EnableLed(1);

    //reg34Value = ADPD1080_ReadReg(0x34);
    //reg34Value |= 0x0000;
    //ADPD1080_WriteReg(0x34, reg34Value);  // Enable LED
    //ADPD1080_WriteReg(0x34, 0x0300);  // Enable LED

    ADPD1080_SelectLED(0x02, 0x0);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //ADPD1080_SelectLED(0x01, 0x1);//????????????
    
    //uint16_t reg14Value = ADPD1080_ReadReg(0x14);
    //reg14Value = (reg14Value & 0xFCFF) | 0x0300;//!!!!!!!!!!!!!!!!!!!!!!!
    //ADPD1080_WriteReg(0x14, reg14Value);
    //ADPD1080_WriteReg(0x14, 0x0002);//??????????????????????????
    // ADPD1080_WriteReg(0x14, 0x000F);////////

    ADPD1080_WriteReg(0x31, 0x1019);  // Pulse number and period/////////////////
    ADPD1080_WriteReg(0x36, 0x1019);  // Pulse number and period////////////////////

    ADPD1080_WriteReg(0x15, 0x0110); //?//////////////////

    ADPD1080_SetOperationMode(0x02);  // Set to normal operation
}