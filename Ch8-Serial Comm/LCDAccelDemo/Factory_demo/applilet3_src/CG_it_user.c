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
* Filename:	CG_it_user.c
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
#include "CG_int.h"
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
extern unsigned char mute;
volatile int G_msTimer = 0;   // Timer Counter
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTIT interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTIT_vect
__interrupt void MD_INTIT(void)
{
	/* Start user code. Do not edit comment generated here */
        //INTP2_Enable(); // Disable for LCD stuff
        //IT_Stop();
        G_msTimer++;
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void delay_ms(int aTimeMS)
{
    G_msTimer = 0;
    IT_Start();
    while(G_msTimer < aTimeMS);
    IT_Stop();
}
/* End user code. Do not edit comment generated here */
