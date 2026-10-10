#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "stm32f407xx.h"

//SPI Configuration Structure
typedef struct
{
	uint8_t SPI_DeviceMode; //Master/Slave
	uint8_t SPI_CommMode;  //Full duplex/half Duplex/Simplex
	uint8_t SPI_SclkSpeed;  //Clock Speed
	uint8_t SPI_DFF;        //Data Frame Format - 8 bit / 16bit
	uint8_t SPI_CPOL;       //Clock Polarity - 0/1
	uint8_t SPI_CPHA;       //Clock Phase - 0/1
	uint8_t SPI_SSM;        //Software Slave management - 0/1
}SPI_Config_t;

//SPI handle Structure
typedef struct {
    SPI_Regdef_t *pSPIx;
    SPI_Config_t SPI_Config;
}SPI_Handle_t;

/* 
@SPI Device Mode 
*/
typedef enum {
    SPI_DEVMODE_SLAVE,
    SPI_DEVMODE_MASTER,
}SPI_DevMode_t;

/*
@SPI Bus Config
*/
typedef enum {
    SPI_COMMODE_FD_TX_RX = 1, //Full duplex Tx and Rx (Both MISO and MOSI line enabled)
    SPI_COMMODE_TX_ONLY,   //Simplex Tx only mode(Only MOSI(master) / MISO(slave) enabled)
    SPI_COMMODE_RX_ONLY,   //Simple Rx only mode(Only MISO(master) / MOSI(slave) enabled)
    SPI_COMMODE_HD_TX_ONLY, //Half duplex with Tx only mode
    SPI_COMMODE_HD_RX_ONLY, //Half duplex with Rx only mode
}SPI_BusConfig_t;

/*
@SPI SCLK Speed
*/
typedef enum {
    SPI_SCLK_SPEED_DIV2 = 0,
    SPI_SCLK_SPEED_DIV4,
    SPI_SCLK_SPEED_DIV8,
    SPI_SCLK_SPEED_DIV16,
    SPI_SCLK_SPEED_DIV32,
    SPI_SCLK_SPEED_DIV64,
    SPI_SCLK_SPEED_DIV128,
    SPI_SCLK_SPEED_DIV256,
}SPI_SCLKSpeed_t;

/*
@SPI DFF
*/
typedef enum {
    SPI_DFF_8BIT = 0,
    SPI_DFF_16BIT,
}SPI_DFF_t;

/*
@SPI CPOL
*/
typedef enum {
    SPI_CPOL_LOW = 0,
    SPI_CPOL_HIGH,
}SPI_CPOL_t;

/*
@SPI CPHA
*/
typedef enum {
    SPI_CPHA_LOW = 0,
    SPI_CPHA_HIGH,
}SPI_CPHA_t;

/*
@SPI SSM
*/
typedef enum {
    SPI_SSM_DI = 0,
    SPI_SSM_EN,
}SPI_SSM_t;


/******************************** SPI Register Fields Def ********************************/
/* SPI_CR1 - 0x00 */
typedef union {
    uint32_t val;
    struct {
        uint32_t CPHA      : 1;   /* bit 0 */
        uint32_t CPOL      : 1;   /* bit 1 */
        uint32_t MSTR      : 1;   /* bit 2 */
        uint32_t BR        : 3;   /* bits 5:3, BR[2:0] */
        uint32_t SPE       : 1;   /* bit 6 */
        uint32_t LSBFIRST  : 1;   /* bit 7 */
        uint32_t SSI       : 1;   /* bit 8 */
        uint32_t SSM       : 1;   /* bit 9 */
        uint32_t RXONLY    : 1;   /* bit 10 */
        uint32_t DFF       : 1;   /* bit 11 */
        uint32_t CRCNEXT   : 1;   /* bit 12 */
        uint32_t CRCEN     : 1;   /* bit 13 */
        uint32_t BIDIOE    : 1;   /* bit 14 */
        uint32_t BIDIMODE  : 1;   /* bit 15 */
        uint32_t RESERVED0 : 16;  /* bits 31:16 */
    }CR1_Bits;
}SPI_CR1;

/* SPI_CR2 - 0x04 */
typedef union {
    uint32_t val;
    struct {
        uint32_t RXDMAEN   : 1;   /* bit 0 */
        uint32_t TXDMAEN   : 1;   /* bit 1 */
        uint32_t SSOE      : 1;   /* bit 2 */
        uint32_t RESERVED0 : 1;   /* bit 3 */
        uint32_t FRF       : 1;   /* bit 4 */
        uint32_t ERRIE     : 1;   /* bit 5 */
        uint32_t RXNEIE    : 1;   /* bit 6 */
        uint32_t TXEIE     : 1;   /* bit 7 */
        uint32_t RESERVED1 : 24;  /* bits 31:8 */
    }CR2_Bits;
}SPI_CR2;

