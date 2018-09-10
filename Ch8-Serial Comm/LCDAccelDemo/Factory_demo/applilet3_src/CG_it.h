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
* Filename:	CG_it.h
* Abstract:	This file implements device driver for IT module.
* APIlib:	Applilet3 for RL78/G13 E1.00b [14 Jan 2011]
* Device:	R5F100LE
* Compiler:	IAR Systems iccrl78
* Creation date:	9/21/2011
*******************************************************************************
*/

#ifndef _MDIT_
#define _MDIT_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/* 
	Interval timer control register (ITMC)
*/
/* Interval timer operation enable/disable specification (RINTE) */
#define	_0000_IT_OPERATION_DISABLE	0x0000U	/* disable interval timer operation */
#define	_8000_IT_OPERATION_ENABLE	0x8000U	/* enable interval timer operation */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* Interval timer compare 11 - 0 (ITMCMP11 - 0) */
#define _000E_ITMCMP_VALUE		0x000EU
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void IT_Init(void);
void IT_Start(void);
void IT_Stop(void);
void IT_ChangeTimerCondition(USHORT regvalue);
__interrupt void MD_INTIT(void);

/* Start user code for function. Do not edit comment generated here */
void delay_ms(int aTimeMS);
/* End user code. Do not edit comment generated here */
#endif
