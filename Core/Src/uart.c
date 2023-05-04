/*
 * uart.c
 *
 *  Created on: Nov 29, 2022
 *      Author: flyozkan
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "uart.h"
#include "io.h"


uint8_t Timeout = 100;
uint8_t nbDataToTransmit = 64;
char msg[64] = {0};
uint8_t aTxBuffer[64];

uint8_t update_crc8(uint8_t crc, uint8_t crc_seed){
    uint8_t crc_u, i;
    crc_u = crc;
    crc_u ^= crc_seed;
    for ( i=0; i<8; i++)
        crc_u = ( crc_u & 0x80 ) ? 0x7 ^ ( crc_u << 1 ) : ( crc_u << 1 );
    return (crc_u);
}

uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen){
    uint8_t crc = 0, i;
    for( i=0; i<BufLen; i++) crc = update_crc8(Buf[i], crc);
    return (crc);
}

void makeTelemPackage(uint8_t temp, uint16_t voltage, uint16_t current, uint16_t consumption, uint16_t e_rpm){

  aTxBuffer[0] = temp; // temperature
  aTxBuffer[1] = (voltage >> 8) & 0xFF; // voltage hB
  aTxBuffer[2] = voltage & 0xFF; // voltage   lowB
  aTxBuffer[3] = (current >> 8) & 0xFF; // current
  aTxBuffer[4] = current & 0xFF; // divide by 10 for Amps
  aTxBuffer[5] = (consumption >> 8) & 0xFF; // consumption
  aTxBuffer[6] = consumption & 0xFF; //  in mah
  aTxBuffer[7] = (e_rpm >> 8) & 0xFF; //
  aTxBuffer[8] = e_rpm & 0xFF; // eRpM *100
  aTxBuffer[9] = get_crc8(aTxBuffer,9);
}

void uart_write(char * msg, uint8_t len){
    for(uint8_t i=0;i<len;i++){
        LL_USART_TransmitData8(USART1, msg[i]);
        while(!LL_USART_IsActiveFlag_TXE(USART1));
    }
    while(!LL_USART_IsActiveFlag_TC(USART1));
}

void soft_write_byte(uint8_t Data)
{
    UART_PORT->BRR = UART_TX_PIN;//reset
    delay_us(UART_BAUD);
    for(uint8_t i = 0; i < 8; i++)
    {
        if(Data & 0x01)
            UART_PORT->BSRR = UART_TX_PIN;//reset
        else
            UART_PORT->BRR = UART_TX_PIN;//reset
        delay_us(UART_BAUD);
        Data = Data>>1;
    }
    UART_PORT->BSRR = UART_TX_PIN;//set
    delay_us(UART_BAUD);
}

void soft_write(char * msg, uint8_t len){
    for(uint8_t i=0;i<len;i++){//String write
        soft_write_byte(msg[i]);
    }
}

void uprintf(char*format, ...){
#ifdef USE_DEBUG
    va_list arglist;
    va_start( arglist, format );
    nbDataToTransmit = vsprintf(msg, format, arglist);
    va_end( arglist );
    //nbDataToTransmit = strlen(msg);
    //memcpy(&aTxBuffer, &msg, nbDataToTransmit+1);
    uart_write(msg, nbDataToTransmit);

    //send_telem_DMA();
    //HAL_Delay(100);
    //while(!LL_DMA_IsActiveFlag_TC2(DMA1));
#endif
}

