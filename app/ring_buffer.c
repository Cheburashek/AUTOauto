/* Includes ------------------------------------------------------------------*/

#include "ring_buffer.h"
#include <stdlib.h>
#include "sLCD.h"

//************************************************************************

void RingBuffer_Init( RingBuffer *ringBuffer ) 
{	
	   		
      uint8_t size = RB_SIZE;
      
      ringBuffer->pStart = ringBuffer->rTab;
		ringBuffer->pEnd = ringBuffer->pStart;		
		
		while( size ){
			
			*ringBuffer->pEnd = 0x00;
			
			ringBuffer->pEnd ++;
			size --;
			
		}
		
		// Buffer is empty:
		ringBuffer->pHead = ringBuffer->pStart;
		ringBuffer->pTail = ringBuffer->pStart;

}

//************************************************************************

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	
	if (ringBuffer) {
		
		ringBuffer->pHead = ringBuffer->pStart;
		ringBuffer->pTail = ringBuffer->pHead;
		
		return true;
	}
	
	return false;
}

//************************************************************************

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{

	if( ringBuffer->pTail == ringBuffer->pHead ){
			    
		return true;
	}
	
	return false;
}

//************************************************************************

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	size_t len = 0;
	uint8_t* pLen = ringBuffer->pHead;

	if (ringBuffer) {
		
		while( pLen != ringBuffer->pTail ){
		
			len ++;
			pLen ++;
			
			if( pLen > ringBuffer->pEnd ){
				pLen = ringBuffer->pStart;	
			}
		}	
		return len;		
	}
	return 0;	
}

//************************************************************************

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{ 

	if (ringBuffer) {
		
		return ((ringBuffer->pEnd - ringBuffer->pStart) / sizeof(uint8_t));
			
	}
	return 0;	
}

//************************************************************************

bool RingBuffer_PutChar(RingBuffer *ringBuffer, uint8_t c)
{

	if (ringBuffer) {
		
		// When buffer is not full:
		if( (ringBuffer->pTail == (ringBuffer->pHead - 1)) || 
		   ((ringBuffer->pTail == ringBuffer->pEnd) &&
		    (ringBuffer->pHead == ringBuffer->pStart)) ){	
			    
			    return false;
			    
		}
		else{			
			*ringBuffer->pTail = c;
			ringBuffer->pTail ++;
		
			// When Tail pointer exceed area of ring buffer:
			if( ringBuffer->pTail > ringBuffer->pEnd ){				
				ringBuffer->pTail = ringBuffer->pStart;				
			}			
			return true;			
		}			
	}
	return false;	
}

//************************************************************************

bool RingBuffer_GetChar(RingBuffer *ringBuffer, uint8_t *c)
{

	   // When buffer is not empty:
		if( ringBuffer->pHead != ringBuffer->pTail ){
		  
			*c = *ringBuffer->pHead;
			ringBuffer->pHead ++;
			
			// When Head pointer exceed area of ring buffer:
			if( ringBuffer->pHead > ringBuffer->pEnd ){
         
				ringBuffer->pHead = ringBuffer->pStart;	
			}			
			return true; 
		}	
      
	return false;
}