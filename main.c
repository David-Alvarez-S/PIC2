#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "Millis.h"
#include "I2C.h"
#include "OLED.h"
#include "Input.h"

// Variables globales
int Temp, State, Mode, TimeLeft, Nivel;
int Config_Option = 1;
int Screen_Num = 1;
uint32_t last_input_time = 0;

// Prototipos de funciones
void Display(int screen_num);
void Config_Options(void);
void Inputs(int Option);

int main(void) {
    Input_Init();
    I2C_Init();
    OLED_Init();
    millis_init();
    sei();
    
    OLED_Clear();
    Display(Screen_Num);
    
    while (1) {
        int button = Input_Button();
        if (button != 0) {
            Inputs(button);
        }
    }
    
    return 0;
}

void Display(int screen_num) {
    OLED_Clear();
    
    switch (screen_num) {
        case 1:
            OLED_Print(0, 45, "INICIO");
            OLED_Print(3, 0, "  Estado:");
            OLED_Print(4, 0, "  Modo:");
            OLED_Print(5, 0, "  Siguiente:");
            OLED_Print(6, 0, "  Nivel:");
            break;
            
        case 2:
            OLED_Print(0, 20, "INFO AMBIENTAL");
            OLED_Print(3, 0, "  Temperatura:");
            OLED_Print(4, 0, "  Humedad:");
            OLED_Print(5, 0, "  Movimiento:");
            break;
            
        case 3:
            Config_Options();
            break;
    }
}

void Config_Options(void) {
    OLED_Clear();
    OLED_Print(0, 20, "CONFIGURACION");
    
    switch (Config_Option) {
        case 1:
            OLED_Print(3, 0, "- Modo:");
            OLED_Print(4, 0, "  Intervalo:");
            OLED_Print(5, 0, "  Bluetooth:");
            break;
            
        case 2:
            OLED_Print(3, 0, "  Modo:");
            OLED_Print(4, 0, "- Intervalo:");
            OLED_Print(5, 0, "  Bluetooth:");
            break;
            
        case 3:
            OLED_Print(3, 0, "  Modo:");
            OLED_Print(4, 0, "  Intervalo:");
            OLED_Print(5, 0, "- Bluetooth:");
            break;
    }
}

void Inputs(int Option) {
    // Debouncing - prevenir múltiples pulsaciones rápidas
    if (millis() - last_input_time < 300) {
        return;
    }
    last_input_time = millis();
    
    switch(Option) {
        case 1: // Izquierda - Pantalla anterior
            Screen_Num--;
            if (Screen_Num < 1) Screen_Num = 3;
            Display(Screen_Num);
            break;
            
        case 2: // Derecha - Siguiente pantalla
            Screen_Num++;
            if (Screen_Num > 3) Screen_Num = 1;
            Display(Screen_Num);
            break;
            
        case 3: // Arriba - Opción anterior en configuración
            if (Screen_Num == 3) {
                Config_Option--;
                if (Config_Option < 1) Config_Option = 3;
                Config_Options();
            }
            break;
            
        case 4: // Abajo - Siguiente opción en configuración
            if (Screen_Num == 3) {
                Config_Option++;
                if (Config_Option > 3) Config_Option = 1;
                Config_Options();
            }
            break;
            
        case 5: // Enter
            // Acción de enter
            break;
    }
}