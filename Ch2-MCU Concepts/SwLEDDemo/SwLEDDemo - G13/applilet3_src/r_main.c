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
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 6/4/2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0xEFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE8U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x04U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void  main(void)
{
		volatile uint16_t d=0;  // delay variable must be volatile or else 
									// compiler will optimize it out
		uint8_t n=0; // counter variable
		
    /* Start user code. Do not edit comment generated here */
    while (1U)
    {

#if 0
			/* first set LEDs according to counter variable n */
				P5_bit.no5 = (n&0x20)? 1 : 0;
				P6_bit.no2 = (n&0x10)? 1 : 0;
	      P6_bit.no3 = (n&0x08)? 1 : 0;
        P5_bit.no2 = (n&0x04)? 1 : 0;
        P5_bit.no3 = (n&0x02)? 1 : 0;
        P5_bit.no4 = (n&0x01)? 1 : 0;
				n++;
				
				/* next read the three switches to set the delay time */
				if (P13_bit.no7 == 0) {
						d = 0x1000;
				} else if (P5_bit.no0 == 0) {
						d = 0x4000;
				} else if (P5_bit.no1 == 0) {
						d = 0x8000;
				} else {
						d = 0xffff;
				}
#else
				/* first set LEDs according to counter variable n */
				LED_R_1 = (n&0x20)? 1 : 0;
				LED_R_2 = (n&0x10)? 1 : 0;
	      LED_R_3 = (n&0x08)? 1 : 0;
        LED_G_4 = (n&0x04)? 1 : 0;
        LED_G_5 = (n&0x02)? 1 : 0;
        LED_G_6 = (n&0x01)? 1 : 0;
				n++;
				
				/* next read the three switches to set the delay time */
				if (SW_1 == 0) {
						d = 0x1000;
				} else if (SW_2 == 0) {
						d = 0x4000;
				} else if (SW_3 == 0) {
						d = 0x8000;
				} else {
						d = 0xffff;
				}
#endif

				/* delay for appropriate time */
				for ( ; d > 0 ; d--)
					;
    }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
