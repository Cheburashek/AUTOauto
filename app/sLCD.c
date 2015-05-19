// sLCD.c

#include "sLCD.h"

const static uint8_t LCD_Front_Pin[LCD_N_FRONT] = {37u, 17u, 7u, 8u, 53u, 38u, 10u, 11u};

uint8_t disp_digit = 0;




//*************************************************************************************************************************
void sLCD_err(uint8_t err_num){
//*************************************************************************************************************************
	
	sLCD_set(0x0E, 1);
	sLCD_set(0x10, 2);
	sLCD_set(0x10, 3);
	
	switch(err_num){
		case 1:			
			sLCD_set(0x01, 4);
			break;
		case 2:
   		sLCD_set(0x02, 4);
			break;
		case 3:
			sLCD_set(0x03, 4);
			break;
		case 4:
			sLCD_set(0x04, 4);
			break;
		case 5:
			sLCD_set(0x00, 4);
			break;
	}
	
}
	
	
void sLCD_init(void){
//*************************************************************************************************************************
	
	
	

SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK
					 | SIM_SCGC5_PORTC_MASK
				   | SIM_SCGC5_PORTD_MASK
				   | SIM_SCGC5_PORTE_MASK
					 | SIM_SCGC5_SLCD_MASK;


// wstepne wylaczenie i reset kontrolera
LCD->GCR |= LCD_GCR_PADSAFE_MASK; // safe state on output control pins  ????
LCD->GCR &= ~LCD_GCR_LCDEN_MASK; // Clear LCDEN w trakcie konfiguracji

// konfiguracja multiplekserów do operacji portów jako kontroler LCD
PORTB->PCR[7] = PORT_PCR_MUX(0u);
PORTB->PCR[8] = PORT_PCR_MUX(0u);
PORTB->PCR[10] = PORT_PCR_MUX(0u);
PORTB->PCR[11] = PORT_PCR_MUX(0u);
PORTB->PCR[21] = PORT_PCR_MUX(0u);
PORTB->PCR[22] = PORT_PCR_MUX(0u);
PORTB->PCR[23] = PORT_PCR_MUX(0u);
PORTC->PCR[17] = PORT_PCR_MUX(0u);
PORTC->PCR[18] = PORT_PCR_MUX(0u);
PORTD->PCR[0] = PORT_PCR_MUX(0u);
PORTE->PCR[4] = PORT_PCR_MUX(0u);
PORTE->PCR[5] = PORT_PCR_MUX(0u);

// konfiguracja rejestrów LCD
LCD->GCR = 
LCD_GCR_RVTRIM(0x00) | LCD_GCR_CPSEL_MASK | LCD_GCR_LADJ(0x03) | LCD_GCR_VSUPPLY_MASK | // !!!!!! LCD_GCR_PADSAFE_MASK | LCD_GCR_ALTDIV(0x03) | LCD_GCR_SOURCE_MASK | // !!
LCD_GCR_SOURCE_MASK | LCD_GCR_LCLK(0x01) | LCD_GCR_ALTDIV(0x00) | // !!!!!!
LCD_GCR_DUTY(0x03); // !!!!!!

// konfiguracja migania wyswietlacza
LCD->AR = LCD_AR_BRATE(0x03); // 3 bit blink mode ????

// konfiguracja rejestru FDCR
LCD->FDCR = 0x00000000; // wszystkie piny od 0 do 63 ????

// aktywowanie 12 pinów do kontroli wyswietlaczem (dwa rejestry po 32 bity)
LCD->PEN[0] =
LCD_PEN_PEN(1u<<7) | // LCD_P7
LCD_PEN_PEN(1u<<8) |
LCD_PEN_PEN(1u<<10) |
LCD_PEN_PEN(1u<<11) |
LCD_PEN_PEN(1u<<18) |
LCD_PEN_PEN(1u<<19) |
LCD_PEN_PEN(1u<<17);
LCD->PEN[1] =
LCD_PEN_PEN(1u<<8) |
LCD_PEN_PEN(1u<<20) |
LCD_PEN_PEN(1u<<5) |
LCD_PEN_PEN(1u<<21) |
LCD_PEN_PEN(1u<<6);

// skonfigurowanie 4 pinów plaszczyzny tylnej (dwa rejestry po 32 bity)
LCD->BPEN[0] =
LCD_BPEN_BPEN(1u<<18) |
LCD_BPEN_BPEN(1u<<19);
LCD->BPEN[1] =
LCD_BPEN_BPEN(1u<<8) |
LCD_BPEN_BPEN(1u<<20);

// konfiguracja rejestrów przebiegów (Waveform register) – 4 aktywne, reszta nie
// konfiguracja polega na równomiernym rozlozeniu faz, w tym przypadku 4, na 8 bitach
// (44.3.7 w KL46 Reference Manual)
LCD->WF[0] =
LCD_WF_WF0(0x00) |
LCD_WF_WF1(0x00) |
LCD_WF_WF2(0x00) |
LCD_WF_WF3(0x00);
LCD->WF[1] =
LCD_WF_WF4(0x00) |
LCD_WF_WF5(0x00) |
LCD_WF_WF6(0x00) |
LCD_WF_WF7(0x00);
LCD->WF[2] =
LCD_WF_WF8(0x00) |

LCD_WF_WF9(0x00) |
LCD_WF_WF10(0x00) |
LCD_WF_WF11(0x00);
LCD->WF[3] =
LCD_WF_WF12(0x00) |
LCD_WF_WF13(0x00) |
LCD_WF_WF14(0x00) |
LCD_WF_WF15(0x00);
LCD->WF[4] =
LCD_WF_WF16(0x00) |
LCD_WF_WF17(0x00) |
LCD_WF_WF18(0x88) | // COM3 (10001000)
LCD_WF_WF19(0x44); // COM2 (01000100)
LCD->WF[5] =
LCD_WF_WF20(0x00) |
LCD_WF_WF21(0x00) |
LCD_WF_WF22(0x00) |
LCD_WF_WF23(0x00);
LCD->WF[6] =
LCD_WF_WF24(0x00) |
LCD_WF_WF25(0x00) |
LCD_WF_WF26(0x00) |
LCD_WF_WF27(0x00);
LCD->WF[7] =
LCD_WF_WF28(0x00) |
LCD_WF_WF29(0x00) |
LCD_WF_WF30(0x00) |
LCD_WF_WF31(0x00);
LCD->WF[8] =
LCD_WF_WF32(0x00) |
LCD_WF_WF33(0x00) |
LCD_WF_WF34(0x00) |
LCD_WF_WF35(0x00);
LCD->WF[9] =
LCD_WF_WF36(0x00) |
LCD_WF_WF37(0x00) |
LCD_WF_WF38(0x00) |
LCD_WF_WF39(0x00);
LCD->WF[10] =
LCD_WF_WF40(0x11) | // COM0 (00010001)
LCD_WF_WF41(0x00) |
LCD_WF_WF42(0x00) |
LCD_WF_WF43(0x00);
LCD->WF[11] =
LCD_WF_WF44(0x00) |
LCD_WF_WF45(0x00) |
LCD_WF_WF46(0x00) |
LCD_WF_WF47(0x00);
LCD->WF[12] =
LCD_WF_WF48(0x00) |
LCD_WF_WF49(0x00) |
LCD_WF_WF50(0x00) |

LCD_WF_WF51(0x00);
LCD->WF[13] =
LCD_WF_WF52(0x22) | // COM1 (00100010)
LCD_WF_WF53(0x00) |
LCD_WF_WF54(0x00) |
LCD_WF_WF55(0x00);
LCD->WF[14] =
LCD_WF_WF56(0x00) |
LCD_WF_WF57(0x00) |
LCD_WF_WF58(0x00) |
LCD_WF_WF59(0x00);
LCD->WF[15] =
LCD_WF_WF60(0x00) |
LCD_WF_WF61(0x00) |
LCD_WF_WF62(0x00) |
LCD_WF_WF63(0x00);

// koniec konfiguracji, wiec clear PADSAFE i wlaczenie wyswietlacza
LCD->GCR &= ~LCD_GCR_PADSAFE_MASK; // disable save state ????
LCD->GCR |= LCD_GCR_LCDEN_MASK; // wlaczenie wyswietlacza


}


	
	
