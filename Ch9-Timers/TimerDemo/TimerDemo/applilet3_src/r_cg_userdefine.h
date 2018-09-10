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
* Copyright (C) 2010, 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_userdefine.h
* Version      : Applilet3 for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file includes user definition.
* Creation Date: 6/11/2012
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */


#define MAX(a,b) ((a>b)? a : b)
#define MIN(a,b) ((a<b)? a : b)

#define D_ANEM (0.1) 		// Duty cycle of signal
#define FC_ANEM (15625) // Count frequency in Hz
#define R_ANEM (2.8)  	// radius in inches from axle to center of cup
#define N_ANEM (2)    	// pulses per revolution
#define K_ANEM (1-D_ANEM)*(2*3.1415927*R_ANEM*FC_ANEM)/(3.6*N_ANEM) // ((2*3.1415927*R_ANEMOMETER)*3600/(5280*12))

#define LED_R_1 P5_bit.no5
#define LED_R_2 P6_bit.no2
#define LED_R_3 P6_bit.no3
#define LED_G_4 P5_bit.no2
#define LED_G_5 P5_bit.no3
#define LED_G_6 P5_bit.no4

#define LED_LCD_BL P7_bit.no0
#define SPKR_AMP_PWR P4_bit.no2
#define MIC_AMP_PWR P4_bit.no1

#define SW_1 P13_bit.no7
#define SW_2 P5_bit.no0
#define SW_3 P5_bit.no1

/* End user code. Do not edit comment generated here */
#endif
