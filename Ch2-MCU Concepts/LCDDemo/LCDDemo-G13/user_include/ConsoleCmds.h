/*-------------------------------------------------------------------------*
 * File:  TestCmds.h
 *-------------------------------------------------------------------------*
 * Description:
 *      FDI console commands
 *-------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
 * This software and associated documentation files (the "Software")
 * are copyright 2010 Future Designs, Inc. All Rights Reserved.
 *
 * A copyright license is hereby granted for redistribution and use of
 * the Software in source and binary forms, with or without modification,
 * provided that the following conditions are met:
 * 	-   Redistributions of source code must retain the above copyright
 *      notice, this copyright license and the following disclaimer.
 * 	-   Redistributions in binary form must reproduce the above copyright
 *      notice, this copyright license and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 * 	-   Neither the name of Future Designs, Inc. nor the names of its
 *      subsidiaries may be used to endorse or promote products
 *      derived from the Software without specific prior written permission.
 *
 * 	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * 	CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * 	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * 	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * 	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * 	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * 	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * 	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * 	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * 	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * 	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * 	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * 	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *-------------------------------------------------------------------------*/
#ifndef _CONSOLE_CMDS_H_
#define _CONSOLE_CMDS_H_

#define MIC_AN_INDEX    3
#define POT_AN_INDEX    4

#define IIC_TIMEOUT_MS   100

// Light Sensor
#define LS_ADDR         0x72u
#define LS_INSTR        0x51

// Serial EEPROM
#define EEPROM_ADDR     0xA0u   // Slave Address (Write)
#define EEPROM_A16      0x02    // A16 of memory address    

// Accelerometer
#define ACCEL_ADDR		0x3Au

#define DATA_FORMAT_REG 0x31u   
#define POWER_CTL_REG  	0x2Du
#define FIFO_CTL_REG   	0x38u
#define DATAX_REG       0x32u
#define DATAY_REG       0x34u
#define DATAZ_REG       0x36u

#define SELF_TEST       0x80u
#define DATA_FORMAT     0x03u
#define PWR_CFG     	0x08u
#define FIFO_CFG     	0x00u

// Temperature Sensor
#define TEMP_ADDR	0x90
#define TEMP_REG	0x00
#define DEGREE_CHAR	186

// SD Card
#define SD_SEND_STATUS 0x13
#define SD_GO_IDLE_CMD	0x40
#define SD_GO_IDLE_CRC	0x95


void StartCmdConsole(void);

#endif // _GFX_TEST_CMDS_H_
/*-------------------------------------------------------------------------*
 * End of File:  ConsoleCmds.h
 *-------------------------------------------------------------------------*/
