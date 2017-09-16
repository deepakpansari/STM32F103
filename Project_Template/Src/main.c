// System will run from internal clock as we didnt configure trhe rcc yet

// Including the necessary Header file
#include "stm32f1xx.h"
#include "clock.h"

// Start of someDelay Function to provide delay
void someDelay(){
	for(unsigned int i=0;i<60000;i++){
		for(unsigned int j=0;j<30;j++)__asm("NOP");
	}
}
// Start of the main Function
int main(void)
{
	//Initializing the clock
	clockConfig();

	// Configure the AHPB(Advance High Performance Bus) Clock for GPIOB
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;	// GPIOB Bus Clock Enabled

	// Set Mode, Type of Output For GPIO Pin
	// Mode	->	11,		CNF ->	00	Output Push Pull with Max 50MHZ Output Speed
	// We are setting GPIOB9
	GPIOB->CRH |=  (GPIO_CRH_MODE9);	// Set MODE9[1:0] to 11
	GPIOB->CRH &= ~(GPIO_CRH_CNF9);		// Set CNF9[1:0] to 00

	//Set the LED
	GPIOB->BRR |= (GPIO_BRR_BR9);	// Setting the GPIOB9 to Low
    while(1)
    {
    	// Now Blink the LED Forever
    	GPIOB->BSRR |= (GPIO_BSRR_BS9);	// Setting the bit to High

    	// Provide some delay
    	someDelay();

    	// Reset the LED Again
    	GPIOB->BRR |= (GPIO_BRR_BR9);	// Setting the bit to LOW

    	// provide some delay
    	someDelay();
    }
}

