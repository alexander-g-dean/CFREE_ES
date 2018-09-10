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
* File Name : r_cgc_user.c
* Version : 1.0
* Device(s) : R5F100LE
* H/W Platform : QB-R5F100LE-TB
* Description : This file implements device driver for CGC module.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/* Start user code for adding. Do not edit comment generated here */
/******************************************************************************
* Function Name: R_CGC_Set_fCLK
* Description : This function changes clock generator operation mode.
* Arguments : mode: Clock generator operation mode
* Return Value : MD_OK
                 MD_ARGERROR
******************************************************************************/
MD_STATUS R_CGC_Set_fCLK(enum ClockMode mode)
{
	MD_STATUS status = MD_OK;
	uint32_t i;

	switch (mode)
	{
		/***********************************************
			Internal high-speed oscillator
		***********************************************/
		case	HIOCLK:
			if(HIOSTOP == 1)	/* fIH operating ? */
			{					/* No */
				HIOSTOP = 0;		/* Start fIH operation */

				CSS = 0;			/* Select fIH as fCLK */
				while(CLS != 0){}	/* Wait for fCLK change into fIH */

				XTSTOP = 1;			/* Stop fSUB operation */
			}
			break;

		/***********************************************
			Subsystem clock oscillator
		***********************************************/
		case	SUBXT1CLK:
			XTSTOP = 0;			/* Start fSUB operation */

			/* Software wait 1s or more */
			for( i = 0; i <= 60000; i++ )
			{
				NOP();
			}

			CSS = 1;			/* Select fSUB as fCLK */
			while(CLS != 1){}	/* Wait for fCLK change into fSUB */

			HIOSTOP = 1;		/* Stop fIH operation */

			break;

		/***********************************************
			Another clock = Argument error
		***********************************************/
		default:
			status = MD_ARGERROR;	/* Return argument error */
			break;
	}

	return (status);
}
/******************************************************************************
End of function R_CGC_Set_fCLK
******************************************************************************/
/* End user code. Do not edit comment generated here */
