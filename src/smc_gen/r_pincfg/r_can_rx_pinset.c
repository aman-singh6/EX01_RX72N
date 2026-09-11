/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name    : r_can_rx_pinset.c
* Version      : 1.0.2
* Device(s)    : R5F572NNDxBD
* Tool-Chain   : RXC toolchain
* Description  : Setting of port and mpc registers
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_can_rx_pinset.h"
#include "platform.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_CAN_PinSet_CAN1
* Description  : This function initializes pins for r_can_rx module
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_CAN_PinSet_CAN1()
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set CRX1 pin */
    PORT1.PMR.BIT.B5 = 0U;
    PORT1.PDR.BIT.B5 = 0U;
    MPC.P15PFS.BYTE = 0x10U;
    PORT1.PMR.BIT.B5 = 1U;
    PORT1.PDR.BIT.B5 = 0U;

    /* Set CTX1 pin */
    PORT2.PMR.BIT.B3 = 0U;
    PORT2.PDR.BIT.B3 = 0U;
    MPC.P23PFS.BYTE = 0x10U;
    PORT2.PMR.BIT.B3 = 1U;
    PORT2.PDR.BIT.B3 = 1U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

