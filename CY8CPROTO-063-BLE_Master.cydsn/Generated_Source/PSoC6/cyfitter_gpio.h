/*******************************************************************************
* File Name: cyfitter_gpio.h
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_GPIO_H
#define INCLUDED_CYFITTER_GPIO_H
#include "cy_device_headers.h"

/* RST */
#define RST_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define RST_0_INBUF_ENABLED 1u
#define RST_0_INIT_DRIVESTATE 0u
#define RST_0_INIT_MUXSEL 0u
#define RST_0_INPUT_SYNC 2u
#define RST_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define RST_0_NUM 0u
#define RST_0_PORT GPIO_PRT10
#define RST_0_SLEWRATE CY_GPIO_SLEW_FAST
#define RST_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define RST_DRIVEMODE CY_GPIO_DM_HIGHZ
#define RST_INBUF_ENABLED 1u
#define RST_INIT_DRIVESTATE 0u
#define RST_INIT_MUXSEL 0u
#define RST_INPUT_SYNC 2u
#define RST_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define RST_NUM 0u
#define RST_PORT GPIO_PRT10
#define RST_SLEWRATE CY_GPIO_SLEW_FAST
#define RST_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* SCL */
#define SCL_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define SCL_0_INBUF_ENABLED 1u
#define SCL_0_INIT_DRIVESTATE 1u
#define SCL_0_INIT_MUXSEL 3u
#define SCL_0_INPUT_SYNC 2u
#define SCL_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SCL_0_NUM 1u
#define SCL_0_PORT GPIO_PRT10
#define SCL_0_SLEWRATE CY_GPIO_SLEW_FAST
#define SCL_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define SCL_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define SCL_INBUF_ENABLED 1u
#define SCL_INIT_DRIVESTATE 1u
#define SCL_INIT_MUXSEL 3u
#define SCL_INPUT_SYNC 2u
#define SCL_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SCL_NUM 1u
#define SCL_PORT GPIO_PRT10
#define SCL_SLEWRATE CY_GPIO_SLEW_FAST
#define SCL_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* SDA */
#define SDA_0_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define SDA_0_INBUF_ENABLED 1u
#define SDA_0_INIT_DRIVESTATE 1u
#define SDA_0_INIT_MUXSEL 3u
#define SDA_0_INPUT_SYNC 2u
#define SDA_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SDA_0_NUM 2u
#define SDA_0_PORT GPIO_PRT10
#define SDA_0_SLEWRATE CY_GPIO_SLEW_FAST
#define SDA_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define SDA_DRIVEMODE CY_GPIO_DM_OD_DRIVESLOW
#define SDA_INBUF_ENABLED 1u
#define SDA_INIT_DRIVESTATE 1u
#define SDA_INIT_MUXSEL 3u
#define SDA_INPUT_SYNC 2u
#define SDA_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define SDA_NUM 2u
#define SDA_PORT GPIO_PRT10
#define SDA_SLEWRATE CY_GPIO_SLEW_FAST
#define SDA_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH0 */
#define ADC_CH0_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH0_0_INBUF_ENABLED 0u
#define ADC_CH0_0_INIT_DRIVESTATE 1u
#define ADC_CH0_0_INIT_MUXSEL 0u
#define ADC_CH0_0_INPUT_SYNC 2u
#define ADC_CH0_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH0_0_NUM 3u
#define ADC_CH0_0_PORT GPIO_PRT10
#define ADC_CH0_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH0_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH0_INBUF_ENABLED 0u
#define ADC_CH0_INIT_DRIVESTATE 1u
#define ADC_CH0_INIT_MUXSEL 0u
#define ADC_CH0_INPUT_SYNC 2u
#define ADC_CH0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH0_NUM 3u
#define ADC_CH0_PORT GPIO_PRT10
#define ADC_CH0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH1 */
#define ADC_CH1_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH1_0_INBUF_ENABLED 0u
#define ADC_CH1_0_INIT_DRIVESTATE 1u
#define ADC_CH1_0_INIT_MUXSEL 0u
#define ADC_CH1_0_INPUT_SYNC 2u
#define ADC_CH1_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH1_0_NUM 4u
#define ADC_CH1_0_PORT GPIO_PRT10
#define ADC_CH1_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH1_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH1_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH1_INBUF_ENABLED 0u
#define ADC_CH1_INIT_DRIVESTATE 1u
#define ADC_CH1_INIT_MUXSEL 0u
#define ADC_CH1_INPUT_SYNC 2u
#define ADC_CH1_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH1_NUM 4u
#define ADC_CH1_PORT GPIO_PRT10
#define ADC_CH1_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH1_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH2 */
#define ADC_CH2_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH2_0_INBUF_ENABLED 0u
#define ADC_CH2_0_INIT_DRIVESTATE 1u
#define ADC_CH2_0_INIT_MUXSEL 0u
#define ADC_CH2_0_INPUT_SYNC 2u
#define ADC_CH2_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH2_0_NUM 5u
#define ADC_CH2_0_PORT GPIO_PRT10
#define ADC_CH2_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH2_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH2_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH2_INBUF_ENABLED 0u
#define ADC_CH2_INIT_DRIVESTATE 1u
#define ADC_CH2_INIT_MUXSEL 0u
#define ADC_CH2_INPUT_SYNC 2u
#define ADC_CH2_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH2_NUM 5u
#define ADC_CH2_PORT GPIO_PRT10
#define ADC_CH2_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH2_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH3 */
#define ADC_CH3_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH3_0_INBUF_ENABLED 0u
#define ADC_CH3_0_INIT_DRIVESTATE 1u
#define ADC_CH3_0_INIT_MUXSEL 0u
#define ADC_CH3_0_INPUT_SYNC 2u
#define ADC_CH3_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH3_0_NUM 6u
#define ADC_CH3_0_PORT GPIO_PRT10
#define ADC_CH3_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH3_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH3_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH3_INBUF_ENABLED 0u
#define ADC_CH3_INIT_DRIVESTATE 1u
#define ADC_CH3_INIT_MUXSEL 0u
#define ADC_CH3_INPUT_SYNC 2u
#define ADC_CH3_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH3_NUM 6u
#define ADC_CH3_PORT GPIO_PRT10
#define ADC_CH3_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH3_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH4 */
#define ADC_CH4_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH4_0_INBUF_ENABLED 0u
#define ADC_CH4_0_INIT_DRIVESTATE 1u
#define ADC_CH4_0_INIT_MUXSEL 4u
#define ADC_CH4_0_INPUT_SYNC 2u
#define ADC_CH4_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH4_0_NUM 0u
#define ADC_CH4_0_PORT GPIO_PRT9
#define ADC_CH4_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH4_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH4_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH4_INBUF_ENABLED 0u
#define ADC_CH4_INIT_DRIVESTATE 1u
#define ADC_CH4_INIT_MUXSEL 4u
#define ADC_CH4_INPUT_SYNC 2u
#define ADC_CH4_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH4_NUM 0u
#define ADC_CH4_PORT GPIO_PRT9
#define ADC_CH4_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH4_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH5 */
#define ADC_CH5_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH5_0_INBUF_ENABLED 0u
#define ADC_CH5_0_INIT_DRIVESTATE 1u
#define ADC_CH5_0_INIT_MUXSEL 5u
#define ADC_CH5_0_INPUT_SYNC 2u
#define ADC_CH5_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH5_0_NUM 1u
#define ADC_CH5_0_PORT GPIO_PRT9
#define ADC_CH5_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH5_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH5_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH5_INBUF_ENABLED 0u
#define ADC_CH5_INIT_DRIVESTATE 1u
#define ADC_CH5_INIT_MUXSEL 5u
#define ADC_CH5_INPUT_SYNC 2u
#define ADC_CH5_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH5_NUM 1u
#define ADC_CH5_PORT GPIO_PRT9
#define ADC_CH5_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH5_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH6 */
#define ADC_CH6_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH6_0_INBUF_ENABLED 0u
#define ADC_CH6_0_INIT_DRIVESTATE 1u
#define ADC_CH6_0_INIT_MUXSEL 0u
#define ADC_CH6_0_INPUT_SYNC 2u
#define ADC_CH6_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH6_0_NUM 2u
#define ADC_CH6_0_PORT GPIO_PRT9
#define ADC_CH6_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH6_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH6_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH6_INBUF_ENABLED 0u
#define ADC_CH6_INIT_DRIVESTATE 1u
#define ADC_CH6_INIT_MUXSEL 0u
#define ADC_CH6_INPUT_SYNC 2u
#define ADC_CH6_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH6_NUM 2u
#define ADC_CH6_PORT GPIO_PRT9
#define ADC_CH6_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH6_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* ADC_CH7 */
#define ADC_CH7_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH7_0_INBUF_ENABLED 0u
#define ADC_CH7_0_INIT_DRIVESTATE 1u
#define ADC_CH7_0_INIT_MUXSEL 0u
#define ADC_CH7_0_INPUT_SYNC 2u
#define ADC_CH7_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH7_0_NUM 3u
#define ADC_CH7_0_PORT GPIO_PRT9
#define ADC_CH7_0_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH7_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define ADC_CH7_DRIVEMODE CY_GPIO_DM_ANALOG
#define ADC_CH7_INBUF_ENABLED 0u
#define ADC_CH7_INIT_DRIVESTATE 1u
#define ADC_CH7_INIT_MUXSEL 0u
#define ADC_CH7_INPUT_SYNC 2u
#define ADC_CH7_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define ADC_CH7_NUM 3u
#define ADC_CH7_PORT GPIO_PRT9
#define ADC_CH7_SLEWRATE CY_GPIO_SLEW_FAST
#define ADC_CH7_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART1_rx */
#define UART1_rx_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART1_rx_0_INBUF_ENABLED 1u
#define UART1_rx_0_INIT_DRIVESTATE 1u
#define UART1_rx_0_INIT_MUXSEL 18u
#define UART1_rx_0_INPUT_SYNC 2u
#define UART1_rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART1_rx_0_NUM 0u
#define UART1_rx_0_PORT GPIO_PRT5
#define UART1_rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART1_rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART1_rx_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART1_rx_INBUF_ENABLED 1u
#define UART1_rx_INIT_DRIVESTATE 1u
#define UART1_rx_INIT_MUXSEL 18u
#define UART1_rx_INPUT_SYNC 2u
#define UART1_rx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART1_rx_NUM 0u
#define UART1_rx_PORT GPIO_PRT5
#define UART1_rx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART1_rx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART1_tx */
#define UART1_tx_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART1_tx_0_INBUF_ENABLED 0u
#define UART1_tx_0_INIT_DRIVESTATE 1u
#define UART1_tx_0_INIT_MUXSEL 18u
#define UART1_tx_0_INPUT_SYNC 2u
#define UART1_tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART1_tx_0_NUM 1u
#define UART1_tx_0_PORT GPIO_PRT5
#define UART1_tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART1_tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART1_tx_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART1_tx_INBUF_ENABLED 0u
#define UART1_tx_INIT_DRIVESTATE 1u
#define UART1_tx_INIT_MUXSEL 18u
#define UART1_tx_INPUT_SYNC 2u
#define UART1_tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART1_tx_NUM 1u
#define UART1_tx_PORT GPIO_PRT5
#define UART1_tx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART1_tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */
