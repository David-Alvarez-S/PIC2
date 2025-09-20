#include "Millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t timer_millis = 0;

void millis_init(void) {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	OCR1A = 250 - 1;
	TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
	timer_millis++;
}

// Función millis() normal
uint32_t millis(void) {
	uint32_t m;
	uint8_t oldSREG = SREG;
	cli();
	m = timer_millis;
	SREG = oldSREG;
	return m;
}

// Resetear millis() a cero - MÉTODO SEGURO
void reset_millis(void) {
	uint8_t oldSREG = SREG;
	cli();
	timer_millis = 0;
	SREG = oldSREG;
}
