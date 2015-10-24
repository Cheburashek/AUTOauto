
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
#define STOP_DIST 500


static void Head_decision_block ( uint16_t dist );
static void Head_search_min ( uint8_t range );
static void Head_goto_min ( uint8_t minPer, uint16_t minDist );


bool motorPermFlag = true;

//************************************************************************
void Head_measure_end ( uint16_t dist )
{

//	static uint32_t distPrev;
//	static uint8_t inerCnt;
//	
//	if ( ((distPrev+INERTION) < dist) || ((distPrev-INERTION) > dist) )
//	{
//		inerCnt++;
//	}
//	else
//	{
//		inerCnt = 0;
//		distPrev = dist;
//		Head_decision_block ( distPrev );
//	}
//  
//	if ( INER_NUM == inerCnt )
//	{
//		inerCnt = 0;
//		distPrev = dist;
//		Head_decision_block ( distPrev );
//	}

	static uint8_t actPer = 50;
	static bool dir = false;
	static uint16_t minDist = 0xFFFF;
	static uint8_t minPer = 0xFF;
	
	if ( minDist > dist )
	{
		minDist = dist;
	}
	
	if ( minPer > actPer )
	{
		minPer = actPer;
	}
	
  if ( dir )
	{
		actPer += 5;
	}
	else
	{
		actPer -= 5;
	}
	
	if ( ((0+RANGE) >= actPer) || ((100-RANGE) <= actPer) )
	{
		//Head_goto_min ( minPer, minDist );
		
		uint8_t data[] = { CMD_PREFIX, 0x10, 0x03, minPer, (uint8_t)(minDist>>8), (uint8_t)minDist };
		UART_data_send ( data, sizeof ( data ) );
		
		dir ^= 1;
		minDist = 0xFFFF;
		minPer = 0xFF;
		
	}		
		//Head_goto_min ( minPer, minDist );

	Drive_head_per ( actPer );
		
	if ( minDist < STOP_DIST )		// STOP
	{
		Drive_motor_init ( );	
		motorPermFlag = false;
	}
	else
	{
		motorPermFlag = true;
	}

}


static void Head_goto_min ( uint8_t minPer, uint16_t minDist )
{
	Drive_steer_per ( (minPer*100)/(100-2*RANGE) );
	//Drive_steer_per ( minPer );
	
	if ( minDist > STOP_DIST )
	{
		Drive_motor_slow();
	}
	
}








//************************************************************************
static void Head_search_min ( uint8_t range )
{
	static uint8_t prevPer = 50;
	//static uint8_t minPer;
  static uint8_t actPer = 50;
	//static uint8_t direction = CLOCKWISE;
	
	static uint8_t actRange = 0xFF;
	
	if ( range != actRange )
	{
		actPer = prevPer-range;
		prevPer = actPer;
	}

	if ( actPer <= (actPer+actRange) )
	{
		if ( ROT_RANGE_LOW == actRange )
		{
			actPer += 1;
		}
		if ( ROT_RANGE_MID == actRange )
		{
			actPer += 2;
		}
		if ( ROT_RANGE_HI == actRange )
		{
			actPer += 3;
		}
		if ( ROT_RANGE_FULL == actRange )
		{
			actPer += 4;
		}
		
		Drive_head_per ( actPer );
	}

	
	

}


//************************************************************************
static void Head_decision_block ( uint16_t dist )
{
	// Stop and scan:
	if ( (DIST_STOP_NEAR >= dist) && (DIST_STOP_FAR <= dist) )
	{
		Drive_motor_per ( 0 );	// Stop motor
		Head_search_min ( ROT_RANGE_FULL );				// Scan for minimal distance
		
	}
	// Target:
	else if ( ((DIST_TARGET+DIST_SENS_TRESH) >= dist) && ((DIST_TARGET-DIST_SENS_TRESH) <= dist) )
	{
	uint8_t a = 1;
		a = 2;
	
	}
	
	// Slow rotation:
	else if ( (DIST_SLOW_ROT >= dist) && (DIST_STOP_NEAR <= dist) )
	{
		Head_search_min ( ROT_RANGE_LOW );				// Scan for minimal distance

	}		
	// Medium rotation:
  else if ( (DIST_SLOW_ROT <= dist) && (DIST_FAST_ROT >= dist) )
	{
		Head_search_min ( ROT_RANGE_MID );				// Scan for minimal distance

	}
	// Hi rotation:
  else if ( (DIST_FAST_ROT <= dist) && (DIST_STOP_FAR >= dist) )
	{
		Head_search_min ( ROT_RANGE_HI );				// Scan for minimal distance

	}	
	else
	{
			Head_search_min ( ROT_RANGE_MID );				// Scan for minimal distance

	}
	
	
	
}