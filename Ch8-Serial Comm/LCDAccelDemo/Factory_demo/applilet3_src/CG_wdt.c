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
* Filename:	CG_wdt.c
* Abstract:	This file implements device driver for WDT module.
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
#include "CG_wdt.h"
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
**	This function initializes the watchdogtimer.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void WDT_Init(void)
{
	WDTIMK = 1U;	/* disable INTWDTI interrupt */
	WDTIIF = 0U;	/* clear INTWDTI interrupt flag */
	/* Set INTWDTI high priority */
	WDTIPR1 = 0U;
	WDTIPR0 = 0U;
	WDTIMK = 0U;	/* enable INTWDTI interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function restarts the watchdog timer.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void WDT_Restart(void)
{
	WDTE = 0xACU; 	/* restart watchdog timer */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
