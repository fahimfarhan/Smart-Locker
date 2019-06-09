#pragma GCC push_options
#pragma GCC optimize ("01")

#define F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

volatile int overflowCount ;
volatile int lastPIRresponse ;
volatile int mode  ;
#define SPEAKER_PORT PORTA

#define SPEAKER_DDR DDRA

#define SPEAKER_PIN 7
//mode = 0 means no timer, no buzzer
//mode = 1 means motion detected, timer starts
//mode = 2 means  intruder confirmed , buzzer starts

void PLAYNOTE(float duration, float frequency);

ISR(TIMER1_OVF_vect){
	
	if(mode==1){
		overflowCount++;
		if(overflowCount>=320)
		{
			if(lastPIRresponse<150){mode = 0 ;}
			else {mode = 2;}
			overflowCount=0;
		}
		PORTA = (overflowCount/10);
	}
	else if(mode == 2)
	{
		PLAYNOTE(10, 1200);
		//PORTA = 0xA;
	}
	else{
		PORTA = 0xA ;
	}
}
int main(void)
{
	overflowCount = 0 ;
	DDRA = 0xff ;
	DDRB = 0x00 ;
	PORTB = 0x00 ;
	//configure Timer
	TCCR1A = 0x00 ;
	TCCR1B = 0x01 ;
	TIMSK = 0x04 ;
	mode=0;
	sei();//global interrupt enable 
	while(1)
	{
		//PORTA = 0x1f ;
		if((PINB&(1<<1))!=0)
		{
			//PORTA=0x6;
			mode = 0 ;
			_delay_ms(1000);
		}
		else if((PINB&(1<<0))!=0)
		{
			//PORTA = 0x9;
			if(mode==0)mode = 1 ;
			lastPIRresponse = overflowCount;
		}
		else
		{
			//PORTA=0x7;
		} 	
	}
	cli();


}

void PLAYNOTE(float duration, float frequency)
{

   // Physics variables
	int i ;
      const int half_period = 2; 

   const float wavelength=(1/frequency)*1000; 

   // Standard physics formula.

   const int cycles=duration/wavelength; 

   // The number of cycles.



   // The time between each toggle.

   // Data direction register Pin 7

   // is set for output.

   SPEAKER_DDR |= (1 << SPEAKER_PIN);

   

   for (i=0;i<cycles;i++) 

   // The output pin 7 is toggled

   // for the 'cycles'number of times.

   // --------------------------------
   {

   	 _delay_ms(half_period); 

     // Wait 1 half wavelength.

     SPEAKER_PORT |= (1 << SPEAKER_PIN); 

     // Output 5 V to port Pin 7.

     _delay_ms(half_period); 

     // Wait 1 half wavelength.

     SPEAKER_PORT &= ~(1 << SPEAKER_PIN); 

     // 0 V at port pin 7.

   }
   return; 

   // Return to main()

   

}

#pragma GCC pop_options
