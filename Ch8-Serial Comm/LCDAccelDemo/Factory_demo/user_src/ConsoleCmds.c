/*-------------------------------------------------------------------------*
 * File:  TestCmds.c
 *-------------------------------------------------------------------------*
 * Description:
 *       Tester command console
 *-------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
 * This software and associated documentation files (the "Software")
 * are copyright 2011 Future Designs, Inc. All Rights Reserved.
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
 * 	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS intERRUPTION)
 * 	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * 	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * 	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * 	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *-------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CG_macrodriver.h"
#include "CG_ad.h"
#include "CG_serial.h"
#include "CG_port.h"
#include "CG_it.h"
#include "CG_int.h"
#include "CG_timer.h"

#include "RDKRL78_spi.h"
#include "Console.h"
#include "ConsoleCmds.h"
#include "lcd.h"


//#define DEMO_ONLY

/*-------------------------------------------------------------------------*
 * Prototypes:
 *-------------------------------------------------------------------------*/

int CommandList(void *aWorkspace, int argc, char *argv[]);
int Verbose_Cmd(void *aWorkspace, int argc, char *argv[]);
int GPIO_Cmd(void *aWorkspace, int argc, char *argv[]);
int Button_Cmd(void *aWorkspace, int argc, char *argv[]);
int Speaker_Cmd(void *aWorkspace, int argc, char *argv[]);
int Accel_Cmd(void *aWorkspace, int argc, char *argv[]);
int Temp_Cmd(void *aWorkspace, int argc, char *argv[]);
int LED_Cmd(void *aWorkspace, int argc, char *argv[]);
int AllLEDs_Cmd(void *aWorkspace, int argc, char *argv[]);
int LightSensor_Cmd(void *aWorkspace, int argc, char *argv[]);
int EEPROM_Cmd(void *aWorkspace, int argc, char *argv[]);
int ADC_Cmd(void *aWorkspace, int argc, char *argv[]);
int POT_Cmd(void *aWorkspace, int argc, char *argv[]);
int MIC_Cmd(void *aWorkspace, int argc, char *argv[]);
int LCD_Cmd(void *aWorkspace, int argc, char *argv[]);
int Loopback_Cmd(void *aWorkspace, int argc, char *argv[]);
int SDCard_Cmd(void *aWorkspace, int argc, char *argv[]);
int DEMO_Cmd(void *aWorkspace, int argc, char *argv[]);

/*-------------------------------------------------------------------------*
 * Globals:
 *-------------------------------------------------------------------------*/
static const T_consoleCmdEntry G_Commands[] = {
        { "?", CommandList },
        { "VERBOSE", Verbose_Cmd},
        { "GPIO", GPIO_Cmd },
        { "BUTTON", Button_Cmd },
        { "ADC", ADC_Cmd },
        { "POT", POT_Cmd },
        { "ACCEL", Accel_Cmd },
        { "TEMP", Temp_Cmd },
		{ "LED", LED_Cmd },
		{ "LEDS", AllLEDs_Cmd },
        { "SPEAKER", Speaker_Cmd },
        { "MIC", MIC_Cmd },
        { "LS", LightSensor_Cmd },
        { "EEPROM", EEPROM_Cmd },
        { "PMOD", Loopback_Cmd},
        { "SDCARD", SDCard_Cmd},
        { "LCD", LCD_Cmd},
        { "DEMO", DEMO_Cmd},
        { 0, 0 } // Place holder for the last one
};

static void *G_Workspace;
uint8_t G_Verbose;
extern volatile UCHAR G_ISRButtonFlag;   // ISR Button Flag
extern volatile int G_msTimer;   // Timer Counter
extern volatile UCHAR G_INTAD_Flag;
extern volatile UCHAR G_IIC_SendingData;
extern volatile UCHAR G_IIC_ReceivingData;

// LEDs
uint8_t LEDPort[] = {
	5, // RLED1
	6, // RLED2
    6, // RLED3
    5, // GLED1
    5, // GLED2
    5, // GLED3
};
	
uint8_t LEDPin[] = {
	5, // RLED1
	2, // RLED2
    3, // RLED3
    2, // GLED1
    3, // GLED2
    4, // GLED3
};

// Buttons
uint8_t G_BtnPort[] = {
    13, 5, 5 };
uint8_t G_BtnPin[] = {
    7, 0, 1 };	

// Speaker
uint16_t G_Notes[] = {
	440,	// A4
	466,	// Bb4
	493,	// B4
	523,	// C4
	554,	// Db4
	587,	// D4
	622,	// Eb4
	659,	// E4
	698,	// F4
	740,	// Gb4
	784,	// G4
	831,	// Ab4
	880		// A5
};


/*---------------------------------------------------------------------------*
 * Command List
 *---------------------------------------------------------------------------
 * Description:
 *      "?" command display output
 *---------------------------------------------------------------------------*/
int CommandList(void *aWorkspace, int argc, char *argv[])
{
	ConsolePrintf("\r\n");
	//ConsolePrintf("SELFTEST		- Runs an automated test on all peripherals\r\n");
    ConsolePrintf("GPIO SET [port] [pin]	- Sets a GPIO Pin\r\n");
	ConsolePrintf("GPIO CLEAR [port] [pin	- Clears a GPIO Pin\r\n");
	ConsolePrintf("GPIO READ [port] [pin]	- Reads a GPIO Pin\r\n");
    ConsolePrintf("BUTTON [SW#]		- Test a button\r\n");
    ConsolePrintf("LED ON [LED #]		- Turns an LED ON\r\n");
	ConsolePrintf("LED OFF [LED #]		- Turns an LED OFF\r\n");
	ConsolePrintf("LEDS ON			- Turns all LEDs ON\r\n");
	ConsolePrintf("LEDS OFF		- Turns all LEDs OFF\r\n");
    ConsolePrintf("LCD [0|1|2]		- Displays several patterns on the screen\r\n");
    ConsolePrintf("TEMP			- Displays the temperature reading in Celsius\r\n");
	ConsolePrintf("TEMP [LOW] [HIGH]	- Prints PASS or FAIL for the given Celsius range\r\n");
	ConsolePrintf("ACCEL			- Displays the accelerometer x, y, and z readings\r\n");
	ConsolePrintf("ACCEL CONFIG		- Displays the accelerometer configuration data\r\n");
    ConsolePrintf("LS			- Displays the abient light sensor Lux. measurement\r\n");
	ConsolePrintf("LS [LOW] [HIGH]		- Prints PASS or FAIL for the given Lux. range\r\n");
    ConsolePrintf("EEPROM			- Runs a 16 Byte write/read test on the EEPROM\r\n");
    ConsolePrintf("ADC [AN#]		- Reads an ADC value\r\n");
	ConsolePrintf("POT 			- Display the POT value as a percent\r\n");
	ConsolePrintf("POT [LOW] [HIGH]	- Prints PASS or FAIL for the given % range\r\n");
	ConsolePrintf("MIC			- Display a single MIC ADC sample\r\n");
	//ConsolePrintf("MIC [time]		- Test the MIC input for [time] seconds\r\n");
    //ConsolePrintf("SPEAKER			- Play chromatic sweep\r\n");
	//ConsolePrintf("SPEAKER [time]		- Play speaker at 1000HZ for [time] seconds\r\n");
	//ConsolePrintf("SPEAKER [time] [freq]	- Play speaker at [freq] HZ for [time] seconds\r\n");
    ConsolePrintf("SDCARD			- Puts SD Card into IDLE STATE and reads response\r\n");
    ConsolePrintf("PMOD			- Runs a loopback test on pins 1, 2, 3, and 4\r\n");
    ConsolePrintf("			  on PMOD1 (Must short pins 1 + 2, and 3 + 4)\r\n");
    ConsolePrintf("DEMO			- Runs a DEMO program with POT volume control,\r\n");
    ConsolePrintf("			  flashing LEDs, and LCD screensaver\r\n");
    return 0;
}


/*---------------------------------------------------------------------------*
 * Verbose Command
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Verbose_Cmd(void *aWorkspace, int argc, char *argv[])
{
	if (argc == 2)
	{
		if(strcmp(argv[1], "ON") == 0)
			G_Verbose = 1;
		else if(strcmp(argv[1], "OFF") == 0)
			G_Verbose = 0;
		else
			ConsolePrintf("FAIL: Second argument must be 'ON' or 'OFF'");
	}
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * GPIO Utility Command
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int GPIO_Cmd(void *aWorkspace, int argc, char *argv[])
{
	uint16_t port;
	uint8_t num;
    if (argc == 4)
    {
		port = atoi(argv[2]);
		num = atoi(argv[3]);
		
		if(strcmp(argv[1], "SET") == 0)
		{
			GPIO_OuputMode(port, num);
			GPIO_SetLow(port, num);
			ConsolePrintf("NOTEST:");
		}
		else if(strcmp(argv[1], "CLEAR") == 0)
		{
			GPIO_OuputMode(port, num);
			GPIO_SetHigh(port, num);
			ConsolePrintf("NOTEST:");
		}
		else if(strcmp(argv[1], "READ") == 0)
		{
			GPIO_InputMode(port, num);
			uint8_t input = GPIO_Read(port, num);
			ConsolePrintf("NOTEST: P%01x%d==%d\r\n", port, num, input);
		}
    } 
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}

/*---------------------------------------------------------------------------*
 * WaitForButton
 *---------------------------------------------------------------------------
 * Description:
 *      
 * Inputs:
 *      aTimeS - Wait time in seconds
 * Outputs:
*      return (uint8_t) - button # that was pressed or 0 if the time expires   
 *---------------------------------------------------------------------------*/
uint8_t WaitForButton(uint32_t aTimeS)
{
	uint32_t s;
	uint8_t i;
	
	// Wait for any previous button to be released
	while(GPIO_Read(G_BtnPort[0], G_BtnPin[0]) == 0);
	while(GPIO_Read(G_BtnPort[1], G_BtnPin[1]) == 0);
	while(GPIO_Read(G_BtnPort[2], G_BtnPin[2]) == 0);
	
	G_ISRButtonFlag = 0;
	
	for(s=0;s<aTimeS;s++)
	{
		for(i=0;i<20;i++)
		{
			if(G_ISRButtonFlag != 0)
				return G_ISRButtonFlag;
			
			delay_ms(50);
		}
	}

	return 0;
}


/*---------------------------------------------------------------------------*
 * Push Button Test
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Button_Cmd(void *aWorkspace, int argc, char *argv[])
{
	if(argc == 2)
	{
		uint8_t bNum = atoi(argv[1]);
	
		if((bNum>0) && (bNum <= 3))
		{
			if(G_Verbose)
				ConsolePrintf("Press SWITCH%d.. ", bNum);

			if(WaitForButton(10) == bNum)
				ConsolePrintf("PASS:\r\n");
			else
				ConsolePrintf("FAIL:\r\n");
		}
		else 
	    {
	        ConsolePrintf("FAIL: Argument must be 1, 2, or 3\r\n");
	    }
	}
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * LoopbackTest
 *---------------------------------------------------------------------------
 * Description:
 *      
 * Inputs:
 *      
 * Outputs:
 *      
 *---------------------------------------------------------------------------*/
uint8_t LoopbackTest(uint8_t oPort, uint8_t oPin, uint8_t iPort, uint8_t iPin)
{
	uint8_t test1, test2;

    CSI10_Stop();
    
	GPIO_InputMode(iPort, iPin);
	GPIO_OuputMode(oPort, oPin);
	
	GPIO_SetHigh(oPort, oPin);
	delay_ms(10);
	test1 = GPIO_Read(iPort, iPin);
	
	GPIO_SetLow(oPort, oPin);
	delay_ms(10);
	test2 = GPIO_Read(iPort, iPin);
	
    CSI10_Start();
    
	if( (test1 == 1) && (test2 == 0) )
	{
        if(G_Verbose)
			ConsolePrintf("PASS: P%01x%d->P%01x%d\r\n", oPort, oPin, iPort, iPin);
			
		return 1;
	}
	else
	{	
		if(G_Verbose)
			ConsolePrintf("FAIL: P%01x%d->P%01x%d\r\n", oPort, oPin, iPort, iPin);
		
		return 0;
	}
}


/*---------------------------------------------------------------------------*
 * Loopback Testing
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Loopback_Cmd(void *aWorkspace, int argc, char *argv[])
{
	if (argc == 1)
    {
		uint32_t passing = 1;

        // PMOD1
		passing &= LoopbackTest(7, 1, 0, 2);    // PMOD1-CS <-> MOSI
		passing &= LoopbackTest(0, 3, 0, 4);    // MISO <-> SCK

		if(passing)
			ConsolePrintf("PASS:\r\n");
		else
			ConsolePrintf("FAIL:\r\n");
		
    } 
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Speaker Testing
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Speaker_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if(argc <= 2)
	{
		uint8_t i;
		if(argc == 1)
			SpeakerON(1, 1);
		else
		{
			if(strcmp(argv[1], "LEFT") == 0)
				SpeakerON(1, 0);
			else if(strcmp(argv[1], "RIGHT") == 0)
				SpeakerON(0, 1);
			else
			{
				ConsolePrintf("FAIL: First argument must be 'LEFT' or 'RIGHT'");
				return 0;
			}
		}
		
		for(i=0;i<13;i++)
		{
			SpeakerSetFreq(G_Notes[i]);
			delay_ms(25);
		}
		SpeakerOFF();
	}
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Microphone Testing
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int MIC_Cmd(void *aWorkspace, int argc, char *argv[])
{
    AD_SelectADChannel((enum ADChannel)MIC_AN_INDEX);
    
    if (argc == 1)
	{
        uint16_t reading;
        
        G_INTAD_Flag = 1;
        AD_Start();
        while(G_INTAD_Flag == 1);
        
        AD_Read((USHORT *)&reading);
		ConsolePrintf("NOTEST: %04X\r\n", reading);
        
        AD_Stop();
	}
	else if (argc == 2)
    {
		int i, s, numSec;
		uint16_t low1 = (uint16_t)0xFFFF;
		uint16_t low2 = (uint16_t)0xFFFF;
		uint16_t high1 = (uint16_t)0;
		uint16_t high2 = (uint16_t)0;
		uint16_t reading;

		numSec = atoi(argv[1]);

		if(G_Verbose)
			ConsolePrintf("Testing Microphone..");
		
        AD_Start();
        
		for(s=0; s<numSec; ++s) {
			
			for (i=0; i<100; i++) {
		        
                G_INTAD_Flag = 1;
                while(G_INTAD_Flag == 1);
                
				AD_Read((USHORT *)&reading);
			
			    if (reading < low1)
			        low1 = reading;
			    if (reading > high1)
			        high1 = reading;
                
                delay_ms(10);
			}
		}
	
		if(G_Verbose)
		{
			ConsolePrintf("\r\nWith Speaker OFF\r\n");
			ConsolePrintf("  Low ADC Reading: %04X\r\n", low1);
			ConsolePrintf("  High ADC Reading: %04X\r\n", high1);
		}
		
		SpeakerSetFreq(G_Notes[11]);
		SpeakerON(1, 1);
		
		for(s=0; s<numSec; ++s) {
			
			for (i=0; i<100; i++) {
		    
                G_INTAD_Flag = 1;
                while(G_INTAD_Flag == 1);
                
				AD_Read((USHORT *)&reading);
			
			    if (reading < low2)
			        low2 = reading;
			    if (reading > high2)
			        high2 = reading;
                
                delay_ms(10);
			}
		}
		
		SpeakerOFF(1, 1);
        AD_Stop();
	
		if(G_Verbose)
		{
			ConsolePrintf("\r\nWith Speaker ON\r\n");
			ConsolePrintf("  Low ADC Reading: %04X\r\n", low2);
			ConsolePrintf("  High ADC Reading: %04X\r\n", high2);
		}
		
		if( ( (low1-low2) > 0x0200) && ( (high2-high1) > 0x0200) )
		{
			ConsolePrintf("PASS:\r\n");
		}
		else
		{
			ConsolePrintf("FAIL:\r\n");
		}
    }  
    else 
    {
        ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * ADC Utility Command
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int ADC_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if (argc == 2)
    {
        uint8_t n;
		uint16_t value;
		n = atoi(argv[1]);
		AD_SelectADChannel((enum ADChannel)n);
        
        G_INTAD_Flag = 1;
        AD_Start();
        while(G_INTAD_Flag == 1);
        
        AD_Read((USHORT *)&value);
		ConsolePrintf("NOTEST: %d\r\n", value);
        
        AD_Stop();
    } 
    else 
    {
        ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Potentiameter Test
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int POT_Cmd(void *aWorkspace, int argc, char *argv[])
{
    uint32_t value;
    
    if (argc == 1)
    {
        AD_SelectADChannel((enum ADChannel)POT_AN_INDEX);
        
        G_INTAD_Flag = 1;
        AD_Start();
        while(G_INTAD_Flag == 1);
        
        AD_Read((USHORT *)&value);
        value *= 100;
        value /= 1023; // Percent Reading
		ConsolePrintf("NOTEST: %d%%\r\n", value);
        
        AD_Stop();
    }
	else if(argc == 3)
	{
		uint16_t low, high;
		low = atoi(argv[1]);
		high = atoi(argv[2]);
		 
        AD_SelectADChannel((enum ADChannel)POT_AN_INDEX);
        AD_Read((USHORT *)&value);
		value *= 100/4095; // Percent Reading
			
		if( (value >= low) && (value <= high) )
			ConsolePrintf("PASS: %d\r\n", value);
		else
			ConsolePrintf("FAIL: %d\r\n", value);
	}
    else 
    {
        ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * WriteIIC
 *---------------------------------------------------------------------------
 * Description:
 *      
 * Inputs:
 *      
 * Outputs:
 *      
 *---------------------------------------------------------------------------*/
void WriteIIC(uint8_t aAddr, uint8_t *aTXData, int aNumBytes)
{
    delay_ms(5);
    G_IIC_SendingData = 1;
    while(IICA0_MasterSendStart(aAddr & ~(0x01), aTXData, aNumBytes, 100) != MD_OK);
    while(G_IIC_SendingData == 1);
}

/*---------------------------------------------------------------------------*
 * ReadIIC
 *---------------------------------------------------------------------------
 * Description:
 *      
 * Inputs:
 *      
 * Outputs:
 *      
 *---------------------------------------------------------------------------*/
void ReadIIC(unsigned char aAddr, unsigned char *aRXData, int aNumBytes)
{
    delay_ms(5);
    G_IIC_ReceivingData = 1;
    while(IICA0_MasterReceiveStart(aAddr | (0x01), aRXData, aNumBytes, 100) != MD_OK);
    while(G_IIC_ReceivingData == 1);
}

/*---------------------------------------------------------------------------*
 * ReadIICReg
 *---------------------------------------------------------------------------
 * Description:
 *      
 * Inputs:
 *      
 * Outputs:
 *      
 *---------------------------------------------------------------------------*/
void ReadIICReg(unsigned char aAddr, unsigned char aReg, unsigned char *aRXData, int aNumBytes)
{
    WriteIIC(aAddr, &aReg, 1);
    ReadIIC(aAddr, aRXData, aNumBytes);
}

void Accel_Init()
{
	uint8_t txData[3];
    
	txData[0] = DATA_FORMAT_REG;		// Full resolution mode  
	txData[1] = DATA_FORMAT;
    WriteIIC(ACCEL_ADDR, txData, 2);
   	
	txData[0] = POWER_CTL_REG;			// Take accelerometer out of standby mode
	txData[1] = PWR_CFG;
	WriteIIC(ACCEL_ADDR, txData, 2);
	
	txData[0] = FIFO_CTL_REG;			// Put FIFO into bypass mode 
	txData[1] = FIFO_CFG;
	WriteIIC(ACCEL_ADDR, txData, 2);
}

/*---------------------------------------------------------------------------*
 * Routine:  AccelRead
 *---------------------------------------------------------------------------*
 * Description:
 *      
 * Outputs:
 *      x axis value
 *      y axis value
 *      z axis value
 *---------------------------------------------------------------------------*/
void AccelRead(int16_t *x, int16_t *y, int16_t *z)
{
	unsigned char rxData[2];
		
	ReadIICReg(ACCEL_ADDR, DATAX_REG, rxData, 2);
	*x = rxData[1] << 8;
	*x += rxData[0];
	
	ReadIICReg(ACCEL_ADDR, DATAY_REG, rxData, 2);
	*y = rxData[1] << 8;
	*y += rxData[0];
	
	ReadIICReg(ACCEL_ADDR, DATAZ_REG, rxData, 2);
	*z = rxData[1] << 8;
	*z += rxData[0];
}


/*---------------------------------------------------------------------------*
 * Accelerometer Test
 *---------------------------------------------------------------------------
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Accel_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if (argc == 1)
    {
		int16_t x=0, y=0, z=0;
        AccelRead(&x, &y, &z);
		ConsolePrintf("NOTEST: (%d, %d, %d)\r\n", x, y, z);
	}
	else if(argc == 2)
	{
		if(strcmp(argv[1], "CONFIG") == 0)
		{
			uint8_t d, p, f;
			ReadIICReg(ACCEL_ADDR, DATA_FORMAT_REG, &d, 1);
			ReadIICReg(ACCEL_ADDR, POWER_CTL_REG, &p, 1);
			ReadIICReg(ACCEL_ADDR, FIFO_CTL_REG, &f, 1);
			
			if(G_Verbose)
			{
				ConsolePrintf("DATA_FORMAT = %02x\r\n", d);
				ConsolePrintf("POWER_CTL = %02x\r\n", p);
				ConsolePrintf("FIFO_CTL = %02x\r\n", f);
			}
			
			if( (d==DATA_FORMAT) && (p==PWR_CFG) && (f == FIFO_CFG) )
			{
				ConsolePrintf("PASS: [%d,%d,%d]==%d,%d,%d\r\n", d, p, f,
					DATA_FORMAT, PWR_CFG, FIFO_CFG);
			}
			else
			{
				ConsolePrintf("FAIL: [%d,%d,%d]!=%d,%d,%d\r\n", d, p, f,
					DATA_FORMAT, PWR_CFG, FIFO_CFG);
			}
		}
		else
		{
			 ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
		}
	}
    else 
    {
        ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Temperature Sensor Test
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int Temp_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if (argc == 1)
    {
        uint8_t readData[] = {0, 0};
		float temp;
        
        ReadIICReg(TEMP_ADDR, TEMP_REG, readData, 2);
		
		temp = ((readData[0] << 8) + readData[1]) * 0.0078;

		ConsolePrintf("NOTEST: %f%cC\r\n", temp, DEGREE_CHAR);
    } 
	else if(argc == 3)
	{
		uint8_t readData[] = {0, 0};
		float temp, low, high;
		low = atoi(argv[1]);
		high = atoi(argv[2]);
		
        ReadIICReg(TEMP_ADDR, TEMP_REG, readData, 2);
		
		temp = ((readData[0] << 8) + readData[1]) * 0.0078;
		
		if( (temp > low) && (temp <= high) )
		{
			ConsolePrintf("PASS: %f%cC\r\n", temp, DEGREE_CHAR);
		}
		else
		{
			ConsolePrintf("FAIL: %f%cC\r\n", temp, DEGREE_CHAR);
		}
	}
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Ambient Light Sensor Test
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int LightSensor_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if( (argc == 1) || (argc == 3) )
    {
        uint16_t Lux;
        unsigned char instrCode;
        unsigned char readData[] = {
            0,  // LSB
            0   // MSB
        }; 

        instrCode = LS_INSTR;
        WriteIIC(LS_ADDR, &instrCode, 1);
        
        ReadIIC(LS_ADDR, readData, 1);
        
        Lux = ((readData[1] << 8) + readData[0]);
        
        if (argc == 1)
            ConsolePrintf("NOTEST: %d\r\n", Lux);
        else // argc == 3
        {
            float low, high;
            low = atoi(argv[1]);
            high = atoi(argv[2]);
            
            if( (Lux > low) && (Lux <= high) )
                ConsolePrintf("PASS: %d\r\n", Lux);
            else
                ConsolePrintf("FAIL: %d\r\n", Lux);
        }

    } // if(argc == 1) || (argc == 3)
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


uint8_t EEPROMData[] = {
    0x00, 0x00,             // Address Bytes
    0x01, 0x02, 0x03, 0x04, // dummy data
    0x05, 0x06, 0x07, 0x08, // dummy data
    0xFF, 0xEF, 0xDF, 0xCF, // dummy data
    0xBF, 0xAF, 0x9F, 0x8F  // dummy data
};

/*---------------------------------------------------------------------------*
 * EEPROM Test Command
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int EEPROM_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if( (argc == 1) || (argc == 3) )
    {
        uint8_t i = 0;
        uint8_t result = 1;
        uint8_t readData[16];
        
        WriteIIC(EEPROM_ADDR, EEPROMData, 18);
        
        WriteIIC(EEPROM_ADDR, EEPROMData, 2);
        ReadIIC(EEPROM_ADDR, readData, 16);
        
        for(i=0; i<16; i++)
        {   
            if(readData[i] == EEPROMData[i+2])
            {
                if(G_Verbose)
                    ConsolePrintf("%02x == %02x\r\n", readData[i], EEPROMData[i+2]);
            }
            else
            {
                if(G_Verbose)
                    ConsolePrintf("%02x != %02x\r\n", readData[i], EEPROMData[i+2]);
                result = 0;
            }
        }
    
        if( result == 1 )
            ConsolePrintf("PASS: \r\n");
        else
            ConsolePrintf("FAIL: \r\n");
           
    } // if(argc == 1) || (argc == 3)
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Single LED Command
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int LED_Cmd(void *aWorkspace, int argc, char *argv[])
{
	int n;
	
    if (argc == 3)
    {
		n = atoi(argv[2]);
		if(n>=0 && n<6)
		{
			if(strcmp(argv[1], "ON") == 0)
				GPIO_SetLow(LEDPort[n], LEDPin[n]);
			else if(strcmp(argv[1], "OFF") == 0)
				GPIO_SetHigh(LEDPort[n], LEDPin[n]);
			else
				ConsolePrintf("FAIL: First argument must be 'ON' or 'OFF'");
		}
		else
		{
			ConsolePrintf("FAIL: Second argument must be between 0 and 5");
		}
    }  
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * LED Test Command
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int AllLEDs_Cmd(void *aWorkspace, int argc, char *argv[])
{
	int n;
	
    if (argc == 2)
    {
		if(strcmp(argv[1], "ON") == 0)
		{
			for(n=0; n<6; ++n)
			{
				GPIO_SetLow(LEDPort[n], LEDPin[n]);
				delay_ms(50);
			}
		}
		else if(strcmp(argv[1], "OFF") == 0)
		{
			for(n=0; n<6; ++n)
			{
				GPIO_SetHigh(LEDPort[n], LEDPin[n]);
				delay_ms(50);
			}
		}
		else
		{
			ConsolePrintf("FAIL: Argument must be ON or OFF\n");
		}
    }  
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\n");
    }
    return 0;
}





/*---------------------------------------------------------------------------*
 * LCD Test Command
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int LCD_Cmd(void *aWorkspace, int argc, char *argv[])
{
	if (argc == 2)
	{	
		uint8_t value = atoi(argv[1]);
		
		switch(value)
		{
			case 0:
                LCDClear();
				LCDFont(FONT_LOGOS);
                LCDChar(0, (LCD_W-80)-10, 0);
                LCDFont(FONT_SMALL);
                LCDString("RL78 RDK", LCDRight(8)-10, 20);
				break;
			case 1:
				LCDTest();
				break;
			case 2:
				LCDInvert();
				break;
			default:
				ConsolePrintf("FAIL: Incorrect parameters\r\n");
				break;
		}
	}
    else 
    {
        ConsolePrintf("FAIL: Incorrect parameters\r\n");
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * CD Card Test Command
 *---------------------------------------------------------------------------*
 * Description:
 *      
 *---------------------------------------------------------------------------*/
