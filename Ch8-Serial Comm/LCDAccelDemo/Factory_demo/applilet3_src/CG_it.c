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
* Filename:	CG_it.c
* Abstract:	This file implements device driver for IT module.
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
#include "CG_it.h"
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
**	This function initializes the IT module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IT_Init(void)
{
	RTCEN = 1U;	/* supply RTC clock */
	ITMC = _0000_IT_OPERATION_DISABLE;	/* disable ITMC operation */
	ITMK = 1U;	/* disable INTIT interrupt */
	ITIF = 0U;	/* clear INTIT interrupt flag */
	/* Set INTIT level1 priority */
	ITPR1 = 0U;
	ITPR0 = 1U;
	ITMC = _000E_ITMCMP_VALUE;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts IT module operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IT_Start(void)
{
	ITIF = 0U;	/* clear INTIT interrupt flag */
	ITMK = 0U;	/* enable INTIT interrupt */
	ITMC |= _8000_IT_OPERATION_ENABLE;	/* enable IT operation */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops IT module operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IT_Stop(void)
{
	ITMC &= (UCHAR)~_8000_IT_OPERATION_ENABLE;	/* disable ITMC operation */
	ITMK = 1U;	/* disable INTIT interrupt */
	ITIF = 0U;	/* clear INTIT interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes IT register value.
**
**  Parameters:
**	regvalue: value for data register
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IT_ChangeTimerCondition(USHORT regvalue)
{
	regvalue &= 0x0FFFU;
	ITMC &= 0x8000U;
	ITMC |= regvalue;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
