

#include "ADC.h"



/***************************
Delay Simple
******************************/
void delay(int cnt)
{
    while(cnt--);
}

/************************
Inicializacion del ADC
**************************/
void ADC_Init()
 {
    /*
    ADCON0 -> ADCS0 = 0
    ADCON0 -> ADCS1 = 0
    ADCON1 -> ADCS2 = 0	=> ESTE REGISTRO SOLO SE TOMA EN CUENTA SI SE UTILIZA EL PIC16F877a
    => CON ESTA CONFIGURACION, SE UTILIZA FREQ = OSC_FREQ / 2
    
    ADCON0 -> CHS0 = 0 
    ADCON0 -> CHS1 = 0
    ADCON0 -> CHS2 = 0 

   000 = Channel 0 (AN0)	=> POR DEFECTO PONEMOS AN0, PERO LUEGO SE RECIBE POR PARAMETRO
   001 = Channel 1 (AN1)
   010 = Channel 2 (AN2)
   011 = Channel 3 (AN3)
   100 = Channel 4 (AN4)
   101 = Channel 5 (AN5)
   110 = Channel 6 (AN6)
   111 = Channel 7 (AN7)
    
   ADCON0 -> GO/DONE = 0 	=> (setting this bit starts the A/D conversion which is automatically cleared by hardware when the A/D conversion is complete)
   Inicializado en 0 para que no comience ninguna conversion.
   
   ADCON0 -> ADON = 0 		=> (A/D converter module is shut-off and consumes no operating current)
    
    */
   ADCON0=0x00;  				// FREQ = OSC_FREQ / 2 && ADC Apagado
   ADCON1=(1<<SBIT_ADFM);  	// All pins are configured as Analog pins and ADC result is right justified  
   /*
   ADCON1->ADFM = 1		=> Right justified. Six (6) Most Significant bits of ADRESH are read as ‘0’.
   IF  (ADCON1->ADFM = 0)	=> Left justified. Six (6) Least Significant bits of ADRESL are read as ‘0’.
   */
}

/************************
Leo el valor del ADC
**************************/
int ADC_Read(int adcChannel)
 {  
    ADCON0 = (1<<SBIT_ADON) | (adcChannel<SBIT_CHS0);  
    /*ADCON0 -> ADON = 1 				=> ENCIENDO EL ADC
      ADCON0 -> CHS[0:2] = adcChanel		=> Eligo el canal que quiero (AN0 hasta AN7)
    */

    delay(1000);                   	//Acquisition Time(Wait for Charge Hold Capacitor to get charged )
   
    GO=1;                           	// Start ADC conversion
    while(GO_DONE==1);      	/*GO/DONE: A/D Conversion Status bit
						When ADON = 1:
						1 = A/D conversion in progress (setting this bit starts the A/D conversion which is automatically cleared by hardware when the A/D conversion is complete)
						0 = A/D conversion not in progress*/

    return((ADRESH<<8) + ADRESL);  	/* Retorno los 10 bits en orden. Es decir, muevo la parte supeior a los
								  8 bits superiores y le sumo los 8 bits inferiores */
 }