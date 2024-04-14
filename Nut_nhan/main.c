#include "stm32f10x.h"

void ConfigOutput(void);
void ConfigInput(void);

void Delay_Ms(uint32_t nCount) 
{
  while(nCount--);
}

void ConfigOutput(void)
{
	RCC->APB2ENR |= 0x10;
	GPIOC->CRH &= ~(0xFF0FFFFF);
	GPIOC->CRH |=  0x00300000;
}

void ConfigInput(void)
{
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &= ~(0x0FU);
	GPIOA->CRL |= 0x08U;
	GPIOA->ODR |= 0x01U;
}

int main(void)
{
	ConfigInput();
	ConfigOutput();
	uint32_t u32Count = 0U;
	GPIOC->ODR &= ~(0x2000U);

	while(1)
	{
		if((GPIOA->IDR & GPIO_IDR_IDR0) == 0U) 
		{
			Delay_Ms(100U);
			while((GPIOA->IDR & GPIO_IDR_IDR0) == 0U);
			u32Count++;
			if(u32Count % 2 != 0) 
			{
				GPIOC->ODR &= ~(0x2000);
			} 
			else 
			{
				GPIOC->ODR |= 0x2000;
			}
		}
	}
}
