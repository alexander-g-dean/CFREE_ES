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
* File Name    : r_cg_dac.h
* Version      : Applilet3 for RL78/G14 V1.01.03.06 [10 Sep 2012]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for DAC module.
* Creation Date: 4/14/2013
***********************************************************************************************************************/

#ifndef DAC_H
#define DAC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/* 
    Peripheral Enable Register 1 (PER1) 
*/
/* Control of D/A converter input clock (DACEN) */
#define _00_DA_CLOCK_STOP              (0x00U) /* stop supply of input clock */
#define _80_DA_CLOCK_SUPPLY            (0x80U) /* supplie input clock */

/*
    D/A Conversion Mode Register (DAM)
*/
/* D/A conversion operation (DACE1) */
#define _00_DA1_CONVERSION_STOP         (0x00U) /* stop conversion operation */
#define _20_DA1_CONVERSION_ENABLE       (0x20U) /* enable conversion operation */
/* D/A conversion operation (DACE0) */
#define _00_DA0_CONVERSION_STOP         (0x00U) /* stop conversion operation */
#define _10_DA0_CONVERSION_ENABLE       (0x10U) /* enable conversion operation */
/* D/A converter operation mode (DAMD1) */
#define _00_DA1_CONVERSION_MODE_NORMAL  (0x00U) /* normal mode */
#define _02_DA1_CONVERSION_MODE_RTO     (0x02U) /* real-time output mode */
/* D/A converter operation mode (DAMD0) */
#define _00_DA0_CONVERSION_MODE_NORMAL  (0x00U) /* normal mode */
#define _01_DA0_CONVERSION_MODE_RTO     (0x01U) /* real-time output mode */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* 8-Bit D/A conversion value setting registers 0 (DACS0) */
#define _00_DA0_CONVERSION_VALUE        (0x00U)
/* 8-Bit D/A conversion value setting registers 1 (DACS1) */
#define _00_DA1_CONVERSION_VALUE        (0x00U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_DAC_Create(void);
void R_DAC0_Start(void);
void R_DAC0_Stop(void);
void R_DAC0_Set_ConversionValue(uint8_t reg_value);
void R_DAC1_Start(void);
void R_DAC1_Stop(void);
void R_DAC1_Set_ConversionValue(uint8_t reg_value);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
