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
* Filename:	CG_wdt.h
* Abstract:	This file implements device driver for WDT module.
* APIlib:	Applilet3 for RL78/G13 E1.00b [14 Jan 2011]
* Device:	R5F100LE
* Compiler:	IAR Systems iccrl78
* Creation date:	9/21/2011
*******************************************************************************
*/

#ifndef _MDWDT_
#define _MDWDT_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void WDT_Init(void);
void WDT_Restart(void);
__interrupt void MD_INTWDTI(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
