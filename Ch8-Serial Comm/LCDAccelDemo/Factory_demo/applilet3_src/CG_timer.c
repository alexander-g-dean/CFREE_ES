/*
*******************************************************************************
* Copyright(C) 2011 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for RL78/G13
* 16-Bit Single-Chip Microcontrollers
* Filename:	CG_timer.c
* Abstract:	This file implements device driver for TAU module.
* APIlib:	Applilet3 for RL78/G13 E1.00b [14 Jan 2011]
* Device:	R5F100LE
* Compiler:	IAR Systems iccrl78
* Creation date:	9/21/2011
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "CG_macrodriver.h"
#include "CG_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the TAU0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Init(void)
{
	TAU0EN = 1U;		/* supplies input clock */
	TPS0 = _0000_TAU_CKM0_FCLK_0 | _0050_TAU_CKM1_FCLK_5 | _0000_TAU_CKM2_FCLK_1 | _0000_TAU_CKM3_FCLK_8;
	/* Stop all channels */
	TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON | _0200_TAU_CH1_H8_STOP_TRG_ON | _0800_TAU_CH3_H8_STOP_TRG_ON;
	/* Mask channel 0 interrupt */
	TMMK00 = 1U;	/* disable INTTM00 interrupt */
	TMIF00 = 0U;	/* clear INTTM00 interrupt flag */
	/* Mask channel 1 interrupt */
	TMMK01 = 1U;	/* disable INTTM01 interrupt */
	TMIF01 = 0U;	/* clear INTTM01 interrupt flag */
	/* Mask channel 1 higher 8 bits interrupt */
	TMMK01H = 1U;	/* disable INTTM01H interrupt */
	TMIF01H = 0U;	/* clear INTTM01H interrupt flag */
	/* Mask channel 2 interrupt */
	TMMK02 = 1U;	/* disable INTTM02 interrupt */
	TMIF02 = 0U;	/* clear INTTM02 interrupt flag */
	/* Mask channel 3 interrupt */
	TMMK03 = 1U;	/* disable INTTM03 interrupt */
	TMIF03 = 0U;	/* clear INTTM03 interrupt flag */
	/* Mask channel 3 higher 8 bits interrupt */
	TMMK03H = 1U;	/* disable INTTM03H interrupt */
	TMIF03H = 0U;	/* clear INTTM03H interrupt flag */
	/* Mask channel 4 interrupt */
	TMMK04 = 1U;	/* disable INTTM04 interrupt */
	TMIF04 = 0U;	/* clear INTTM04 interrupt flag */
	/* Mask channel 5 interrupt */
	TMMK05 = 1U;	/* disable INTTM05 interrupt */
	TMIF05 = 0U;	/* clear INTTM05 interrupt flag */
	/* Mask channel 6 interrupt */
	TMMK06 = 1U;	/* disable INTTM06 interrupt */
	TMIF06 = 0U;	/* clear INTTM06 interrupt flag */
	/* Mask channel 7 interrupt */
	TMMK07 = 1U;	/* disable INTTM07 interrupt */
	TMIF07 = 0U;	/* clear INTTM07 interrupt flag */
	/* Set INTTM01 low priority */
	TMPR101 = 1U;
	TMPR001 = 1U;
	/* Set INTTM02 low priority */
	TMPR102 = 1U;
	TMPR002 = 1U;
	/* Channel 0 is used as master channel for PWM output function */
	TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_COMBINATION_MASTER | _0000_TAU_TRIGGER_SOFTWARE | _0001_TAU_MODE_PWM_MASTER;
	TDR00 = _3E7F_TAU_TDR00_VALUE;
	TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
	TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
	/* Channel 1 is used as slave channel for PWM output function */
	TMR01 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
	TDR01 = _0C80_TAU_TDR01_VALUE;
	TOM0 |= _0002_TAU_CH1_OUTPUT_COMBIN;
	TOL0 &= ~_0002_TAU_CH1_OUTPUT_LEVEL_L;
	TO0 &= ~_0002_TAU_CH1_OUTPUT_VALUE_1;
	TOE0 |= _0002_TAU_CH1_OUTPUT_ENABLE;
	/* Channel 2 used as interval timer */
	TMR02 = _8000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | _0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
	TDR02 = _EA5F_TAU_TDR02_VALUE;
	TOM0 &= ~_0004_TAU_CH2_OUTPUT_COMBIN;
	TOL0 &= ~_0004_TAU_CH2_OUTPUT_LEVEL_L;
	TO0 &= ~_0004_TAU_CH2_OUTPUT_VALUE_1;
	TOE0 &= ~_0004_TAU_CH2_OUTPUT_ENABLE;
	/* Set TO01 pin */
	P1 &= 0xBFU;
	PM1 &= 0xBFU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel0_Start(void)
{
	TMIF01 = 0U;	/* clear INTTM01 interrupt flag */
	TMMK01 = 0U;	/* enable INTTM01 interrupt */
	TOE0 |= _0002_TAU_CH1_OUTPUT_ENABLE;
	TS0 |= _0001_TAU_CH0_START_TRG_ON | _0002_TAU_CH1_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel0_Stop(void)
{
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON;
	TOE0 &= ~_0002_TAU_CH1_OUTPUT_ENABLE;
	/* Mask channel 1 interrupt */
	TMMK01 = 1U;	/* disable INTTM01 interrupt */
	TMIF01 = 0U;	/* clear INTTM01 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU0 channel 1 duty value when used as PWM slave channel.
**
**  Parameters:
**	ratio: duty value to change
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel1_ChangeDuty(UCHAR ratio)
{
	ULONG reg = 0U;
	
	if (ratio > 100U)
	{
		ratio = 100U;
	}
	reg = TDR00;
	reg = (reg + 1) * ratio / 100U;
	TDR01 = (USHORT)reg;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU0 channel 2 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel2_Start(void)
{
	TMIF02 = 0U;	/* clear INTTM02 interrupt flag */
	TMMK02 = 0U;	/* enable INTTM02 interrupt */
	TS0 |= _0004_TAU_CH2_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU0 channel 2 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel2_Stop(void)
{
	TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
	/* Mask channel 2 interrupt */
	TMMK02 = 1U;	/* disable INTTM02 interrupt */
	TMIF02 = 0U;	/* clear INTTM02 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU0 channel 2 register value.
**
**  Parameters:
**	regvalue: value for data register
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel2_ChangeTimerCondition(USHORT regvalue)
{
	TDR02 = regvalue;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
