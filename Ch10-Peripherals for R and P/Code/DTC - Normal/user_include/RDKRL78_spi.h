#include "r_cg_userdefine.h"

// RDKRL78_spi.h
#ifndef _RDKRL78_SPI_H
#define _RDKRL78_SPI_H


#ifdef RDKRL78G13
#define SPI_LCD     0
#define SPI_SD      1
#define SPI_PMOD1   2
#define SPI_PMOD2   3

#define RESET_IO_PORT P13
#define RESET_IO_BIT_POS (0)

#define CSI_SEND_RECEIVE(a,b,c) R_CSI10_Send_Receive(a,b,c)
#define CSI_CREATE 							R_CSI10_Create
#define CSI_START 							R_CSI10_Start
#endif

#ifdef RDKRL78G14
#define SPI_LCD     0
#define SPI_SD      1
/*
#define SPI_PMOD1   2
#define SPI_PMOD2   3
*/

#define RESET_IO_PORT P13
#define RESET_IO_BIT_POS (0)

#define CSI_SEND_RECEIVE(a,b,c) R_CSI21_Send_Receive(a,b,c)
#define CSI_CREATE 							R_CSI21_Create
#define CSI_START 							R_CSI21_Start


#endif

void SPI_Init();
void SPI_Send(uint8_t aDevice, uint8_t *aData, uint32_t aLength);
void SPI_SendReceive(uint8_t aDevice, uint8_t *aTXData, uint32_t aTXLength, uint8_t *aRXData);

#endif // _RSPI_H