
#define SBIT_ADON     0
#define SBIT_CHS0     3
#define SBIT_ADFM     7

#include<pic16f877.h>

void delay(int cnt);
void ADC_Init(void);
int ADC_Read(int adcChannel);
