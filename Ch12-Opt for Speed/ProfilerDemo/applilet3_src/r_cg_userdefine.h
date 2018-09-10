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
* Creation Date: 9/22/2012
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */

// YRDKRL78 devices

#define DIR_OUT	0
#define DIR_IN  1

#define RLED1 	P5_bit.no5
#define RLED2 	P6_bit.no2
#define RLED3 	P6_bit.no3
#define GLED4 	P5_bit.no2
#define GLED5 	P5_bit.no3
#define GLED6 	P5_bit.no4
#define BACKLIGHT P7_bit.no0

#define RLED1_M 	PM5_bit.no5
#define RLED2_M 	PM6_bit.no2
#define RLED3_M 	PM6_bit.no3
#define GLED4_M 	PM5_bit.no2
#define GLED5_M 	PM5_bit.no3
#define GLED6_M 	PM5_bit.no4
#define BACKLIGHT_M PM7_bit.no0

#define INIT_LEDS { RLED1_M = RLED2_M = RLED3_M = GLED4_M = GLED5_M = GLED6_M = DIR_OUT; }

#define MAX(a,b) ((a>b)? a : b)
#define MIN(a,b) ((a<b)? a : b)

/* End user code. Do not edit comment generated here */
#endif
