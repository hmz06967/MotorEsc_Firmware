/*
 * comutate.h
 *
 *  Created on: 2 Oca 2023
 *      Author: flyozkan
 */

#ifndef INC_COMUTATE_H_
#define INC_COMUTATE_H_

#include "include.h"
typedef enum {
    PHASE_COMPA = 1,
    PHASE_COMPB = 3,
    PHASE_COMPC = 5,
} motorComp_e;

uint16_t run_comutate(uint16_t duty);
uint8_t get_step(void);
void init_comutator(void);

#endif /* INC_COMUTATE_H_ */
