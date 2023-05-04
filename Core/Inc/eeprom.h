/*
 * eeprom.h
 *
 *  Created on: Dec 5, 2022
 *      Author: flyozkan
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "main.h"
#include "input.h"

#define EEPROM_CONF_VERSION     1

void eeprom_test(uint8_t *data, int lenght, uint8_t chk);

void eeprom_save(void);
uint8_t eeprom_read(void);
void save_flash_nolib(pwm_config_t *data, int length, uint32_t add);
uint8_t read_flash_bin(pwm_config_t*  data , uint32_t add , int out_buff_len);

#endif /* INC_EEPROM_H_ */
