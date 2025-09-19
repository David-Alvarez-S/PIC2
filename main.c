#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "I2C.h" 
#include "OLED.h"

#define DEBOUNCE_DELAY 500
#define F_CPU 16000000UL // Frecuencia del Atmega328p (16MHz)

int Temp, State, Mode, TimeLeft, Nivel, Screen_Num;
int Intervalo = 600; //Medido en minutos
int Config_Option = 1;
Screen_Num = 1;

void Press_Button();
void Display();
void Config_Options();

int main(void) {
	
	DDRD = 0x00;
	PORTD |= 0b00111110;
	
	State = 1;
	Mode = 1;
	TimeLeft = Intervalo;
	
	
	I2C_Init();
	OLED_Init();
	OLED_Clear();
	
	Display(Screen_Num);
	
	while (1) {
		Press_Button();
	}
	
	return 0;
}


void Display(){
	OLED_Clear();
	switch (Screen_Num){
		case 1:
			OLED_Print(0, 45, "INICIO");
			OLED_Print(3, 0, " Estado:");
			OLED_Print(4, 0, " Modo:");
			OLED_Print(5, 0, " Proximo spray:");
			OLED_Print(6, 0, " Nivel:");
		break;
		case 2:
			OLED_Print(0, 20, "INFO AMBIENTAL");
			OLED_Print(3, 0, " Temperatura:");
			OLED_Print(4, 0, " Humedad:");
			OLED_Print(5, 0, " Movimiento:");
		break;
		case 3:
			OLED_Print(0, 20, "CONFIGURACION");
			OLED_Print(3, 0, " Modo:");
			OLED_Print(4, 0, " Intervalo:");
			OLED_Print(5, 0, " Bluetooth:");
		break;
	}
	
}

void Press_Button(){
	bool PresionadoI = (PIND & (1 << PD2));
	bool PresionadoD = (PIND & (1 << PD3));
	
	bool PresionadoA = (PIND & (1 << PD4));
	bool PresionadoAb = (PIND & (1 << PD5));
	
	bool PresionadoE = (PIND & (1 << PD6));
	
	if (!PresionadoD){
		Screen_Num++;
		_delay_ms(DEBOUNCE_DELAY);
		if(Screen_Num <= 0){
			Screen_Num = 3;
		}else if (Screen_Num >= 4){
			Screen_Num = 1;
		}
		Display(Screen_Num);
	}
	if (!PresionadoI){
		Screen_Num--;
		_delay_ms(DEBOUNCE_DELAY);
		if(Screen_Num <= 0){
			Screen_Num = 3;
			}else if (Screen_Num >= 4){
			Screen_Num = 1;
			}
		Display(Screen_Num);
	}
	
	if (!PresionadoA){
		_delay_ms(DEBOUNCE_DELAY);
		if (Screen_Num == 3){
			Config_Option ++;
			if (Config_Option >= 4){
				Config_Option = 1;
			}
		}
		Config_Options();

	}
	
	if (!PresionadoAb){
		_delay_ms(DEBOUNCE_DELAY);
		Screen_Num--;
		_delay_ms(DEBOUNCE_DELAY);
		if(Screen_Num <= 0){
			Screen_Num = 3;
			}else if (Screen_Num >= 4){
			Screen_Num = 1;
		}
		Config_Options();
	
	}
}

void Config_Options(){
	OLED_Print(0, 20, "CONFIGURACION");
	if (Config_Option == 1){
		OLED_Print(3, 0, "{Modo:");
		OLED_Print(4, 0, " Intervalo:");
		OLED_Print(5, 0, " Bluetooth:");
	}else if (
		Config_Option == 2){
		OLED_Print(3, 0, " Modo:");
		OLED_Print(4, 0, "{Intervalo:");
		OLED_Print(5, 0, " Bluetooth:");
	}else if (
		Config_Option == 3){
		OLED_Print(3, 0, " Modo:");
		OLED_Print(4, 0, " Intervalo:");
		OLED_Print(5, 0, "{Bluetooth:");
	}
}