
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

#include "eeprom.h"
#include "uart.h"


#define FLASH_PAGE_SIZE                 0x400//1kb
#define FLASH_PAGE_COUNT                32//sayfa
#define FLASH_TO_RESERVE_FOR_CONFIG     0x400//2kb
#define CONFIG_START_FLASH_ADDRESS      (0x08000000 + (uint32_t)((FLASH_PAGE_SIZE * FLASH_PAGE_COUNT) - FLASH_TO_RESERVE_FOR_CONFIG))

#define EEPROM_START_ADD  CONFIG_START_FLASH_ADDRESS

// master config struct with data independent from profiles

uint32_t FLASH_FKEY1 =0x45670123;
uint32_t FLASH_FKEY2 =0xCDEF89AB;

extern pwm_config_t config;

static uint8_t calculateChecksum(const uint8_t *data, uint32_t length)
{
    uint8_t checksum = 0;
    const uint8_t *byteOffset;

    for (byteOffset = data; byteOffset < (data + length); byteOffset++)
        checksum ^= *byteOffset;

    //eeprom_test(data, length, checksum);
    return checksum;
}

uint8_t eeprom_read(){
    return read_flash_bin(&config,  EEPROM_START_ADD, sizeof(pwm_config_t));
}

void eeprom_save(){
   save_flash_nolib(&config, sizeof(pwm_config_t), EEPROM_START_ADD);
}


void save_flash_nolib(pwm_config_t *data, int length, uint32_t add){

    volatile uint32_t data_length = ceil(length / 2);
    uint16_t data_to_FLASH[data_length];

    memcpy(data_to_FLASH, data, length);

    config.chk = calculateChecksum((uint8_t *)data_to_FLASH, length-4);

    memcpy(data_to_FLASH, data, length);

    // unlock flash

    while ((FLASH->SR & FLASH_SR_BSY) != 0);
    if ((FLASH->CR & FLASH_CR_LOCK) != 0) {
        FLASH->KEYR = FLASH_FKEY1;
        FLASH->KEYR = FLASH_FKEY2;
    }

    // erase page if address even divisable by 1024

    if((add % 1024) == 0){
        FLASH->CR |= FLASH_CR_PER;
        FLASH->AR = add;
        FLASH->CR |= FLASH_CR_STRT;

        while ((FLASH->SR & FLASH_SR_BSY) != 0);

        if ((FLASH->SR & FLASH_SR_EOP) != 0){
            FLASH->SR = FLASH_SR_EOP;
        }
        FLASH->CR &= ~FLASH_CR_PER;
    }

     volatile uint32_t write_cnt=0, index=0;

     while(index < data_length){

        FLASH->CR |= FLASH_CR_PG; /* (1) */
        *(__IO uint16_t*)(add+write_cnt) = data_to_FLASH[index];
        while ((FLASH->SR & FLASH_SR_BSY) != 0);
        if ((FLASH->SR & FLASH_SR_EOP) != 0){
            FLASH->SR = FLASH_SR_EOP;
        }
        FLASH->CR &= ~FLASH_CR_PG;
        write_cnt += 2;
        index++;
    }

    SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

uint8_t read_flash_bin(pwm_config_t*  data , uint32_t add , int out_buff_len){
    uint8_t data_to_FLASH[out_buff_len];
    //volatile uint32_t read_data;
    for (int i = 0; i < out_buff_len ; i ++){
        data_to_FLASH[i] = *(uint8_t*)(add + i);
    }

    uint8_t chk = calculateChecksum(data_to_FLASH, out_buff_len - 4);

    if(chk != data_to_FLASH[out_buff_len - 4]){
        return ERROR;
    }

    memcpy(data, data_to_FLASH, out_buff_len);
    return SUCCESS;
}


void eeprom_test(uint8_t *data, int lenght, uint8_t chk){
    int i=0;
    uprintf("\n");
    while(i< lenght){
        uprintf("0x%X ", data[i]);
        i++;
    }
    uprintf("cal_chk: 0x%X, ckh:0x%X l: %d\n", chk, data[i-4], lenght);
}
