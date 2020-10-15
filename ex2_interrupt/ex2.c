#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
#include "timer.h"




/*
 * Declaration of peripheral setup functions 
 */

void enableDAC();
void setupNVIC();
void setupGPIO();
void setupNVIC();

/*
* Declaration of sound functions
*/


int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */

	setupGPIO();
	enableDAC();
	setupTimer(PERIOD);
	setupNVIC();

	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */

	return 0;
}
void setupNVIC()
{
	*ISER0 |= (GPIO_EVEN_ISER0 | GPIO_ODD_ISER0 | TIMER1_ISER0);
}