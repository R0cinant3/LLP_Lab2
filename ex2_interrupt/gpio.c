#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"


void setupGPIO()
{

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	/* enable GPIO clock */
	*GPIO_PA_CTRL = 2;	/* set high drive strength */
	*GPIO_PA_MODEH = 0x55555555;	/* set pins A8-15 as output */
	*GPIO_PA_DOUT = 0xFF00;	/* turn on LEDs D4-D8 (LEDs are active*/

	*GPIO_PC_MODEL = 0x33333333;	
	*GPIO_PC_DOUT = 0x00FF;

	*GPIO_EXTIPSELL = 0x22222222; 
	*GPIO_IEN = 0xFF;
	*GPIO_EXTIRISE = 0xFF; 
	*GPIO_EXTIFALL = 0xFF;

}

