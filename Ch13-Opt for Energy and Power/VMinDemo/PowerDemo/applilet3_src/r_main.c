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
* Creation Date: 6/15/2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */
#include "lcd.h"
#include "glyph_api.h"
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

uint16_t f_clk=32000; // Monitor clock speed (in kHz) to normalize debounce delays

void AwaitSW3(void);
void SetLEDs(uint8_t);
void SetLCDBacklight(uint8_t);
void SetSpkrAmp(uint8_t);	
void SetMicAmp(uint8_t);

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

  LCDInit();              /* Draw axes and labels */

  while (1U)
  {
		HOCODIV = 0;
		CSS = 0;
		f_clk = 32000;
		SetLEDs(ON);
		SetLCDBacklight(ON);
		SetSpkrAmp(ON);	
		SetMicAmp(ON);
	
		LCDClear();
		LCDPrintf(3, 0, "Start");
		AwaitSW3();

		LCDClear();
		LCDPrintf(3, 0, "LEDS 1-6");
		LCDPrintf(4, 0, "Off");
		AwaitSW3();
		SetLEDs(OFF);

		LCDClear();
		LCDPrintf(2, 0, "LCD");
		LCDPrintf(3, 0, "Backlight?");
		AwaitSW3();
		SetLCDBacklight(OFF);
	
		LCDClear();
		LCDPrintf(3, 0, "Speaker Amp?");
		AwaitSW3();
		SetSpkrAmp(OFF);
		
		LCDClear();
		LCDPrintf(3, 0, "Mic Amp?");
		AwaitSW3();
		SetMicAmp(OFF);

		LCDClear();
		LCDPrintf(3, 0, "1 MHz clk?");
		AwaitSW3();
		
		HOCODIV = 5;
		f_clk = 1000;

		LCDClear();
		LCDPrintf(3, 0, "32 kHz clk?");
		AwaitSW3();
		CSS = 1; 
		f_clk = 32;
		

		LCDClear();
		LCDPrintf(3, 0, "All done!");
		AwaitSW3();
		
  }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void AwaitSW3(void) {
	volatile long d;
	while (SW_3) {// wait for press
		if (!SW_2) {
			LED_R_1 ^= 1;
			for (d=10*f_clk; d>0; d--) // delay to debounce
				;
		}
	}
	for (d=10*f_clk; d>0; d--) // delay to debounce
		;
	while (!SW_3) // wait for release
		;
	for (d=10*f_clk; d>0; d--) // delay to debounce
		;
}	

void SetLEDs(uint8_t on) {
	uint8_t state;
	
	if (on) // LED drive signals are active low
		state = 0;
	else
		state = 1;

	LED_R_1 = state;
	LED_R_2 = state;
	LED_R_3 = state;
	LED_G_4 = state;
	LED_G_5 = state;
	LED_G_6 = state;
}

void SetLCDBacklight(uint8_t on) {
	LED_LCD_BL = on;
}

void SetSpkrAmp(uint8_t on) {
	if (on)
		SPKR_AMP_PWR = 1;
	else
		SPKR_AMP_PWR = 0;
}
			
void SetMicAmp(uint8_t on) {
	if (on)
		MIC_AMP_PWR = 1;
	else
		MIC_AMP_PWR = 0;
}

/* End user code. Do not edit comment generated here */
