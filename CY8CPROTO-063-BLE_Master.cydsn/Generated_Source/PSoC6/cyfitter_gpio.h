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

/* UART_rx */
#define UART_rx_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_0_INBUF_ENABLED 1u
#define UART_rx_0_INIT_DRIVESTATE 1u
#define UART_rx_0_INIT_MUXSEL 18u
#define UART_rx_0_INPUT_SYNC 2u
#define UART_rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_0_NUM 0u
#define UART_rx_0_PORT GPIO_PRT5
#define UART_rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_rx_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_INBUF_ENABLED 1u
#define UART_rx_INIT_DRIVESTATE 1u
#define UART_rx_INIT_MUXSEL 18u
#define UART_rx_INPUT_SYNC 2u
#define UART_rx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_NUM 0u
#define UART_rx_PORT GPIO_PRT5
#define UART_rx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_tx */
#define UART_tx_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_0_INBUF_ENABLED 0u
#define UART_tx_0_INIT_DRIVESTATE 1u
#define UART_tx_0_INIT_MUXSEL 18u
#define UART_tx_0_INPUT_SYNC 2u
#define UART_tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_0_NUM 1u
#define UART_tx_0_PORT GPIO_PRT5
#define UART_tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_tx_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_INBUF_ENABLED 0u
#define UART_tx_INIT_DRIVESTATE 1u
#define UART_tx_INIT_MUXSEL 18u
#define UART_tx_INPUT_SYNC 2u
#define UART_tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_NUM 1u
#define UART_tx_PORT GPIO_PRT5
#define UART_tx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */
