// RDKRL78_spi.c
#include <stdbool.h>
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_serial.h"
#include "r_cg_it.h"
#include "RDKRL78_spi.h"

extern volatile uint8_t g_SPI_SendingData; //spi busy flag
extern volatile uint8_t g_SPI_ReceivingData; //spi busy flag

unsigned char *SPI_CS_Port[] = {
    (unsigned char *)&P1, // LCD-CS    P10
    (unsigned char *)&P3, // SD-CS     P30
    (unsigned char *)&P7, // PMOD1-CS  P71
    (unsigned char *)&P7  // PMOD2-CS  P72
};

uint8_t SPI_CS_Pin[] = {
    0, // LCD-CS    P10
    0, // SD-CS     P30
    1, // PMOD1-CS  P71
    2  // PMOD2-CS  P72
};


void IO_Reset();

void SPI_Init()
{
    IO_Reset();
    
    R_CSI10_Create();
    R_CSI10_Start();
}

void IO_Reset()
{
    volatile int i = 0;
    
	//#warning RESET-IO must be inverted for actual HW
	P13 |= (1<<0); // Assert P130 (#RESET-IO)
    for (i=0;i<10000;i++);
    P13 &= ~(1<<0);  // Deassert P130 (#RESET-IO)
    for (i=0;i<10000;i++);
}

void SPI_CS_Start(uint8_t aDevice)
{
	*SPI_CS_Port[aDevice] &= ~(1<<SPI_CS_Pin[aDevice]);
}

void SPI_CS_End(uint8_t aDevice)
{
	*SPI_CS_Port[aDevice] |= (1<<SPI_CS_Pin[aDevice]);
}

void SPI_Send(uint8_t aDevice, uint8_t *aData, uint32_t aLength)
{
    uint8_t noRXData;
		g_SPI_SendingData = 1;
		g_SPI_ReceivingData = 0;
	
		SPI_CS_Start(aDevice);

    R_CSI10_Send_Receive(aData, aLength, &noRXData);
    while(g_SPI_SendingData);
    
    SPI_CS_End(aDevice);
}

void SPI_SendReceive(uint8_t aDevice, uint8_t *aTXData, uint32_t aTXLength, uint8_t *aRXData)
{
		g_SPI_SendingData = 1;
		g_SPI_ReceivingData = 1;
	
		SPI_CS_Start(aDevice);
   
    R_CSI10_Send_Receive(aTXData, aTXLength, aRXData);
    while(g_SPI_SendingData || g_SPI_ReceivingData);
    
		SPI_CS_End(aDevice);
}

