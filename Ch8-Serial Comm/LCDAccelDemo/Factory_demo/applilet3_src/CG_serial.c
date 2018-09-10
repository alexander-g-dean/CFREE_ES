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
* Filename:	CG_serial.c
* Abstract:	This file implements device driver for Serial module.
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
#include "CG_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
volatile UCHAR  *gpCsi10RxAddress;	/* csi10 receive buffer address */
volatile USHORT gCsi10RxLen;		/* csi10 receive data length */
volatile USHORT gCsi10RxCnt;		/* csi10 receive data count */
volatile UCHAR  *gpCsi10TxAddress;	/* csi10 send buffer address */
volatile USHORT gCsi10TxLen;		/* csi10 send data length */
volatile USHORT gCsi10TxCnt;		/* csi10 send data count */
volatile UCHAR	gIica0MasterStatusFlag;	/* iica0 master flag */
volatile UCHAR	gIica0SlaveStatusFlag;	/* iica0 slave flag */
volatile UCHAR*	gpIica0RxAddress;	/* iica0 receive buffer address */
volatile USHORT	gIica0RxLen;		/* iica0 receive data length */
volatile USHORT	gIica0RxCnt;		/* iica0 receive data count */
volatile UCHAR*	gpIica0TxAddress;	/* iica0 send buffer address */
volatile USHORT	gIica0TxCnt;		/* iica0 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the SAU0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void SAU0_Init(void)
{
	SAU0EN = 1U;	/* supply SAU0 clock */
	NOP();
	NOP();
	NOP();
	NOP();
	SPS0 = _0002_SAU_CK00_FCLK_2 | _0000_SAU_CK01_FCLK_0;
	CSI10_Init();
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the CSI10 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI10_Init(void)
{
	ST0 |= _0004_SAU_CH2_STOP_TRG_ON;	/* disable CSI10 */
	CSIMK10 = 1U;	/* disable INTCSI10 interrupt */
	CSIIF10 = 0U;	/* clear INTCSI10 interrupt flag */
	/* Set INTCSI10 low priority */
	CSIPR110 = 1U;
	CSIPR010 = 1U;
	SIR02 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;	/* clear error flag */
	SMR02 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
	SCR02 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
	SDR02 = _FE00_CSI10_DIVISOR;
	SO0 |= _0400_SAU_CH2_CLOCK_OUTPUT_1;	/* CSI10 clock initial level */
	SO0 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;	/* CSI10 SO initial level */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;	/* enable CSI10 output */
	/* Set SI10 pin */
	PMC0 &= 0xF7U;
	PM0 |= 0x08U;
	/* Set SO10 pin */
	P0 |= 0x04U;
	PMC0 &= 0xFBU;
	PM0 &= 0xFBU;
	/* Set SCK10 pin */
	P0 |= 0x10U;
	PM0 &= 0xEFU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the CSI10 module operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI10_Start(void)
{
	CSIIF10 = 0U;	/* clear INTCSI10 interrupt flag */
	CSIMK10 = 0U;	/* enable INTCSI10 */
	SO0 |= _0400_SAU_CH2_CLOCK_OUTPUT_1;	/* CSI10 clock initial level */
	SO0 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;	/* CSI10 SO initial level */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;	/* enable CSI10 output */
	SS0 |= _0004_SAU_CH2_START_TRG_ON;	/* enable CSI10 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the CSI10 module operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI10_Stop(void)
{
	ST0 |= _0004_SAU_CH2_STOP_TRG_ON;	/* disable CSI10 */
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;	/* disable CSI10 output */
	CSIMK10 = 1U;	/* disable INTCSI10 interrupt */
	CSIIF10 = 0U;	/* clear INTCSI10 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function sends and receives CSI10 data.
**
**  Parameters:
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**	rxbuf: receive buffer pointer
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CSI10_SendReceiveData(UCHAR *txbuf, USHORT txnum, UCHAR *rxbuf)
{
	MD_STATUS status = MD_OK;

	if (txnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gCsi10TxCnt = txnum;	/* send data count */
		gpCsi10TxAddress = txbuf;	/* send buffer pointer */
		gpCsi10RxAddress = rxbuf;	/* receive buffer pointer */
		CSIMK10 = 1U;	/* disable INTCSI10 interrupt */
		SIO10 = *gpCsi10TxAddress;	/* started by writing data to SDR[7:0] */
		gpCsi10TxAddress++;
		gCsi10TxCnt--;
		CSIMK10 = 0U;	/* enable INTCSI10 interrupt */
	}

	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the IICA0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IICA0_Init(void)
{
	IICA0EN = 1U;	/* supply IICA0 clock */
	IICE0 = 0U;	/* disable IICA0 operation */
	IICAMK0 = 1U;	/* disable INTIICA0 interrupt */
	IICAIF0 = 0U;	/* clear INTIICA0 interrupt flag */
	/* Set INTIICA0 low priority */
	IICAPR10 = 1U;
	IICAPR00 = 1U;	
	/* Set SCLA0, SDAA0 pin */
	P6 &= 0xFCU;
	PM6 |= 0x03U;
	SMC0 = 0U;
	IICWL0 = _97_IICA0_IICWL_VALUE;
	IICWH0 = _AA_IICA0_IICWH_VALUE;
	IICCTL01 &= (UCHAR)~_01_IICA_fCLK_HALF;
	SVA0 = _10_IICA0_MASTERADDRESS;
	STCEN0 = 1U;
	IICRSV0 = 1U;
	SPIE0 = 0U;
	WTIM0 = 1U;
	ACKE0 = 1U;
	IICAMK0 = 0U;
	IICE0 = 1U;
	LREL0 = 1U;
	/* Set SCLA0, SDAA0 pin */
	PM6 &= 0xFCU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops IICA0 module operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IICA0_Stop(void)
{
	IICE0 = 0U;	/* disable IICA0 operation */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function set IICA0 stop condition flag.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void IICA0_StopCondition(void)
{
	SPT0 = 1U;	/* set stop condition flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts to send data as master mode.
**
**  Parameters:
**	adr: set address for select slave
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**	wait: wait for start condition
**
**  Returns:
**	MD_OK
**	MD_ERROR1
**	MD_ERROR2
**
**-----------------------------------------------------------------------------
*/
MD_STATUS IICA0_MasterSendStart(UCHAR adr, UCHAR *txbuf, USHORT txnum, UCHAR wait)
{
	MD_STATUS status = MD_OK;

	IICAMK0 = 1U;	/* disable INTIICA0 interrupt */
	if (IICBSY0 == 1U)
	{
		/* Check bus busy */
		IICAMK0 = 0U;	/* enable INTIICA0 interrupt */
		status = MD_ERROR1;
	}	
	else if ((SPT0 == 1U) || (STT0 == 1U)) 
	{
		/* Check trigger */
		IICAMK0 = 0U;	/* enable INTIICA0 interrupt */	
		status = MD_ERROR2;
	}
	else
	{
		STT0 = 1U;	/* send IICA0 start condition */
		IICAMK0 = 0U;	/* enable INTIICA0 interrupt */
		/* Wait */
		while (wait--)
		{
			;
		}
		/* Set parameter */
		gIica0TxCnt = txnum;
		gpIica0TxAddress = txbuf;
		gIica0MasterStatusFlag = _00_IICA_MASTER_FLAG_CLEAR;
		adr &= (UCHAR)~0x01U;	/* set send mode */
		IICA0 = adr;	/* send address */
	}

  	return (status);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts to receive IICA0 data as master mode.
**
**  Parameters:
**	adr: set address for select slave
**	rxbuf: receive buffer pointer
**	rxnum: buffer size
**	wait: wait for start condition
**
**  Returns:
**	MD_OK
**	MD_ERROR1
**	MD_ERROR2
**
**-----------------------------------------------------------------------------
*/
MD_STATUS IICA0_MasterReceiveStart(UCHAR adr, UCHAR *rxbuf, USHORT rxnum, UCHAR wait)
{
	MD_STATUS status = MD_OK;

	IICAMK0 = 1U;	/* disable INTIIA0 interrupt */
	if (IICBSY0 == 1U)
	{
		/* Check bus busy */
		IICAMK0 = 0U;	/* enable INTIIA0 interrupt */
		status = MD_ERROR1;
	}	
	else if ((SPT0 == 1U) || (STT0 == 1U))
	{
		/* Check trigger */
		IICAMK0 = 0U;	/* enable INTIICA0 interrupt */
		status = MD_ERROR2;
	}
	else
	{
		STT0 = 1U;	/* set IICA0 start condition */
		IICAMK0 = 0U;	/* enable INTIIA0 interrupt */
		/* Wait */
		while (wait--)
		{
			;
		}
		/* Set parameter */
		gIica0RxLen = rxnum;
		gIica0RxCnt = 0U;
		gpIica0RxAddress = rxbuf;
  		gIica0MasterStatusFlag  = _00_IICA_MASTER_FLAG_CLEAR;
		adr |= 0x01U;	/* set receive mode */
		IICA0 = adr;	/* receive address */
	}

	return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
