/* Library for Clock Config
 * Options for Clock
 * Clock Option: 
 * 		1. HSI --> Internal High Speed Clock
 *		2. HSE --> External High Speed Clock
 *
 * Clock Speed:
 * 		1. SPEED_8  --> Internal or External clock with 8 MHZ no PLL (CSS OFF/ON) 
 *		2. SPEED_64 --> Internal HSI clock with PLL for 64 MHZ speed (CSS OFF)
 *		3. SPEED_72 --> External HSI clock with PLL for 72 MHZ (CSS ON)
 */ 

#ifndef CLOCKCONFIG
#define	CLOCKCONFIG

// Define speed Parameters
#define HSI			0
#define HSE 		1
#define SPEED_8		2
#define SPEED_72	3
#define SPEED_64	4

void clockConfig(uint8_t clock_type, uint8_t clock_speed){
	
	// If HSI with SPEED_8
	// HSI with PLL off and CSS OFF
	if(clock_type == HSI && clock_speed == SPEED_8){
		
		// On the HSI
		RCC->CR |= RCC_CR_HSION;
		
		// Wait for HSI to Ready
		while(!(RCC->CR & (RCC_CR_HSIRDY)));

		// APB1 takes prescaller of 1
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_2);

		// APB2 takes prescaller of 1
		RCC->CFGR &= ~(RCC_CFGR_PPRE2_2);

		// AHB Prescaler 1
		RCC-> CFGR &= ~(RCC_CFGR_HPRE_2);

		// PLL OFF 
		RCC->CR &= ~(RCC_CR_PLLON);

		// SYSCLOCK AS HSI
		RCC->CFGR &= ~(RCC_CFGR_SW_0 | RCC_CFGR_SW_1);
	}

	// Clock type HSI and speed 64 that is maximum with internal
	// HSI with PLL ON and CSS OFF
	else if(clock_type == HSI && clock_speed == SPEED_64){
		
		// HSI ON
		RCC->CR |= RCC_CR_HSION;
		
		// Wait for HSI to ready
		while(!(RCC->CR & (RCC_CR_HSIRDY)));

		// PLL Predivider 2 & PLL Clock source HSI
		RCC->CFGR &= ~(RCC_CFGR_PLLSRC);

		// Load PLL With Mul Factor
		RCC->CFGR |= (RCC_CFGR_PLLMULL_0 | RCC_CFGR_PLLMULL_1 |RCC_CFGR_PLLMULL_2 |RCC_CFGR_PLLMULL_3);


		// APB1 div 2, as max clock 36MHZ
		RCC->CFGR |= RCC_CFGR_PPRE1_2;
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_0);

		// APB2 div 1
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_2);

		// AHB Div 1
		RCC->CFGR &= ~(RCC_CFGR_HPRE_3);

		// Start the PLL
		RCC->CR |= RCC_CR_PLLON;

		// Wait till PLL Ready
		while(!(RCC->CR & (RCC_CR_PLLRDY)));

		// Select the sysclock Switch as PLL
		RCC->CFGR |= RCC_CFGR_SW_1;
		RCC->CFGR &= ~(RCC_CFGR_SW_0);
	}

	else if(clock_type == HSE && clock_speed == SPEED_72){

		// Chip is running by its internal 8Mhz Clock
		// Now set it to use external 8 mhz clock with PLLx9 and Sysclock as HSEXPLL
		// After This Chip will run at 72Mhz
		// CSS will be ON so if anything on HSE happens, chip with run on HSI with 64 MHZ

		// Set the clock input to HSE
		//RCC->CR |= RCC_CR_HSEON;

		// Wait till it enables
		//while(!(RCC->CR & (RCC_CR_HSERDY)));

		// CSS ON 
		//RCC->CR |= RCC_CR_CSSON;

		// Load PLL With Mul Factor
		//RCC->CFGR |= (RCC_CFGR_PLLMULL_0 | RCC_CFGR_PLLMULL_1 | RCC_CFGR_PLLMULL_2);
		//RCC ->CFGR &= ~(RCC_CFGR_PLLMULL_3);

		// PLL Prediv 1
		//RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);

		// Start the PLL
		//RCC->CR |= RCC_CR_PLLON;

		// Wait till PLL Ready
		//while(!(RCC->CR & (RCC_CR_PLLRDY)));

		// Select the sysclock Switch as PLL
		//RCC->CFGR |= RCC_CFGR_SW_1;
		//RCC->CFGR &= ~(RCC_CFGR_SW_0);

				//Configure the APB1 Prescaler to 2 because it's max speed is 36MHZ
		//RCC->CFGR |= RCC_CFGR_PPRE1_2;
		//RCC->CFGR &= ~(RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1);

		// APB2 Prescaler 1
		//RCC->CFGR &= ~(RCC_CFGR_PPRE2_2);

		//AHB Presecaler 1
		//RCC->CFGR &= ~(RCC_CFGR_HPRE_3);

		// Disable HSI to save power
		RCC->CR &= ~(RCC_CR_HSION);
	}
}
void NMI_Handler(){

	// Clearing the interrupt for CSS
	RCC->CIR |= RCC_CIR_CSSC;

	// Now system is running on HSI
}

#endif
