#include "stm32f10x.h"
#include "Delay.h"
#include "math.h"

//uint32_t sine[255];

const unsigned char wave[181] = {128,132,137,141,146,150,155,159,163,
																 168,172,176,180,184,188,192,196,200,
																 203,207,210,214,217,220,223,226,229,
																 232,234,237,239,241,243,245,247,248,
																 250,251,252,253,254,254,255,255,255,
																 255,255,255,255,255,254,253,252,251,
																 250,248,247,245,243,241,239,237,234,
																 232,229,226,223,220,217,214,210,207,
																 203,200,196,192,188,184,180,176,172,
																 168,163,159,155,150,146,141,137,132,
																 128,124,119,115,110,106,101,97,93,88,
																 84,80,76,72,68,64,60,56,53,49,46,42,
																 39,36,33,30,27,24,22,19,17,15,13,11,
																 9,8,6,5,4,3,2,1,1,0,0,0,0,0,1,1,2,3,
																 4,5,6,8,9,11,13,15,17,19,22,24,27,30,
																 33,36,39,42,46,49,53,56,60,64,68,72,
																 76,80,84,88,93,97,101,106,110,115,119,124,128};

// Config pin in port A
void ConfigPortA()
{
	RCC->APB2ENR |= 1 << 2; // Enable clock port A
	GPIOA->CRH &= 0x00000000; // Reset pin A8 -> A15
	GPIOA->CRH |= 0x11111111; // Set output push-pull pin A8 -> A15 
}

/*void SetupSin()
{
	double x, y;
	for (int i = 0; i < 256; i++)
		{
    x = (double)i;
    y = sin((x / 256) * 2 * 3.1415926535897932384626433832799);
    sine[i] = (int) (y * 128) + 128;
		}
}*/

// Generate a sine signal
void Sine_Funtion(uint32_t freq)
{
		for (int i = 0; i < 181; i++) 
		{
			GPIOA->ODR = wave[i] << 8; 
			Delay_ms(freq);
		}
}


// Generate a triangle signal
void Triangle_Funtion(uint32_t freq)
{
	for (int i = 0; i <= 255; i++)
		{
			GPIOA->ODR = i << 8;
			Delay_ms(freq/2);
		}

		for (int i = 255; i >= 0; i--)
		{
			GPIOA->ODR = i << 8;
			Delay_ms(freq/2);
		}
}

// Generate a saw signal
void Saw_Funtion(uint32_t freq)
{
	for (int i = 0; i <= 255; i++)
	{
		GPIOA->ODR = i << 8;
		Delay_ms(freq);
	}
		
}

// Generate a square signal
void Square_Funtion(uint32_t freq)
{
	for (int i = 0; i <= 255; i++)
	{
		GPIOA->ODR = 255 << 8;
		Delay_ms(freq/2);
	}
	for (int i = 255; i >= 0; i--)
	{
		GPIOA->ODR = 0 << 8;
		Delay_ms(freq/2);
	}
	
}
int main()
{
	initSysTickInterrupt();
	SysTick_Handler();
	ConfigPortA();
	//SetupSin();
	while (1)
	{
		//Sine_Funtion(20);
		//Triangle_Funtion(20);
		Square_Funtion(20);
		//Saw_Funtion(20);
	}
}
