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
* Creation Date: 6/20/2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
#include "lcd.h"
volatile uint8_t run=1, stop=0, halt=0, state_change=1;

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
void delay(uint16_t);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void  main(void)
{
    /* Start user code. Do not edit comment generated here */
	uint8_t f=32; // clock speed in MHz
	uint8_t clock_divider=0;
	
  LCDInit();          
	LCDFont(FONT_LARGE);

	R_INTC0_Start();
	R_INTC1_Start();
	R_INTC2_Start();

	LED_R_1 = LED_R_2 = LED_R_3 = 1;
	LED_G_4 = LED_G_5 = LED_G_6 = 1;
	
	__enable_interrupt();
	
  while (1U)
  {
		while (!state_change)
    	;
		state_change = 0;
		LCDClear();
		if (run) {
			LED_G_4 = LED_G_5 = LED_G_6 = 0;
			LED_R_1 = LED_R_2 = LED_R_3 = 1;
			LCDPrintf(1,1,"Run 32 MHz");

		} else if (halt) {

			LED_R_1 = 0;
			LED_R_2 = LED_R_3 = 1;
			LED_G_4 = LED_G_5 = LED_G_6 = 1;
			LCDString("Halt",2,2);
			delay(1000);
		
			// slow down HSOCO to 1 MHz
			SET_HOCODIV(5);
			
			__halt();
			
//			RTCLPC = 0;
			// speed up HSOCO to 32 MHz
			SET_HOCODIV(0);

		} else if (stop) {

			LED_R_1 = LED_R_3 = 1;
			LED_R_2 = 0;
			LED_G_4 = LED_G_5 = LED_G_6 = 1;
			LCDString("Stop",2,2);
			delay(1000);

			
			// Start subsystem clock
			XTSTOP = 0;
			
			delay(1);
			
			// switch to XT1
			CSS = 1;
			while (CLS != 1)
				;
			
			// slow down HSOCO to 1 MHz
			SET_HOCODIV(5);

			// turn off HSOCO
			HIOSTOP = 1;

			// turn off SAU0
//			SAU0EN = 0;
			
			__stop();

			LED_G_6 = 0;	
			
			// start up HSOCO
			HIOSTOP = 0;
	
			// switch back to HSOCO
			CSS = 0;
			while (CLS != 0)
				;

			
			XTSTOP = 1;

			// Speed up to 32 MHz
			SET_HOCODIV(0);		

			// turn on SAU0
//			SAU0EN = 1;

			LED_G_6 = 1;	

			
		}
		LED_R_1 = LED_R_2 = LED_R_3 = 1;
		LED_G_4 = LED_G_5 = LED_G_6 = 0;
		
  }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void delay(uint16_t t) {
	volatile uint32_t d = t*1000;
	
	while (d--)
		;
}

/* End user code. Do not edit comment generated here */