void sLCD_set(uint8_t value,uint8_t digit){
//*************************************************************************************************************************	
	
	
//dodatkowa pozycja zgaszona					
// value – wyswietlana wartosc,
// digit – pozycja na której ma byc wyswietlona wartosc
		
		if(digit == 0 || digit > 4){sLCD_err(2);}
	
		if(value==0x00){ 
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E |LCD_S_F); 
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] =	(LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x01){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] =	(LCD_C);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] =	(LCD_S_B | LCD_S_C);
		}

		else if(value==0x02){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B);
		}

		else if(value==0x03){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x04){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_C);
		}

		else if(value==0x05){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G | LCD_S_D);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_C);
		}

		else if(value==0x06){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_E | LCD_S_D | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_C);
		}

		else if(value==0x07){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_C);

		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x08){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_E | LCD_S_F | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x09){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_G | LCD_S_D);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x0A){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_E | LCD_S_F | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A | LCD_S_B | LCD_S_C);
		}

		else if(value==0x0B){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_E | LCD_S_G | LCD_S_D);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_C);
		}

		else if(value==0x0C){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_G | LCD_S_E | LCD_S_D);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_C);
		}

		else if(value==0x0D){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_D | LCD_S_G | LCD_S_E);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_B | LCD_S_C);
		}

		else if(value==0x0E){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_E | LCD_S_G | LCD_S_D);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A);
		}

		else if(value==0x0F){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_F | LCD_S_E | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_S_A);
		}
				
		//r		
		else if(value==0x10){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_S_E | LCD_S_G);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_C);
		}
		
		//gaszenie
		else if(value==0xff){
		LCD->WF8B[LCD_Front_Pin[((2*digit)-2)]] = (LCD_C);
		LCD->WF8B[LCD_Front_Pin[((2*digit)-1)]] = (LCD_C);
		}
		
		else{sLCD_err(1);}
		
	}

	
	
