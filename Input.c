#include "Input.h"
#include "Millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_LEFT    PD2
#define BUTTON_RIGHT   PD3
#define BUTTON_UP      PD4
#define BUTTON_DOWN    PD5
#define BUTTON_ENTER   PD6

#define DEBOUNCE_TIME 50

// Estados para cada botón
typedef enum {
	BTN_STATE_RELEASED,
	BTN_STATE_DEBOUNCING,
	BTN_STATE_PRESSED
} ButtonState_t;

typedef struct {
	uint8_t pin;
	volatile ButtonState_t state;
	volatile uint32_t last_change_time;
	volatile uint8_t new_press;
} Button_U;

volatile Button_U BUTTON[5];

void Input_Init(void) {
	DDRD  &= ~((1<<BUTTON_LEFT) | (1<<BUTTON_RIGHT) | (1<<BUTTON_UP) |
	(1<<BUTTON_DOWN) | (1<<BUTTON_ENTER));
	PORTD |=   (1<<BUTTON_LEFT) | (1<<BUTTON_RIGHT) | (1<<BUTTON_UP) |
	(1<<BUTTON_DOWN) | (1<<BUTTON_ENTER);
	
	for (uint8_t i = 0; i < 5; i++) {
		BUTTON[i].state = BTN_STATE_RELEASED;
		BUTTON[i].new_press = 0;
		BUTTON[i].last_change_time = 0;
	}
	
	BUTTON[0].pin = BUTTON_LEFT;
	BUTTON[1].pin = BUTTON_RIGHT;
	BUTTON[2].pin = BUTTON_UP;
	BUTTON[3].pin = BUTTON_DOWN;
	BUTTON[4].pin = BUTTON_ENTER;
}

void Update_Button_States(void) {
	for (uint8_t i = 0; i < 5; i++) {
		uint8_t current_state = (PIND & (1 << BUTTON[i].pin)) ? 1 : 0;
		
		switch (BUTTON[i].state) {
			case BTN_STATE_RELEASED:
			if (current_state == 0) { // Botón presionado
				BUTTON[i].state = BTN_STATE_DEBOUNCING;
				BUTTON[i].last_change_time = millis();
			}
			break;
			
			case BTN_STATE_DEBOUNCING:
			if (current_state == 1) { // Rebote, volver a released
				BUTTON[i].state = BTN_STATE_RELEASED;
			}
			else if (millis() - BUTTON[i].last_change_time > DEBOUNCE_TIME) {
				BUTTON[i].state = BTN_STATE_PRESSED;
				BUTTON[i].new_press = 1;
			}
			break;
			
			case BTN_STATE_PRESSED:
			if (current_state == 1) { // Botón liberado
				BUTTON[i].state = BTN_STATE_RELEASED;
			}
			break;
		}
	}
}

int Input_Button(void) {
	Update_Button_States();
	
	for (uint8_t i = 0; i < 5; i++) {
		if (BUTTON[i].new_press) {
			BUTTON[i].new_press = 0;
			return i + 1;
		}
	}
	
	return 0;
}