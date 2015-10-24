
#include "Head.h"
#include "Drive.h"


#define MEAS_AVE_NUM 2 		//(* 60ms)

#define DIST_STOP_NEAR	 (DIST_TARGET-DIST_SENS_TRESH)  // mm
#define DIST_STOP_FAR		 3800	// mm

#define DIST_SLOW_ROT		 150		// mm
#define DIST_FAST_ROT 	 2000		// mm

#define DIST_SENS_TRESH  30			// mm
#define DIST_TARGET			 100

#define ROT_RANGE_LOW		 10			// %
#define ROT_RANGE_MID		 25			// %
#define ROT_RANGE_HI		 60			// %
#define ROT_RANGE_FULL 	 100		// %






static void Head_decision_block ( uint16_t dist );
static void Head_search_min ( uint8_t range );



//************************************************************************
void Head_measure_end ( uint16_t dist )
{

	static uint32_t distSum;
	static uint8_t cnt;
	
	if ( cnt < MEAS_AVE_NUM )
	{
		distSum += dist;
		cnt++;
  }
	else
	{
		cnt = 0;
		distSum /= MEAS_AVE_NUM;
		Head_decision_block ( distSum );
		
	}
}


//************************************************************************
static void Head_search_min ( uint8_t range )
{
	static uint8_t prevPer = 50;
	//static uint8_t minPer;
  static uint8_t actPer = 50;

	static uint8_t actRange = 0xFF;
	
	if ( range != actRange )
	{
		actPer = prevPer-(range/2);
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
			actPer += 3;
		}
		if ( ROT_RANGE_HI == actRange )
		{
			actPer += 5;
		}
		if ( ROT_RANGE_FULL == actRange )
		{
			actPer += 7;
		}
		
		Drive_head_per ( actPer );
	}
	else
	{
		actPer = prevPer-(range/2);	// Search again
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
	// ? steering
	
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
	
	
	
}