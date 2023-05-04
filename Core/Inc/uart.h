/*
 * uart.h
 *
 *  Created on: Nov 29, 2022
 *      Author: flyozkan
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

//for software uart
#define UART_BAUD 100
#define UART_PORT GPIOB
#define UART_TX_PIN LL_GPIO_PIN_7

void soft_write_byte(uint8_t Data);
void uart_write(char * msg, uint8_t len);

uint8_t update_crc8(uint8_t crc, uint8_t crc_seed);
uint8_t get_crc8(uint8_t *Buf, uint8_t BufLen);
void makeTelemPackage(uint8_t temp, uint16_t voltage, uint16_t current, uint16_t consumption, uint16_t e_rpm);
void uprintf(char*format, ...);

#endif /* INC_UART_H_ */
