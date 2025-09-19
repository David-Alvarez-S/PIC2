/*
 * OLED.h
 *
 * Created: 19/9/2025 0:54:14
 *  Author: David
 */ 


#ifndef OLED_H_
#define OLED_H_

void OLED_Command(uint8_t cmd);
void OLED_Data(uint8_t data);
void OLED_Init(void);
void OLED_SetPosition(uint8_t page, uint8_t column);
void OLED_Clear(void);
void OLED_DrawChar(uint8_t page, uint8_t col, char c);
void OLED_Print(uint8_t page, uint8_t col, const char *str);





#endif /* OLED_H_ */