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
* Filename:	CG_port.c
* Abstract:	This file implements device driver for PORT module.
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
#include "CG_port.h"
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
**	This function initializes the Port I/O.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_Init(void)
{
	P1 = _01_Pn0_OUTPUT_1 | _20_Pn5_OUTPUT_1;
	P4 = _04_Pn2_OUTPUT_1;
	P5 = _00_Pn5_OUTPUT_0;
	PM1 = _00_PMn0_MODE_OUTPUT | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _00_PMn5_MODE_OUTPUT | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
	PM4 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _00_PMn2_MODE_OUTPUT | _08_PMn3_NOT_USE | _F0_PM4_DEFAULT;
	PM5 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _00_PMn5_MODE_OUTPUT | _C0_PM5_DEFAULT;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P16 to input mode by software.
**
**  Parameters:
**	enablepu: Pull-up enable or not
**	enablettl: TTL enable or not
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP16Input(BOOL enablepu, BOOL enablettl)
{
	if (enablepu)
	{
		PU1 |= _40_PUn6_PULLUP_ON;
	}
	else
	{
		PU1 &= (UCHAR)~_40_PUn6_PULLUP_ON;
	}
	if (enablettl)
	{
		PIM1 |= _40_PIMn6_TTL_ON;
	}
	else
	{
		PIM1 &= (UCHAR)~_40_PIMn6_TTL_ON;
	}
	PM1 |= _40_PMn6_MODE_INPUT;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P16 to output mode by software.
**
**  Parameters:
**	initialvalue: initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP16Output(BOOL initialvalue)
{
	if (initialvalue)
	{
		P1 |= _40_Pn6_OUTPUT_1;
	}
	else
	{
		P1 &= (UCHAR)~_40_Pn6_OUTPUT_1;
	}
	PM1 &= (UCHAR)~_40_PMn6_MODE_INPUT;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P55 to input mode by software.
**
**  Parameters:
**	enablepu: Pull-up enable or not
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP55Input(BOOL enablepu)
{
	if (enablepu)
	{
		PU5 |= _20_PUn5_PULLUP_ON;
	}
	else
	{
		PU5 &= (UCHAR)~_20_PUn5_PULLUP_ON;
	}
	PM5 |= _20_PMn5_MODE_INPUT;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P55 to output mode by software.
**
**  Parameters:
**	initialvalue: initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP55Output(BOOL initialvalue)
{
	if (initialvalue)
	{
		P5 |= _20_Pn5_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~_20_Pn5_OUTPUT_1;
	}
	PM5 &= (UCHAR)~_20_PMn5_MODE_INPUT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
