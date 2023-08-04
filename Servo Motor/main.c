#include "TM4C123.h"                    // Device header



/*****pins

Vcc pin	Red  = 5v
GND pin brown = GND 
PWM pin orange = PA4


*********/

void Delay_microsecond (int time );
void servo_0_degree (void);
void servo_90_degree (void);
void servo_180_degree (void);

int main ()
{
	SYSCTL->RCGCGPIO |= 0x01 ;     //clock for port A
	GPIOA->DEN |= 0x10 ;      //digital enable PA4
	GPIOA->DIR |= 0x10 ;     //make PA4 an output
	
	
	while (1){
		servo_0_degree();
		Delay_microsecond(1000000) ; //delay 2 seconds
		servo_90_degree() ;
		Delay_microsecond(1000000) ; //delay 2 seconds
		servo_180_degree();
		Delay_microsecond(1000000) ; //delay 2 seconds
	}
	
	
}
void servo_0_degree (void)
{
	
	int i;
	for (i = 0 ; i < 50 ; i++ ){
	 
		GPIOA->DATA |= 0x10 ; //pin 4 HIGH
		Delay_microsecond(600) ; //0.6 ms delay
		GPIOA->DATA &= ~0x10 ; //pin 4 LOW
		Delay_microsecond(19400) ;//19.4 ms delay
	}

}

void servo_90_degree (void)
{
	
	int i;
	for (i = 0 ; i < 50 ; i++ ){
	 
		GPIOA->DATA |= 0x10 ; //pin 4 HIGH
		Delay_microsecond(1400) ; //1,4 ms delay
		GPIOA->DATA &= ~0x10 ; //pin 4 LOW
		Delay_microsecond(18600) ;//18.6 ms delay
	}

}

void servo_180_degree (void)
{
	
	int i;
	for (i = 0 ; i < 50 ; i++ ){
	 
		GPIOA->DATA |= 0x10 ; //pin 4 HIGH
		Delay_microsecond(2400) ; //2.4 ms delay
		GPIOA->DATA &= ~0x10 ; //pin 4 LOW
		Delay_microsecond(17600) ;//17.6 ms delay
	}

}


void Delay_microsecond (int time)
{
	int i ;
	
	//Timer0 initialization
	SYSCTL->RCGCTIMER = 0x01;
	TIMER0->CTL = 0x00 ;  //disable timer
	TIMER0->CFG = 0x04 ;  //16bit mode
	TIMER0->TAMR = 0x2; //periodic mode
	TIMER0->TAILR = 16-1 ;  //Load value
	TIMER0->ICR -=0x1 ;
  TIMER0->CTL |=0x1 ;	
	
	for ( i = 0 ; i < time ; i++){
		
		while ((TIMER0->RIS & 0x01 ) == 0 ); //wait for timer flag
			TIMER0->ICR = 0x1 ; //clear timer interrupt
	}
	
}
