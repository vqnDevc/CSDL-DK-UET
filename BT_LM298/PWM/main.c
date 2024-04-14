#include "stm32f10x.h"

void PWM_Timer2_Reister(uint32_t u32Speed)
{
	// enable clock cho timer2
	RCC->APB1ENR |= 0x01;
	// dat gia tri reload, no tuong duong voi chon tan so, chon do rong xung 
	TIM2->ARR = 10000-1;
	// chia clock, set tgian cho 1 tick
	TIM2->PSC = 720-1;
	// chon pwm mode 1 (xung thuan) : dat bit [6:4] = 110
	TIM2->CCMR1 = 0x60;
	/* dat do rong muc cao/thap mong muon, CCR1 la dung cho chan PA0, max la 4 chan 
	tuong duong CCR2,3,4 dieu khien cho PB0, PC0, PD0 */
	TIM2->CCR1 = 10000*u32Speed/100;
	/* bit cc1e trong thanh ghi chon input/output cho dau phat
	con bit cc1p trong thanh ghi chon xem muc mong muon la muc cao hay muc thap (0:cao, 1:thap) */
	TIM2->CCER = 0x01;
	// enable counter
	TIM2->CR1 = 0x01;
	// enable bit UDIS de cap nhap su kien, vi ben tren set tran roi ben cai nay khong can lam
	//TIM2->EGR = 0x01;
}

void Timer2_Register(void)
{
	/* enable clock cho timer2 */
	RCC->APB1ENR |= 0x01;
	/* Dat reload la gia tri cao nhat */
	TIM2->ARR |= 0xFFFF;
	/* Set gia tri cho thanh PSC de chia: 1 tick = fCLK/(PSC[15]-1) */
	TIM2->PSC = 71;
	TIM2->CR1 |= 0x01;
	TIM2->EGR |= 0x01;
}

void Delay_Timer2_Ms(uint32_t u32Delay)
{
	while(u32Delay)
	{
		TIM2->CNT = 0U;
		while((TIM2->CNT) < 1000);
		u32Delay--;
	}
}

void Inout(void)
{
	RCC->APB2ENR |= 0x04;
	GPIOA->CRL &= ~0x0FFFFF;
	GPIOA->CRL |= 0x08833B;
	
	GPIOA->ODR |= GPIO_ODR_ODR2;
	GPIOA->ODR &= ~GPIO_ODR_ODR1;
	GPIOA->ODR |= GPIO_ODR_ODR3;
	GPIOA->ODR |= GPIO_ODR_ODR4;
}

int main()
{
	Inout();
	Timer2_Register();
	uint32_t u32Count = 40;
	uint32_t u32Count1 = 0;
	PWM_Timer2_Reister(u32Count);
	
	while(1)
	{
		if((GPIOA->IDR & GPIO_IDR_IDR3) == 0U) 
		{
			Delay_Timer2_Ms(2U);
			while((GPIOA->IDR & GPIO_IDR_IDR3) == 0U);
			u32Count = u32Count+20;
			PWM_Timer2_Reister(u32Count);
			if(u32Count == 100)
			{
				u32Count = 20;
			}
		}
		
		if((GPIOA->IDR & GPIO_IDR_IDR4) == 0U) 
		{
			Delay_Timer2_Ms(200U);
			while((GPIOA->IDR & GPIO_IDR_IDR4) == 0U);
			u32Count1 += 1;
			if(u32Count1 % 2 != 0)
			{
				GPIOA->ODR &= ~GPIO_ODR_ODR2;
				GPIOA->ODR |= GPIO_ODR_ODR1;
			} else
			{
				GPIOA->ODR |= GPIO_ODR_ODR2;
				GPIOA->ODR &= ~GPIO_ODR_ODR1;
			}
		}
	}
}
		