int SDCard_Cmd(void *aWorkspace, int argc, char *argv[])
{
    if (argc == 1)
    {
		uint8_t txData[9];
        uint8_t rxData[9];
		uint8_t tryNum;		
		for(tryNum=0; tryNum<10; tryNum++)
		{
			txData[0] = SD_GO_IDLE_CMD;
			txData[1] = 0;
			txData[2] = 0;
			txData[3] = 0;
			txData[4] = 0;
			txData[5] = SD_GO_IDLE_CRC;
            txData[6] = 0;
            txData[7] = 0;
            txData[8] = 0;
			
            SPI_SendReceive(SPI_SD, txData, 9, rxData);
			
			if(rxData[7] == 0x01)
				break;
				
			delay_ms(10);
		}
		
		if(G_Verbose)
		{
			ConsolePrintf("Response: 0x%02x (try# %d)\r\n", rxData[7], tryNum);
		}
		
		if(rxData[7] == 0x01)
			ConsolePrintf("PASS: 0x%02x==0x01\r\n", rxData[7]);
		else
			ConsolePrintf("FAIL: 0x%02x!=0x01\r\n", rxData[7]);
    }  
    else 
    {
        ConsoleSendString(aWorkspace, "FAIL: Incorrect parameters\n");
    }
    return 0;
}


