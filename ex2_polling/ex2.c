#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "timer.h"
#include "sound.h"



/*
 * Declaration of peripheral setup functions 
 */

void setupDAC();
void enableDAC();
void disableDAC();
void setupGPIO();


void soundOutput(uint8_t output, char strength);
void sounds(Sound *wave);
void selectSound(char button); 

int i = 0;
bool playing = true, startUp = true;
uint8_t button = 0, buttonPrev = 0;

struct Sound* currentSound; //Pointer to struct


int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer();

    selectSound(3);
    char mask = 1; //Mask bit
    
    while (1) {
        if (playing == true) {
            sounds(currentSound);
        }else {
            button = *GPIO_PC_DIN ^ 0xFF;
            char buttonLoc = 0;
            if (button != 0 && buttonPrev != button) {
                while (!((button >> buttonLoc) & mask)) buttonLoc++;
                buttonLoc++;
                startTimer();
                enableDAC();
                playing = true;
                *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
                selectSound(buttonLoc);
            }
            buttonPrev = button;
        }
    }
	return 0;
}


void soundOutput(uint8_t output, char strength) {
    *DAC0_CH0DATA = output << strength;
    *DAC0_CH1DATA = output << strength;
}
void sounds(Sound* wave) {
    if (*TIMER1_CNT >= PERIOD) {
        *TIMER1_CNT = 0;
        if (i < wave->length){
            soundOutput(wave->samples[i], 4);
            i++;
        }else{
            i = 0;
            if (startUp) {
                selectSound(2);
                startUp = false;
            }
            else {
                playing = false;
                stopTimer();
                disableDAC();
            }
        }
    }
}
void selectSound(char button) {
    switch (button) {
        case 1: currentSound = &impact;     break;
        case 2: currentSound = &pause_in;   break;
        case 3: currentSound = &pause_out;  break;
        case 4: currentSound = &landing;    break;
        default: currentSound = &jump;      break;
    }
}