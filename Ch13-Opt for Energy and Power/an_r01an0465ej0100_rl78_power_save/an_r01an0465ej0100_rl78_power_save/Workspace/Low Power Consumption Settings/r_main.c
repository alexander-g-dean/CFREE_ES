/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : r_main.c
* Version : 1.0
* Device(s) : R5F100LE
* H/W Platform : R5F100LE
* Description : This file implements main function.
* Operation : 1. Compile and download the sample code. Click ÅeReset GoÅf
*                to start the software.
******************************************************************************/
/******************************************************************************
* History : DD.MM.YYYY Version Description
* : 15.09.2011 1.00 First Release
******************************************************************************/

/******************************************************************************
Includes <System Includes> , ÅgProject IncludesÅh
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/* Start user code for global. Do not edit comment generated here */
/******************************************************************************
Private global variables and functions
******************************************************************************/
static	enum	mode	operate_mode = MODE_OCO_RUN;	/* Operate mode */

static const uint8_t	led_pattern[5] =				/* LED0-LED2 pattern */
{
	/* +++++----------  No use (Low level output) */
	/* |||||+---------  P12:LED2	ON:STOP mode */
	/* ||||||+--------  P11:LED1	ON:HALT mode */
	/* |||||||+-------  P10:LED0	ON:fCLK = fIH OFF:fCLK = fSUB */
	 0b00000110		/* MODE_OCO_RUN		LED0 = ON,  LED1 = OFF, LED2 = OFF */
	,0b00000100		/* MODE_OCO_HALT	LED0 = ON,  LED1 = ON,  LED2 = OFF */
	,0b00000010		/* MODE_OCO_STOP	LED0 = ON,  LED1 = OFF, LED2 = ON  */
	,0b00000111		/* MODE_SUB_RUN		LED0 = OFF, LED1 = OFF, LED2 = OFF */
	,0b00000101		/* MODE_SUB_HALT	LED0 = OFF, LED1 = ON,  LED2 = OFF */
};
/* End user code. Do not edit comment generated here */

/******************************************************************************
* Function Name: main
* Description : This function implements main function.
* Arguments : None
* Return Value : None
******************************************************************************/
void main(void)
{
	/* Start user code. Do not edit comment generated here */
	MD_STATUS	status;			/* Status */
	uint16_t	counter10ms;	/* About 10ms counter */

	DI();						/* Set interrupt disabled */
	R_INTC0_Start();			/* Enable INTP0 interrupt */

	/* Main loop */
	while (1U)
	{
		P_LED = led_pattern[operate_mode];	/* LED0-2 output */

		/* Operation for each mode */
		switch(operate_mode)
		{
			case	MODE_OCO_RUN:
				/*==========================================
					fCLK = fIH
				 =========================================*/
				/* Change operation clock fSUB -> fIH */
				status = R_CGC_Set_fCLK(HIOCLK);

				/*--------------------------
					Run mode
				 -------------------------*/
				while(!PIF0)
				{
					NOP();			/* Wait INTP0 input */
				}
				break;

			case	MODE_OCO_HALT:
				/*--------------------------
					HALT mode
				 -------------------------*/
				HALT();				/* Wait INTP0 input */
				break;

			case	MODE_OCO_STOP:
				/*--------------------------
					STOP mode
				 -------------------------*/
				STOP();				/* Wait INTP0 input */
				break;

			case	MODE_SUB_RUN:
				/*==========================================
					fCLK = fSUB
				 =========================================*/
				/* Change operation clock fIH -> fSUB */
				status = R_CGC_Set_fCLK(SUBXT1CLK);

				/*--------------------------
					Sub-Run mode
				 -------------------------*/
				while(!PIF0)
				{
					NOP();			/* Wait INTP0 input */
				}
				break;

			case	MODE_SUB_HALT:
				/*--------------------------
					Sub-HALT mode
				 -------------------------*/
				HALT();				/* Wait INTP0 input */
				break;

			default:
				break;
		}
		PIF0 = 0;				/* Clear INTP0 interrupt flag */

		/*==========================================
			Countermeasure for chattering on INTP0
		 =========================================*/
		/* Wait about 10ms */
		if(CLS == 0)
		{	/* fCLK = 1MHz */
			counter10ms = 1050;		/* Set 10ms counter */
		}
		else
		{	/* fCLK = 32.768kHz */
			counter10ms = 32;		/* Set 10ms counter */
		}
		/* Wait 10ms or more have elapsed */
		for( ; counter10ms > 0; counter10ms-- )
		{
			NOP();
		}
		if (P13.7 == 0)			/* No chattering action on INTP0 ? */
		{						/* Yes */
			/* Update operate mode */
			operate_mode = (operate_mode + 1) % MODE_MAX;
		}
		PIF0 = 0;				/* Clear INTP0 interrupt flag */
	}
	/* End user code. Do not edit comment generated here */
}
/******************************************************************************
End of function main
******************************************************************************/

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
