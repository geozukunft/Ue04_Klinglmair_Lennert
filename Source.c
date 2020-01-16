/*#include <stdio.h>
#include <avr/io.h>
#include "..\DriverLibHW\LCD.h"
#include "..\DriverLibHW\Wait.h"
//#include "..\DriverLibHW\USART.h"
#include "C:\Users\geozu\Documents\Arduino\DriverLibHW\USART.h"

char duty_cycle_output[16];

int main(void)
{
	DDRD = ~0x0C;
	PORTD = 0x0C;


	DDRB = 0x60;		// PortB.5 and PortB.6 as Output
	PIND = 0xF3;
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);    // Fast PWM 8 Bit, mode 5
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);      // OC1A and OC1B cleared on compare match
															// and set at BOTTOM. Clock Prescaler 1024.
	OCR1A = 254;                           // Dutycycle of OC1A = 0%     
	OCR1B = 127;                          // Dutycycle of OC1B = 50% 


	LCDInit(); // Initialisieren des LCD
	LCDClear(); // Loeschen des LCD

	USARTInit(0, 9600, 1, 0, 1, 0);


	LCDString(1, 4, "Duty Cycle ");
	int i = 0;
	int duty_cycle[11] = { 0, 25, 50, 76, 102, 127, 152, 178, 203, 229, 254 };
	int duty_percent[11] = { 00, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };



	while (1)
	{
		if (((~PIND & 0x04) >> 2))
		{
			if (i != 0)
			{
				i--;
				OCR1A = duty_cycle[i];
				OCR1B = duty_cycle[i];
				printf("%i\n", duty_percent[i]);
				LCDClearLine(2);
				sprintf(duty_cycle_output, "%i%% ", duty_percent[i]);

				LCDString(2, 7, duty_cycle_output);
				WaitMs(200);
			}


		}
		else if (((~PIND & 0x08) >> 3))
		{
			if (i != 10)
			{
				i++;
				OCR1A = duty_cycle[i];
				OCR1B = duty_cycle[i];

				printf("%i\n", duty_percent[i]);
				sprintf(duty_cycle_output, "%i%% ", duty_percent[i]);

				LCDClearLine(2);
				LCDString(2, 7, duty_cycle_output);
				WaitMs(200);

			}
		}






	}

}*/






#include <avr/io.h>
#include "C:\Users\geozu\source\DriverLibHW\USART.h"
#include "C:\Users\geozu\source\DriverLibHW\LCD.h"
#include "C:\Users\geozu\source\DriverLibHW\Wait.h"
#include <stdio.h>



uint16_t duty_cycle[11][11] = { { 0,6400,12800,19200,25600,32000,38400,44800,51200,57600, 64000},
{0,5300, 10666, 16000, 21333, 26666, 31999, 37333, 42666, 47999, 53333},
{0,4571,9142,13714,18285,22857,27428,31999,36571,41142,45714},
{0,4000,8000,12000,16000,20000,24000,28000,32000,36000,40000},
{0,3555,7111,10666,14222,17778,21333,2489,28444,32000,35556},
{0,3200,6400,9600,12800,16000,19200,22400,25600,28800,32000},
{0,2909,5818,8727,11636,14545,17454,20363,23272,26181,29091},
{0,2666,5333,8000,10666,13333,16000,18666,21333,24000,26667},
{0,2461,4923,7384,9846,12307,14769,17230,19692,22153,24615},
{0,2285,4571,6857,9142,11428,13714,15999,18285,20571,22857},
{0,2133,4266,6399,8533,10666,12799,14933,17066,19199,21333} };


int duty_percent[11] = { 0,10,20,30,40,50,60,70,80,90,100 };


uint16_t pwm_frequency[11] = { 64000, 53333, 45714, 40000, 35556, 32000, 29091, 26667, 24615, 22857, 21333 };

int pwm_frequency_percent[11] = { 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750 };


void print_duty_freq(int i)
{
	char duty_cycle_string[16];

	if (i == 10)
	{
		LCDString(2, 5, "%");
		sprintf(duty_cycle_string, "%i", duty_percent[i]);	 //fill duty cycle string 
		LCDString(2, 2, duty_cycle_string);				 //print duty cycle string
		LCDString(2, 5, "% ");
	}
	else if (i == 0)
	{
		LCDClearLine(2);
		LCDString(2, 5, "%");
		sprintf(duty_cycle_string, "%i", duty_percent[i]);	 //fill duty cycle string 
		LCDString(2, 4, duty_cycle_string);				 //print duty cycle string
		LCDString(2, 5, "% ");
	}
	else if (i == 9)
	{
		LCDClearLine(2);
		LCDString(2, 5, "%");
		sprintf(duty_cycle_string, "%i", duty_percent[i]);	 //fill duty cycle string 
		LCDString(2, 3, duty_cycle_string);				 //print duty cycle string
		LCDString(2, 5, "% ");
	}
	else
	{
		LCDString(2, 5, "%");
		sprintf(duty_cycle_string, "%i", duty_percent[i]);	 //fill duty cycle string 
		LCDString(2, 3, duty_cycle_string);				 //print duty cycle string
		LCDString(2, 5, "% ");
	}

	LCDString(2, 10, "244Hz ");


}



void main()
{

	int duty = 10;
	int freq = 10;

	DDRD = ~0x0C;
	PORTD = 0x0C;

	DDRB = 0xFF;									 // PortB.6 as Output   
	//PORTB = 0x40;

	LCDInit();
	LCDClear();

	TCCR1A = (1 << WGM10) | (1 << COM1B1) | (1 << COM1B0);	 // Fast PWM 8 Bit, mode 15  

	TCCR1B = (1 << WGM12) | (1 << CS12);					 // OC1B cleared on compare match                                   
																		// and set at BOTTOM. Clock Prescaler 256.     
	OCR1B = 0;											 // Start-Dutycycle of OC1B = 0%
	OCR1A = 21333;

	LCDString(1, 1, "Tastver.");
	LCDString(1, 10, "Freq.");

	



	while (1)
	{
		print_duty_freq(duty);
		if ((PIND & 0x04) == 0)
		{
			if (duty < 10)
			{
				duty++;

				WaitMs(200);

				print_duty_freq(duty);

				OCR1B = duty_cycle[freq][duty];
			}
		}

		if ((PIND & 0x08) == 0)
		{
			if (duty > 0)
			{
				duty--;

				WaitMs(200);

				print_duty_freq(duty);

				OCR1B = duty_cycle[freq][duty];
			}

		}
	}
}


