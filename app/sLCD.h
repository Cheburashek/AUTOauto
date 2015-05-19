//Program sterujacy wyswietlaczem LCD w KL46Z, gaszenie zer nieznaczacych (sLCD_dec(value))

//sLCD_init() - inicjalizuje LCD
//sLCD_set(value,digit) - wyswietla znak od 0 do 'F' na pozycji 1:4
		//0xFF - pusty znak
	
//value = 0xFF - wygaszenie pozycji
//sLCD_dot(dot) - DODAJE kropke dziesietna do znaku dla wartosci 1-3 i dwukropek dla 4 
//(kasowanie kropki to wywolanie funkcji z 4x wieksza wartoscia)
//Pojawienie sie blednej wartosci zatrzymuje program wyswietlajac jeden z komunikatow:
	
		//err1 - za duza wartosc "value"
		//err2 - za duza pozycja lub = 0
		//err3 - za duza pozycja dot lub = 0
		//err4 - za duza liczba do wyswietlenia (sLCD_disp) > 9999
		
		//err - wywolany z 5, dowolny blad zewnetrznego programu


#ifndef sLCD_H
#define sLCD_H

#include "MKL46Z4.h"
#define LCD_N_FRONT 8
#define LCD_N_BACK 4

#define LCD_S_D 0x11 // segment D
#define LCD_S_E 0x22 // segment E
#define LCD_S_G 0x44 // segment G
#define LCD_S_F 0x88 // segment F
#define LCD_S_DEC 0x11
#define LCD_S_C 0x22
#define LCD_S_B 0x44
#define LCD_S_A 0x88
#define LCD_C 0x00 // clear

// Makra dla kazdego pinu
#define LCD_FRONT0 37u
#define LCD_FRONT1 17u
#define LCD_FRONT2 7u
#define LCD_FRONT3 8u
#define LCD_FRONT4 53u
#define LCD_FRONT5 38u
#define LCD_FRONT6 10u
#define LCD_FRONT7 11u
#define LCD_BACK0 40u
#define LCD_BACK1 52u
#define LCD_BACK2 19u
#define LCD_BACK3 18u



//Deklaracje funckji (potrzebne, aby uzyskac dostep do funckji z innej funkcji przed jej definicja)
void sLCD_err(uint8_t err_num);
void sLCD_init(void);
void sLCD_set(uint8_t value, uint8_t digit);
void sLCD_dot(uint8_t dot);
void sLCD_dec(uint16_t disp_value);
void sLCD_hex(uint32_t disp_value);
void sLCD_oct(uint16_t disp_value);
void sLCD_bin(uint8_t disp_value);

	


#endif
