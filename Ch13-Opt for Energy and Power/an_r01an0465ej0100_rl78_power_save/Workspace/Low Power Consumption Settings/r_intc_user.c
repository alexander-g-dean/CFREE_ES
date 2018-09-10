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
* File Name : r_intc_user.c
* Version : 1.0
* Device(s) : R5F100LE
* H/W Platform : QB-R5F100LE-TB
* Description : This file implements device driver for INTC module.
******************************************************************************/
/******************************************************************************
* History : DD.MM.YYYY Version Description
* : 15.09.2011 1.00 First Release
******************************************************************************/

/*
*******************************************************************************
** Pragma directive
*******************************************************************************
*/
// #pragma interrupt INTP0 R_INTC0_Interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
Includes <System Includes> , ÅgProject IncludesÅh
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
* Function Name: R_INTC0_Interrupt
* Description : This function is INTP0 interrupt service routine.
* Arguments : None
* Return Value : None
******************************************************************************/
#pragma vector = INTP0_vect
__interrupt static void R_INTC0_Interrupt(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/******************************************************************************
End of function R_INTC0_Interrupt
******************************************************************************/

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
