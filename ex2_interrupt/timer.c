#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "efm32gg.h"

void setupTimer(uint16_t period)
{
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;
	*TIMER1_TOP = period;
	*TIMER1_IEN = 1;
	*TIMER1_CMD = 1;
}
void startTimer() {
	*TIMER1_CMD = 0x1;
}
void stopTimer() {
	*TIMER1_CMD = 0x2;
	*TIMER1_CNT = 0;
}