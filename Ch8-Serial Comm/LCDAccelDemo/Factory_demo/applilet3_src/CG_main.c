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
* Filename:	CG_main.c
* Abstract:	This file implements main function.
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
#include "CG_system.h"
#include "CG_port.h"
#include "CG_int.h"
#include "CG_serial.h"
#include "CG_timer.h"
#include "CG_wdt.h"
#include "CG_it.h"
/* Start user code for include. Do not edit comment generated here */
#include <stdint.h>
#include "lcd.h"
#include "glyph_api.h"

/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Set option bytes */
#pragma location = "OPTBYTE"
__root const UCHAR opbyte0 = 0xEFU;
#pragma location = "OPTBYTE"
__root const UCHAR opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const UCHAR opbyte2 = 0xE8U;
#pragma location = "OPTBYTE"
__root const UCHAR opbyte3 = 0x04U;

/* Set security ID */
#pragma location = "SECUID"
__root const UCHAR secuid[10] = 
	{0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
/* Start user code for global. Do not edit comment generated here */

/* Accelerometer constants */
#define ACCEL_WADDR         0x3A
#define ACCEL_RADDR         0x3B
#define ACCEL_REG_PWRCTL    0x2D
#define ACCEL_REG_DATASTART 0x32
#define ACCEL_CTL_MEASURE   0x08

/* Globals for the indicator location */
extern int32_t G_ind_x;
extern int32_t G_ind_y;
extern int32_t G_ind_x_next;
extern int32_t G_ind_y_next;

/* Global for the screen refresh ready indicator */
extern unsigned char drawlcd;
extern signed char mute;

/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function implements main function.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void  main(void)
{
  /* Start user code. Do not edit comment generated here */
  unsigned char i2cbuf[6];/* Buffer for I2C transactions */
  signed int datax = 0;   /* x axis acceleration */
  signed int datay = 0;   /* y axis acceleration */
  signed int dataz = 0;   /* z axis acceleration */

  __low_level_init();     /* Initialize peripherals */
  TAU0_Channel2_Start();  /* Start the screen redrawing timer */

  CSI10_Start();          /* LCD SPI initialization */
  LCDInit();              /* Clear LCD, set fonts*/

  INTP2_Enable();         /* Enable the mute button interrupt */

  /* Set the 'measure' bit to turn on accelerometer */
  i2cbuf[0] = ACCEL_REG_PWRCTL;
  i2cbuf[1] = ACCEL_CTL_MEASURE;
  IICA0_MasterSendStart(ACCEL_WADDR, i2cbuf, 2, 32);
  while (IICBSY0)
	;        /* Busy-wait until previous I2C TX is done */

  while (1) {
	/*** ACCELEROMETER HANDLING ***/

	/* Inform accelerometer of starting address at which to read next */
	i2cbuf[0] = ACCEL_REG_DATASTART; 
	IICA0_MasterSendStart(ACCEL_WADDR, i2cbuf, 1, 32);
	while (IICBSY0);    /* Busy-wait until previous I2C TX is done */

	/* Read axis data (three at 2 bytes each) from the accelerometer */
	IICA0_MasterReceiveStart(ACCEL_RADDR, i2cbuf, 6, 32);
	while (IICBSY0);    /* Busy-wait until previous I2C RX is done */
 
	/* Convert the returned x and y data bytes into signed data */
	datax = ((signed int)i2cbuf[1] << 8) | i2cbuf[0];
	datay = ((signed int)i2cbuf[3] << 8) | i2cbuf[2];
	dataz = ((signed int)i2cbuf[5] << 8) | i2cbuf[4];
         
            
	/*** LCD HANDLING ***/
            
	/* Update LCD if the timer allows */
	if (drawlcd) {
	  LCDPrintf(1,0, "X:%3d", datax);
	  LCDPrintf(2,0, "Y:%3d", datay);
	  LCDPrintf(3,0, "Z:%3d", dataz);
	  drawlcd = 0;
	}

  }
  /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */ 
/* End user code. Do not edit comment generated here */
