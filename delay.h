#define FREQ_1_5_MHZ 1500000
#define FREQ_3_MHZ 3000000
#define FREQ_6_MHZ 6000000
#define FREQ_12_MHZ 12000000
#define FREQ_24_MHZ 24000000
#define FREQ_48_MHZ 48000000


int delay_ms(int ms, int frq);
int delay_us(int us, int frq);
int setDCO(int frq);
