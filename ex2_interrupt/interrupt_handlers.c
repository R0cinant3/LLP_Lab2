#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
#include "sound.h"
#include "timer.h"

void enableDAC();
void disableDAC();
void buttonId();
void soundSelect(uint8_t button);

struct Sound *currentSound; 

bool buttonState = false;
bool startup = true;

uint32_t i = 0;
/*
 * TIMER1 interrupt handler 
 */

void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	play(currentSound);
	*TIMER1_IFC = *TIMER1_IF;
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	buttonId();
	*GPIO_IFC = *GPIO_IF;
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	buttonId();
	*GPIO_IFC = *GPIO_IF;
}

void soundSelect(uint8_t select) {
	switch (select) {
	case 0: currentSound = &uni;		break;
	case 1: currentSound = &impact;     break;
	case 2: currentSound = &pause_in;   break;
	case 3: currentSound = &pause_out;  break;
	case 4: currentSound = &landing;    break;
	default: currentSound = &jump;      break;
	}
}

void soundOutput(uint8_t output, char strength) {
	*DAC0_CH0DATA = output << strength;
	*DAC0_CH1DATA = output << strength;
}

void play(Sound* melody) {
	if (buttonState||startup) {
		if (startup) soundSelect(0);
		if (i < melody->length) {
			soundOutput(melody->samples[i], 2);
			i++;
		}
		else {
			i = 0;
			buttonState = false;
			startup = false;
			disableDAC();
			stopTimer();
			*SCR = 0x6;
		}
	}
}

void buttonId() {
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
	uint8_t button = *GPIO_PC_DIN ^ 0xFF;
	uint8_t mask = 1; //Mask bit
	uint8_t buttonLoc = 0; //Button location
	if (button != 0) {
		while (!((button >> buttonLoc) & mask)) buttonLoc++;
		soundSelect(buttonLoc + 1);
		buttonState = true;
		startTimer();
		enableDAC();
		*SCR = 0x0;
	}
}