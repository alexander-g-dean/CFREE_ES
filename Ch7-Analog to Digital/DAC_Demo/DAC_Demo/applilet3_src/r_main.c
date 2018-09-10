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
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G14 V1.01.03.06 [10 Sep 2012]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 4/14/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_adc.h"
#include "r_cg_dac.h"
#include <intrinsics.h>
/* Start user code for include. Do not edit comment generated here */
#include <math.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void DAC_Test(void);
void Init_SineTable(void);
void Delay(unsigned d);

uint8_t SineTable[NUM_STEPS];
// uint8_t TonePeriodTable[NUM_TONES] = { 31, 16, 42, 99, 27, 38, 31, 5, 13, 9, 19, 27};
/* End user code. Do not edit comment generated here */

/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0xEFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xF8U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x85U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Secure trace RAM area */
__no_init __root unsigned char ocdtraceram[1024] @ 0xFA300;

void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */

		Init_SineTable();
		DAC_Test();

    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void Init_SineTable(void) {
	unsigned n;
	
	for (n=0; n<NUM_STEPS; n++) {
		SineTable[n] = (uint8_t) ((MAX_DAC_CODE/2)*(1+sin(n*2*3.1415927/NUM_STEPS)));
	}
}

void Delay(unsigned d) {
	volatile unsigned n;
	
	for (n=0; n<d; n++)
		__no_operation();
}

/*
	Observe DAC outputs on pins 87 and 88 of MCU. Disable speaker by removing
	jumper JP3, disconnecting pins 2 and 3
*/
void DAC_Test(void) {
		uint16_t i=0, n=0;
		uint16_t delay=0;
		uint16_t lfsr=0x7316;
		uint16_t num_cycles=0;
		uint16_t bit=0;
	
		ADPC = 5; // set pins with ANO0 and ANO1 to analog
 		R_DAC0_Start();
		R_DAC1_Start();

    while (1U)
    {
		  bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
  		lfsr =  (lfsr >> 1) | (bit << 15);			

			delay = lfsr & 0x7f;

			if (delay < 3)
					delay = 3;
			
			num_cycles = 6000/delay;
			
			for (n=0; n<num_cycles; n++) {
				for (i=0; i<NUM_STEPS; i++) {
					R_DAC1_Set_ConversionValue(SineTable[i]);
					Delay(delay);
				}
			}
    }

}
/* End user code. Do not edit comment generated here */
