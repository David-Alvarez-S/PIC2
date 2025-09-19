#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "I2C.h" 
#include "OLED.h"

#define F_CPU 16000000UL // Frecuencia del Atmega328p (16MHz)

int Temp, State, Mode, TimeLeft, Nivel, Screen_Num;
int Intervalo = 600; //Medido en minutos

int main(void) {
	
	
	State = 1;
	Mode = 1;
	TimeLeft = Intervalo;
	Screen_Num = 1;
	
	I2C_Init();
	OLED_Init();
	OLED_Clear();
	
	Display(Screen_Num);
	
	while (1) {
		// Tu código principal aquí
		_delay_ms(1000);
	}
	
	return 0;
}


void Display(int Screen){
	switch (Screen){
		case 1:
			OLED_Print(0, 45, "INICIO");
			OLED_Print(3, 0, "Estado:");
			OLED_Print(4, 0, "Modo:");
			OLED_Print(5, 0, "Proximo spray:");
			OLED_Print(6, 0, "Nivel:");
		break;
		case 2:
			OLED_Print(0, 20, "INFO AMBIENTAL");
			OLED_Print(3, 0, "Temperatura:");
			OLED_Print(4, 0, "Humedad:");
			OLED_Print(5, 0, "Movimiento:");
		break;
		case 3:
			OLED_Print(0, 20, "CONFIGURACION");
			OLED_Print(3, 0, "Modo:");
			OLED_Print(4, 0, "Intervalo:");
			OLED_Print(5, 0, "Bluetooth:");
		break;
	}
	
}
