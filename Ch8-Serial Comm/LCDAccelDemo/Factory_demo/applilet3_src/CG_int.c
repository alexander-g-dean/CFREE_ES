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
* Filename:	CG_int.c
* Abstract:	This file implements device driver for INT module.
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
#include "CG_int.h"
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
**	This function initializes INTP module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP_Init(void)
{
	PMK0 = 1U;	/* disable INTP0 operation */
	PIF0 = 0U;	/* clear INTP0 interrupt flag */
	PMK1 = 1U;	/* disable INTP1 operation */
	PIF1 = 0U;	/* clear INTP1 interrupt flag */
	PMK2 = 1U;	/* disable INTP2 operation */
	PIF2 = 0U;	/* clear INTP2 interrupt flag */
	PMK3 = 1U;	/* disable INTP3 operation */
	PIF3 = 0U;	/* clear INTP3 interrupt flag */
	PMK4 = 1U;	/* disable INTP4 operation */
	PIF4 = 0U;	/* clear INTP4 interrupt flag */
	PMK5 = 1U;	/* disable INTP5 operation */
	PIF5 = 0U;	/* clear INTP5 interrupt flag */
	PMK6 = 1U;	/* disable INTP6 operation */
	PIF6 = 0U;	/* clear INTP6 interrupt flag */
	PMK7 = 1U;	/* disable INTP7 operation */
	PIF7 = 0U;	/* clear INTP7 interrupt flag */
	PMK8 = 1U;	/* disable INTP8 operation */
	PIF8 = 0U;	/* clear INTP8 interrupt flag */
	PMK9 = 1U;	/* disable INTP9 operation */
	PIF9 = 0U;	/* clear INTP9 interrupt flag */
	PMK10 = 1U;	/* disable INTP10 operation */
	PIF10 = 0U;	/* clear INTP10 interrupt flag */
	PMK11 = 1U;	/* disable INTP11 operation */
	PIF11 = 0U;	/* clear INTP11 interrupt flag */
	/* Set INTP2 low priority */
	PPR12 = 1U;
	PPR02 = 1U;
	EGN0 = _04_INTP2_EDGE_FALLING_SEL;
    	/* Set INTP2 pin */
	PM5 |= 0x02U;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function clears INTP2 interrupt flag and enables interrupt.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP2_Enable(void)
{
	PIF2 = 0U;	/* clear INTP2 interrupt flag */
	PMK2 = 0U;	/* enable INTP2 interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function disables INTP2 interrupt and clears interrupt flag.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP2_Disable(void)
{
	PMK2 = 1U;	/* disable INTP2 interrupt */
	PIF2 = 0U;	/* clear INTP2 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
