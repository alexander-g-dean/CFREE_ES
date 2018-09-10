/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial.c
* Version      : Applilet3 for RL78/G14 V1.01.03.06 [10 Sep 2012]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for Serial module.
* Creation Date: 4/25/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint8_t * gp_csi21_rx_address;         /* csi21 receive buffer address */
uint16_t  g_csi21_rx_length;           /* csi21 receive data length */
uint16_t  g_csi21_rx_count;            /* csi21 receive data count */
uint8_t * gp_csi21_tx_address;         /* csi21 send buffer address */
uint16_t  g_csi21_send_length;         /* csi21 send data length */
uint16_t  g_csi21_tx_count;            /* csi21 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU1_Create
* Description  : This function initializes the SAU1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Create(void)
{
    SAU1EN = 1U;    /* supply SAU1 clock */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS1 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
    R_CSI21_Create();
}

/***********************************************************************************************************************
* Function Name: R_CSI21_Create
* Description  : This function initializes the CSI21 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI21_Create(void)
{
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON;    /* disable CSI21 */
    CSIMK21 = 1U;    /* disable INTCSI21 interrupt */
    CSIIF21 = 0U;    /* clear INTCSI21 interrupt flag */
    /* Set INTCSI21 low priority */
    CSIPR121 = 1U;
    CSIPR021 = 1U;
    SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR11 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR11 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
    SDR11 = _6400_CSI21_DIVISOR;
    SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1;    /* CSI21 clock initial level */
    SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;    /* CSI21 SO initial level */
    SOE1 |= _0002_SAU_CH1_OUTPUT_ENABLE;    /* enable CSI21 output */
    /* Set SI21 pin */
    PM7 |= 0x02U;
    /* Set SO21 pin */
    P7 |= 0x04U;
    PM7 &= 0xFBU;
    /* Set SCK21 pin */
    P7 |= 0x01U;
    PM7 &= 0xFEU;
}

/***********************************************************************************************************************
* Function Name: R_CSI21_Start
* Description  : This function starts the CSI21 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI21_Start(void)
{
    CSIIF21 = 0U;    /* clear INTCSI21 interrupt flag */
    CSIMK21 = 0U;    /* enable INTCSI21 */
    SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1;    /* CSI21 clock initial level */
    SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;           /* CSI21 SO initial level */
    SOE1 |= _0002_SAU_CH1_OUTPUT_ENABLE;           /* enable CSI21 output */
    SS1 |= _0002_SAU_CH1_START_TRG_ON;             /* enable CSI21 */
}

/***********************************************************************************************************************
* Function Name: R_CSI21_Stop
* Description  : This function stops the CSI21 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI21_Stop(void)
{
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON;        /* disable CSI21 */
    SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;    /* disable CSI21 output */
    CSIMK21 = 1U;    /* disable INTCSI21 interrupt */
    CSIIF21 = 0U;    /* clear INTCSI21 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_CSI21_Send_Receive
* Description  : This function sends and receives CSI21 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_CSI21_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi21_tx_count = tx_num;        /* send data count */
        gp_csi21_tx_address = tx_buf;     /* send buffer pointer */
        gp_csi21_rx_address = rx_buf;     /* receive buffer pointer */
        CSIMK21 = 1U;                     /* disable INTCSI21 interrupt */
        SIO21 = *gp_csi21_tx_address;    /* started by writing data to SDR[7:0] */
        gp_csi21_tx_address++;
        g_csi21_tx_count--;
        CSIMK21 = 0U;                     /* enable INTCSI21 interrupt */
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
