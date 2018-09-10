// RDKRL78_spi.c
#include <stdbool.h>
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_serial.h"
#include "r_cg_it.h"
#include "RDKRL78_spi.h"

extern volatile uint8_t G_SPI_SendingData; //spi busy flag
extern volatile uint8_t G_SPI_ReceivingData; //spi busy flag

#ifdef RDKRL78G13
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
#endif
#ifdef RDKRL78G14
unsigned char *SPI_CS_Port[] = {
    (unsigned char *)&P14, // LCD-CS    P145
    (unsigned char *)&P14, // SD-CS     P142
};

uint8_t SPI_CS_Pin[] = {
    5, // LCD-CS    P145
    2, // SD-CS     P142
};
#endif


void IO_Reset();

void SPI_Init()
{
    IO_Reset();
    
    CSI_CREATE();
    CSI_START();
}

void IO_Reset()
{
    volatile int i = 0;
    
		//#warning RESET-IO must be inverted for actual HW
		RESET_IO_PORT |= (1<<RESET_IO_BIT_POS);
		// P13 |= (1<<0); // Assert #RESET-IO
    for (i=0;i<10000;i++)
			;
		RESET_IO_PORT &= !(1<<RESET_IO_BIT_POS);
		//    P13 &= ~(1<<0);  // Deassert #RESET-IO
    for (i=0;i<10000;i++)
			;
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
		volatile uint16_t d;

    uint8_t noRXData;
		G_SPI_SendingData = 1;
		G_SPI_ReceivingData = 0;
	
		SPI_CS_Start(aDevice);

		for (d=100; d>0; d--) // delay
			;

    CSI_SEND_RECEIVE(aData, aLength, &noRXData);
    while(G_SPI_SendingData);
    
    SPI_CS_End(aDevice);
}

void SPI_SendReceive(uint8_t aDevice, uint8_t *aTXData, uint32_t aTXLength, uint8_t *aRXData)
{
		volatile uint16_t d;
		
		G_SPI_SendingData = 1;
		G_SPI_ReceivingData = 1;
	
		SPI_CS_Start(aDevice);
	
		for (d=100; d>0; d--) // delay
			;
    
    CSI_SEND_RECEIVE(aTXData, aTXLength, aRXData);
    while(G_SPI_SendingData || G_SPI_ReceivingData);
    
		SPI_CS_End(aDevice);
}

