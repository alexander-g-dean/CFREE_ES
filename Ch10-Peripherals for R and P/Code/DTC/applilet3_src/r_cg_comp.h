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
* File Name    : r_cg_comp.h
* Version      : Applilet3 for RL78/G14 V1.01.03.06 [10 Sep 2012]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for COMP module.
* Creation Date: 4/29/2013
***********************************************************************************************************************/

#ifndef COMP_H
#define COMP_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Comparator mode setting register (COMPMDR)
*/
/* Comparator 0 operation enable bit (C0ENB) */
#define _00_COMP0_OPERATION_DISABLED    (0x00U)   /* disable comparator 0 operation */
#define _01_COMP0_OPERATION_ENABLED     (0x01U)   /* enable comparator 0 operation */
/* Comparator 0 windows mode selection bit (C0WDE) */
#define _00_COMP0_MODE_NORMAL           (0x00U)   /* normal mode */
#define _02_COMP0_MODE_WINDOWS          (0x02U)   /* windows mode */
/* Comparator 0 reference voltage selection bit (C0VRF) */
#define _00_COMP0_REF_VOLTAGE_IVREF0    (0x00U)   /* IVREF0 input */
#define _04_COMP0_REF_VOLTAGE_BGRVREF   (0x04U)   /* BGRVREF input */
/* Comparator 0 monitor flag bit (C0MON) */
#define _00_COMP0_FLAG_IVREF0           (0x00U)   /* IVCMP0 < IVREF0 or stop comparator 0 */
#define _08_COMP0_FLAG_IVCMP0           (0x08U)   /* IVCMP0 > IVREF0 */
/* Comparator 1 operation enable bit (C1ENB) */
#define _00_COMP1_OPERATION_DISABLED    (0x00U)   /* disable comparator 1 operation */
#define _10_COMP1_OPERATION_ENABLED     (0x10U)   /* enable comparator 1 operation */
/* Comparator 1 windows mode selection bit (C1WDE) */
#define _00_COMP1_MODE_NORMAL           (0x00U)   /* normal mode */
#define _20_COMP1_MODE_WINDOWS          (0x20U)   /* windows mode */
/* Comparator 1 reference voltage selection bit (C1VRF) */
#define _00_COMP1_REF_VOLTAGE_IVREF1    (0x00U)   /* IVREF1 input */
#define _40_COMP1_REF_VOLTAGE_BGRVREF   (0x40U)   /* BGRVREF input */
/* Comparator 1 monitor flag bit (C1MON) */
#define _00_COMP1_FLAG_IVREF1           (0x00U)   /* IVCMP1 < IVREF1 or stop comparator 1 */
#define _80_COMP1_FLAG_IVCMP1           (0x80U)   /* IVCMP1 > IVREF1 */

/*
    Comparator filter control register (COMPFIR)
*/
/* Comparator 0 filter selection bits (C0FCK) */
#define _00_COMP0_FILTER_NONE           (0x00U)   /* disable filter */
#define _01_COMP0_FILTER_FCLK           (0x01U)   /* sample with fCLK */
#define _02_COMP0_FILTER_FCLK_8         (0x02U)   /* sample with fCLK/2^3 */
#define _03_COMP0_FILTER_FCLK_32        (0x03U)   /* sample with fCLK/2^5 */
/* Comparator 0 edges polarity selection bit (C0EPO) */
#define _00_COMP0_RISING_INTERRUPT      (0x00U)   /* interrupt when rising edge */
#define _04_COMP0_FALLING_INTERRUPT     (0x04U)   /* interrupt when falling edge */
/* Comparator 0 edge detectioin selection bit (C0EDG) */
#define _00_COMP0_ONE_EDGE_INTERRUPT    (0x00U)   /* interrupt when one edge */
#define _08_COMP0_BOTH_EDGES_INTERRUPT  (0x08U)   /* interrupt when both edges */
/* Comparator 1 filter selection bits (C1FCK) */
#define _00_COMP1_FILTER_NONE           (0x00U)   /* disable filter */
#define _10_COMP1_FILTER_FCLK           (0x10U)   /* sample with fCLK */
#define _20_COMP1_FILTER_FCLK_8         (0x20U)   /* sample with fCLK/2^3 */
#define _30_COMP1_FILTER_FCLK_32        (0x30U)   /* sample with fCLK/2^5 */
/* Comparator 1 edges polarity selection bit (C1EPO) */
#define _00_COMP1_RISING_INTERRUPT      (0x00U)   /* interrupt when rising edge */
#define _40_COMP1_FALLING_INTERRUPT     (0x40U)   /* interrupt when falling edge */
/* Comparator 1 edge detectioin selection bit (C1EDG) */
#define _00_COMP1_ONE_EDGE_INTERRUPT    (0x00U)   /* interrupt when one edge */
#define _80_COMP1_BOTH_EDGES_INTERRUPT  (0x80U)   /* interrupt when both edges */

/*
    Comparator output control register (COMPOCR)
*/
/* Comparator 0 interrupt demand permission bit (C0IE) */
#define _00_COMP0_INTERRUPT_DISABLE     (0x00U)   /* disbale interrupt demand */
#define _01_COMP0_INTERRPUT_ENABLE      (0x01U)   /* enable interrupt demand */
/* Comparator 0 VC0OUT output permission bit (C0OE) */
#define _00_COMP0_VC0OUT_DISABLE        (0x00U)   /* disable VC0OUT output */
#define _02_COMP0_VC0OUT_ENABLE         (0x02U)   /* enable VC0OUT output */
/* Comparator 0 VC0OUT output polarity selection bit (C0OP) */
#define _00_COMP0_VC0OUT_NORMAL         (0x00U)   /* VC0OUT normal output */
#define _04_COMP0_VC0OUT_INVERTED       (0x04U)   /* VC0OUT inverted output */
/* Comparator 1 interrupt demand permission bit (C1IE) */
#define _00_COMP1_INTERRUPT_DISABLE     (0x00U)   /* disbale interrupt demand */
#define _10_COMP1_INTERRPUT_ENABLE      (0x10U)   /* enable interrupt demand */
/* Comparator 1 VC1OUT output permission bit (C1OE) */
#define _00_COMP1_VC1OUT_DISABLE        (0x00U)   /* disable VC1OUT output */
#define _20_COMP1_VC1OUT_ENABLE         (0x20U)   /* enable VC1OUT output */
/* Comparator 1 VC1OUT output polarity selection bit (C1OP) */
#define _00_COMP1_VC1OUT_NORMAL         (0x00U)   /* VC1OUT normal output */
#define _40_COMP1_VC1OUT_INVERTED       (0x40U)   /* VC1OUT inverted output */
/* Comparator speed selection bit (SPDMD) */
#define _00_COMP_SPEED_LOW              (0x00U)   /* low speed */
#define _80_COMP_SPEED_HIGH             (0x80U)   /* high speed */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define COMP_WAIT_TIME                  (3200U)   /* wait time for 100us */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_COMP_Create(void);
void R_COMP0_Start(void);
void R_COMP0_Stop(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
