void setupTimer(uint16_t period);
void startTimer();
void stopTimer();

#define		HFCLK				14000000
#define		SAMPLE_RATE			44100
#define		PERIOD				HFCLK/SAMPLE_RATE