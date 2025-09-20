/*
 * millis.h
 *
 * Created: 19/9/2025 23:02:56
 *  Author: David
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>


#ifndef MILLIS_H_
#define MILLIS_H_

void reset_millis(void);
uint32_t millis(void);
void millis_init(void);


#endif /* MILLIS_H_ */