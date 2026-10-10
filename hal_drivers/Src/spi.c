#include "spi.h"
#include "rcc.h"
#include "nvic.h"
#include "stm32f407xx.h"

/*
    SPI Init and De-init APIs
*/
void SPI_Init(SPI_Handle_t *pSPI_Handle) {
    //Enable the Peripheral Clock
    SPI_Regdef_t *pSPIx = pSPI_Handle->pSPIx;
    SPI_Config_t SPI_cfg = pSPI_Handle->SPI_Config;
    RCC_PeriClockEnable((uint32_t)pSPIx);

    //Configure SPI as master/slave
    SPI_CR1 cr1 = {0x00};
    cr1.CR1_Bits.MSTR = SPI_cfg.SPI_DeviceMode;

    //Configure SPI in FD/HD/SIMPLEX mode of communication
    switch(SPI_cfg.SPI_CommMode) {
        case SPI_COMMODE_FD_TX_RX:
        case SPI_COMMODE_TX_ONLY:
            cr1.CR1_Bits.BIDIMODE = 0;
            cr1.CR1_Bits.RXONLY = 0;
            break;
        case SPI_COMMODE_RX_ONLY:
            cr1.CR1_Bits.BIDIMODE = 0;
            cr1.CR1_Bits.RXONLY = 1;
            break;
        case SPI_COMMODE_HD_TX_ONLY:
            cr1.CR1_Bits.BIDIMODE = 1;
            cr1.CR1_Bits.BIDIOE = 1;
            break;
        case SPI_COMMODE_HD_RX_ONLY:
            cr1.CR1_Bits.BIDIMODE = 1;
            cr1.CR1_Bits.BIDIOE = 0;
            break;
        default:
            break;
    }

    //Configure SPI Data Frame Format
    cr1.CR1_Bits.DFF = SPI_cfg.SPI_DFF;

    //Configure SPI Clock Polarity and Clock Phase
    cr1.CR1_Bits.CPOL = SPI_cfg.SPI_CPOL;
    cr1.CR1_Bits.CPHA = SPI_cfg.SPI_CPHA;

    //Configure SPI Slave management
    cr1.CR1_Bits.SSM = SPI_cfg.SPI_SSM;
    if(cr1.CR1_Bits.SSM) {
        cr1.CR1_Bits.SSI = cr1.CR1_Bits.MSTR;
    }

    //Configure SCLK Speed
    cr1.CR1_Bits.BR = SPI_cfg.SPI_SclkSpeed;
    pSPIx->CR1 = cr1.val;
    
    //Enable SPI
    cr1.CR1_Bits.SPE = 1;
    pSPIx->CR1 |= cr1.val;
}

void SPI_DeInit(SPI_Handle_t *pSPI_Handle) {
    //Reset all Registers of SPI 
    RCC_PeriRst((uint32_t)pSPI_Handle->pSPIx);
    //Disable the SPI Peri clock
    RCC_PeriClockDisable((uint32_t)pSPI_Handle->pSPIx);
}

/*
    SPI Send and receive APIs
*/
void SPI_SendData(SPI_Regdef_t *pSPIx, uint8_t *pTxBuff, size_t len) {
    SPI_CR1 cr;
    SPI_DR dr;
    SPI_SR sr;

    if(!pTxBuff || !pSPIx ) {
        return;
    }

    uint8_t *buff = pTxBuff;

    while(len) {
        sr.val = pSPIx->SR;
        while(!sr.SR_Bits.TXE) {
            sr.val = pSPIx->SR;
        }
        cr.val = pSPIx->CR1;
        if(cr.CR1_Bits.DFF == SPI_DFF_8BIT) {
            dr.val = *buff;
            pSPIx->DR = dr.val & 0xFF;
            buff++;
        }
        else {
            dr.val = *buff;
            buff++;
            len--;
            if(len != 0) {
                dr.val = (dr.val & 0x00FF) | ((*buff << 8) & 0xFF00);
                pSPIx->DR = dr.val & 0xFFFF;
                buff++;
            }
            else {
                pSPIx->DR = dr.val & 0xFF;
                break;
            } 
        }
        len--;
    }

    sr.val = pSPIx->SR;
    while(!sr.SR_Bits.TXE) {
        sr.val = pSPIx->SR;
    }
    sr.val = pSPIx->SR;
    while(sr.SR_Bits.BSY) {
        sr.val = pSPIx->SR;
    }
    return;
}

void SPI_RecvData(SPI_Regdef_t *pSPIx, uint8_t *pRxBuff, size_t len) {

}

/*
    SPI IRQ Handling APIs
*/
void SPI_IRQConfig(SPI_Handle_t *pSPI_Handle, uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi) {

}

void SPI_IRQHandling(SPI_Handle_t *pSPI_Handle) {

}