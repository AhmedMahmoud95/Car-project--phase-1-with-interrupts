#include "softwareDelay.h"

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the milli-seconds
 */

 #define MILLISECOND_ON_KIT 270
 #define MILLISECOND_ON_SIMULATION 30

void SwDelay_ms(uint32 n)
{
	while (n--)
	{
	    uint32 i;
		for (i =0; i<MILLISECOND_ON_SIMULATION; i++);
	}
}
