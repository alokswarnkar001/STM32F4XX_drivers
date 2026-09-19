#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t SPI_DeviceMode; //Master/Slave
	uint8_t SPI_BusConfig;  //Full duplex/half Duplex/Simplex
	uint8_t SPI_SclkSpeed;  //Clock Speed
	uint8_t SPI_DFF;        //Data Frame Format - 8 bit / 16bit
	uint8_t SPI_CPOL;       //Clock Polarity - 0/1
	uint8_t SPI_CPHA;       //Clock Phase - 0/1
	uint8_t SPI_SSM;        //Software Slave management - 0/1
}SPI_Config_t;

typedef struct {
    SPI_Regdef_t *pSPIx;
    SPI_Config_t SPI_Config;
}SPI_Handle_t;

#endif //_SPI_DRIVER_H_