void sLCD_dot(uint8_t dot){	
		
		switch(dot){			
			case 1:
				LCD->WF8B[LCD_Front_Pin[1]] |= (LCD_S_DEC);
				break;
			case 2:
				LCD->WF8B[LCD_Front_Pin[3]] |= (LCD_S_DEC);
				break;
			case 3:
				LCD->WF8B[LCD_Front_Pin[5]] |= (LCD_S_DEC);
				break;
			case 4:
				LCD->WF8B[LCD_Front_Pin[7]] |= (LCD_S_DEC);
				break;
			case 5:
				LCD->WF8B[LCD_Front_Pin[1]] -= (LCD_S_DEC);
				break;
			case 6:
				LCD->WF8B[LCD_Front_Pin[3]] -= (LCD_S_DEC);
				break;
			case 7:
				LCD->WF8B[LCD_Front_Pin[5]] -= (LCD_S_DEC);
				break;
			case 8:
				LCD->WF8B[LCD_Front_Pin[7]] -= (LCD_S_DEC);
				break;
			
			default:
				sLCD_err(3);
				break;		
	}	
}
	

//*************************************************************************************************************************
void sLCD_dec(uint16_t disp_value){
	
	uint16_t temp_value;
	
	if(disp_value > 9999){sLCD_err(4);}
	
	disp_digit = disp_value % 10;		
	sLCD_set(disp_digit, 4);
	
	temp_value = disp_value / 10;
	disp_digit = temp_value % 10;
	//if(disp_value < 10){disp_digit=0xFF;}
	sLCD_set(disp_digit, 3);
	
	temp_value = temp_value / 10;
	disp_digit = temp_value % 10;
	//if(disp_value < 100){disp_digit=0xFF;}
	sLCD_set(disp_digit, 2);
	
	disp_digit = temp_value / 10;
	//if(disp_value < 1000){disp_digit=0xFF;}
	sLCD_set(disp_digit, 1);
	

	
}

//*************************************************************************************************************************
void sLCD_hex(uint32_t disp_value){
//*************************************************************************************************************************

	uint32_t temp_value;
	
	if(disp_value > 0xFFFF){sLCD_err(4);}
	
	disp_digit = disp_value % 16;		
	sLCD_set(disp_digit, 4);
	
	temp_value = disp_value / 16;
	disp_digit = temp_value % 16;
	if(disp_value < 0x10){disp_digit=0xFF;}
	sLCD_set(disp_digit, 3);
	
	temp_value = temp_value / 16;
	disp_digit = temp_value % 16;
	if(disp_value < 0x100){disp_digit=0xFF;}
	sLCD_set(disp_digit, 2);
	
	disp_digit = temp_value / 16;
	if(disp_value < 0x1000){disp_digit=0xFF;}
	sLCD_set(disp_digit, 1);
	
}
//*************************************************************************************************************************
void sLCD_oct(uint16_t disp_value){

	uint16_t temp_value;
	
	if(disp_value > 07777){sLCD_err(4);}
	
	disp_digit = disp_value % 8;		
	sLCD_set(disp_digit, 4);
	
	temp_value = disp_value / 8;
	disp_digit = temp_value % 8;
	if(disp_value < 07){disp_digit=0xFF;}
	sLCD_set(disp_digit, 3);
	
	temp_value = temp_value / 8;
	disp_digit = temp_value % 8;
	if(disp_value < 070){disp_digit=0xFF;}
	sLCD_set(disp_digit, 2);
	
	disp_digit = temp_value / 8;
	if(disp_value < 0700){disp_digit=0xFF;}
	sLCD_set(disp_digit, 1);
	
}

//*************************************************************************************************************************
void sLCD_bin(uint8_t disp_value){
	uint8_t temp_value;
	
	if(disp_value > 15){sLCD_err(4);}
	
	disp_digit = disp_value % 2;		
	sLCD_set(disp_digit, 4);
	
	temp_value = disp_value / 2;
	disp_digit = temp_value % 2;
	sLCD_set(disp_digit, 3);
	
	temp_value = temp_value / 2;
	disp_digit = temp_value % 2;
	sLCD_set(disp_digit, 2);
	
	disp_digit = temp_value / 2;
	sLCD_set(disp_digit, 1);

}
//*************************************************************************************************************************