/* SPI_SR - 0x08 */
typedef union {
    uint32_t val;
    struct {
        uint32_t RXNE      : 1;   /* bit 0 */
        uint32_t TXE       : 1;   /* bit 1 */
        uint32_t CHSIDE    : 1;   /* bit 2 */
        uint32_t UDR       : 1;   /* bit 3 */
        uint32_t CRCERR    : 1;   /* bit 4 */
        uint32_t MODF      : 1;   /* bit 5 */
        uint32_t OVR       : 1;   /* bit 6 */
        uint32_t BSY       : 1;   /* bit 7 */
        uint32_t FRE       : 1;   /* bit 8 */
        uint32_t RESERVED0 : 23;  /* bits 31:9 */
    }SR_Bits;
}SPI_SR;

/* SPI_DR - 0x0C */
typedef union {
    uint32_t val;
    struct {
        uint32_t DR        : 16;  /* bits 15:0, DR[15:0] */
        uint32_t RESERVED0 : 16;  /* bits 31:16 */
    }DR_Bits;
}SPI_DR;

/* SPI_CRCPR - 0x10 */
typedef union {
    uint32_t val;
    struct {
        uint32_t CRCPOLY   : 16;  /* bits 15:0, CRCPOLY[15:0] */
        uint32_t RESERVED0 : 16;  /* bits 31:16 */
    }CRCPR_Bits;
}SPI_CRCPR;

/* SPI_RXCRCR - 0x14 */
typedef union {
    uint32_t val;
    struct {
        uint32_t RXCRC     : 16;  /* bits 15:0, RXCRC[15:0] */
        uint32_t RESERVED0 : 16;  /* bits 31:16 */
    }RXCRCR_Bits;
}SPI_RXCRCR;

/* SPI_TXCRCR - 0x18 */
typedef union {
    uint32_t val;
    struct {
        uint32_t TXCRC     : 16;  /* bits 15:0, TXCRC[15:0] */
        uint32_t RESERVED0 : 16;  /* bits 31:16 */
    }TXCRCR_Bits;
}SPI_TXCRCR;

/* SPI_I2SCFGR - 0x1C */
typedef union {
    uint32_t val;
    struct {
        uint32_t CHLEN     : 1;   /* bit 0 */
        uint32_t DATLEN    : 2;   /* bits 2:1, DATLEN[1:0] */
        uint32_t CKPOL     : 1;   /* bit 3 */
        uint32_t I2SSTD    : 2;   /* bits 5:4, I2SSTD[1:0] */
        uint32_t RESERVED0 : 1;   /* bit 6 */
        uint32_t PCMSYNC   : 1;   /* bit 7 */
        uint32_t I2SCFG    : 2;   /* bits 9:8, I2SCFG[1:0] */
        uint32_t I2SE      : 1;   /* bit 10 */
        uint32_t I2SMOD    : 1;   /* bit 11 */
        uint32_t RESERVED1 : 20;  /* bits 31:12 */
    }I2SCFGR_Bits;
}SPI_I2SCFGR;

/* SPI_I2SPR - 0x20 */
typedef union {
    uint32_t val;
    struct {
        uint32_t I2SDIV    : 8;   /* bits 7:0, I2SDIV[7:0] */
        uint32_t ODD       : 1;   /* bit 8 */
        uint32_t MCKOE     : 1;   /* bit 9 */
        uint32_t RESERVED0 : 22;  /* bits 31:10 */
    }I2SPR_Bits;
}SPI_I2SPR;

/*********************************APIs Supported by Driver*********************************/

/*
    SPI Init and De-init APIs
*/
void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_DeInit(SPI_Handle_t *pSPI_Handle);

/*
    SPI Send and receive APIs
*/
void SPI_SendData(SPI_Regdef_t *pSPIx, uint8_t *pTxBuff, size_t len);
void SPI_RecvData(SPI_Regdef_t *pSPIx, uint8_t *pRxBuff, size_t len);

/*
    SPI IRQ Handling APIs
*/
void SPI_IRQConfig(SPI_Handle_t *pSPI_Handle, uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pSPI_Handle);

#endif //_SPI_DRIVER_H_