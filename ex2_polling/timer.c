#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "efm32gg.h"

/*
 * function to setup the timer 
 */

void setupTimer()
{
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;
	*TIMER1_CMD = 1;
}
void startTimer() {
	*TIMER1_CMD = 1;
}
void stopTimer() {
	*TIMER1_CMD = 0;
	*TIMER1_CNT = 0;
}