int DEMO_Cmd(void *aWorkspace, int argc, char *argv[])
{
    int8_t dirX, dirY;
    int16_t x, y;
    uint32_t value;
    uint8_t i, j, animMode, toggle, ledMode = 0;
    
    LCDStringLinePos("SW1: POT Volume", 0, 6);
    LCDStringLinePos("SW2: Animate LEDS", 0, 7);
    LCDStringLinePos("SW3: Animate LCD", 0, 8);
    
    i = 0;
    j = 0;
    toggle = 0;
    dirX = -8;
    dirY = 1;
    G_ISRButtonFlag = 0;
    animMode = 0;
    while(1)
    {
        if(G_ISRButtonFlag != 0)
        {
            ledMode = G_ISRButtonFlag-1;
            G_ISRButtonFlag = 0;
            
            for(i = 0; i < 6; i++)
            {
                GPIO_SetHigh(LEDPort[i], LEDPin[i]);
            }
            
            LCDClear();
            LCDFont(FONT_LOGOS);
            LCDChar(0, (LCD_W-80)-10, 0);
            LCDFont(FONT_SMALL);
            LCDString("RL78 RDK", LCDRight(8)-10, 20);
            LCDStringLinePos("SW1: POT Volume", 0, 6);
            LCDStringLinePos("SW2: Animate LEDS", 0, 7);
            LCDStringLinePos("SW3: Animate LCD", 0, 8);
        }
        
        if(ledMode == 0)
        {
            AD_SelectADChannel((enum ADChannel)POT_AN_INDEX);
        
            G_INTAD_Flag = 1;
            AD_Start();
            while(G_INTAD_Flag == 1);
            
            AD_Read((USHORT *)&value);
            value *= 100;
            value /= 1023; // Percent Reading
            
            for(i = 0; i < 6; i++)
            {
                if(value < (100-16*i) )
                    GPIO_SetHigh(LEDPort[i], LEDPin[i]);
                else
                    GPIO_SetLow(LEDPort[i], LEDPin[i]);
            }
           
            AD_Stop();
            
            delay_ms(10);
        }
        else if(ledMode == 1)
        {
            if(animMode == 0)
            {
                if(i>5)
                {
                    i = 0;
                    toggle = ~toggle;
                }
                
                if(toggle)
                    GPIO_SetLow(LEDPort[i], LEDPin[i]);
                else
                    GPIO_SetHigh(LEDPort[i], LEDPin[i]);

                i++;
                
                delay_ms(250);
            }
            else if(animMode == 1)
            {
                toggle = ~toggle;
                
                for(i = 0; i < 6; i++)
                {
                    if(i%2 == 0)
                    {
                        if(toggle)
                            GPIO_SetHigh(LEDPort[i], LEDPin[i]);
                        else
                            GPIO_SetLow(LEDPort[i], LEDPin[i]);
                    }
                    else
                    {
                        if(toggle)
                            GPIO_SetLow(LEDPort[i], LEDPin[i]);
                        else
                            GPIO_SetHigh(LEDPort[i], LEDPin[i]);
                    }
                }
                
                delay_ms(250);
            }
            else
            {
                toggle = ~toggle;
                
                for(i = 0; i < 6; i++)
                {
                    if(toggle)
                        GPIO_SetLow(LEDPort[i], LEDPin[i]);
                    else
                        GPIO_SetHigh(LEDPort[i], LEDPin[i]);

                }
                
                delay_ms(100);
            }
            
            if(j > 20)
            {
                animMode++;
                if(animMode > 2)
                  animMode = 0;
                
                j = 0;
            }
            j++;
        }
        else
        {
            x += dirX;
            y += dirY;
            
            if(x >= LCD_W-80)
            {
                x = LCD_W-80;
                dirX = -8;
            }
            else if(x < 0)
            {
                x = 0;
                dirX = 8;
            }
            
            if(y >= 3)
            {
                y = 3;
                dirY = -1;
            }
            else if(y < 0)
            {
                y = 0;
                dirY = 1;
            }
            
            LCDClear();
            LCDFont(FONT_LOGOS);
            LCDChar(0, x, y);
            
            delay_ms(2000);
        }
    }
}


/*---------------------------------------------------------------------------*
 * Routine:  StartCmdConsole
 *---------------------------------------------------------------------------*
 * Description:
 *      Start up  Command Console on device "Console" or return an error.
 * Outputs:
 *      T_uezError -- Error code if any.
 *---------------------------------------------------------------------------*/
void StartCmdConsole(void)
{
#ifdef DEMO_ONLY
    char *argv[1];
#endif
    UART0_Start();

    G_Verbose = 1;
    
    CSI10_Start();
    
    LCDInit();
    LCDFont(FONT_LOGOS);
	LCDChar(0, (LCD_W-80)-10, 0);
	LCDFont(FONT_SMALL);
	LCDString("RL79 RDK", LCDRight(8)-10, 20);
        
    INTP0_Enable(); // SW1 Interrupt
    INTP1_Enable(); // SW2 Interrupt
    INTP2_Enable(); // SW3 Interrupt
    
    // IT Interrupt Priority HIGH
    ITPR1 = 0U;
	ITPR0 = 0U;

    Accel_Init();
    
#ifndef DEMO_ONLY
    ConsolePrintf("RL78 Console\r\n");
    ConsolePrintf("Press '?' for a list of commands.\r\n");
#endif
    
    // Start FDI Cmd Console
    G_Workspace = 0;
    ConsoleStart(&G_Workspace, G_Commands);

#ifdef DEMO_ONLY
    DEMO_Cmd(G_Workspace, 1, argv);
#endif
    
    ConsoleTask(G_Workspace);
}

/*-------------------------------------------------------------------------*
 * File:  TestCmds.c
 *-------------------------------------------------------------------------*/
