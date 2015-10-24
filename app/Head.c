
#include "Head.h"
#include "Drive.h"
#include "USART.h"

#define DIST_STOP_NEAR	 (DIST_TARGET + 700)  // mm
#define DIST_STOP_FAR		 3800	// mm

#define DIST_SLOW_ROT		 (DIST_TARGET-DIST_SENS_TRESH)		// mm
#define DIST_FAST_ROT 	 2000		// mm

#define DIST_SENS_TRESH  100			// mm
#define DIST_TARGET			 1000

#define ROT_RANGE_LOW		 10			// %
#define ROT_RANGE_MID		 25			// %
#define ROT_RANGE_HI		 60			// %
#define ROT_RANGE_FULL 	 100		// %

#define INERTION  			 70
#define INER_NUM				 6

#define CLOCKWISE 0x10
#define CNTCLOCKWISE 0x11


// New implem
#define RANGE 20
#define STOP_DIST 1500


static void Head_decision_block ( uint16_t dist );
static void Head_search_min ( uint8_t range );
static void Head_goto_min ( uint8_t minPer, uint16_t minDist );


bool motorPermFlag = true;

//************************************************************************
void Head_measure_end ( uint16_t dist )
{
		static uint8_t cnt;
		
	if ( dist < STOP_DIST )		// STOP
	{
		Drive_motor_init ( );	
		motorPermFlag = false;
		Drive_horn_beep ( 0x01 );
	}
	else
	{
		motorPermFlag = true;
		Drive_horn_beep ( 0x00 );
	}
	
	cnt ++;	
	
	if ( cnt == 10 )
	{
		uint8_t data[] = { CMD_PREFIX, 0x10, 0x02, (uint8_t)(dist>>8), (uint8_t)dist };
		
		UART_data_send ( data, sizeof ( data ) );
		cnt = 0;	
	}
}
