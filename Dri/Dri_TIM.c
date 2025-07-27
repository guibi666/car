#include "Dri_TIM.h"

//定时器4初始化，CH3，CH4输出PWM波形
void Dri_TIM4_Init(void)
{
    /* 1.  开启时钟*/
    /* 1.1 定时器4的时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    /* 1.2 GPIO的时钟 PA */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* 2. 设置GPIO的复用推挽输出 PA1 CNF=10 MODE=11*/
    GPIOB->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
    GPIOB->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOB->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1);
    GPIOB->CRH &= ~GPIO_CRH_CNF8_0;

    /* 3. 定时器配置 */
    /*PWM输出频率 = 72M / PSC / ARR ;*/
    /* 3.1 预分频器的配置 */
    TIM4->PSC = 72 - 1;
    /* 3.2 自动重装载寄存器的配置 */
    TIM4->ARR = 100 - 1;
    /* 3.3 计数器的计数方向 0=向上 1=向下*/
    TIM4->CR1 &= ~TIM_CR1_DIR;

    /* 3.4 配置通道3的捕获比较寄存器 */
    TIM4->CCR3 = 0;
    /* 3.5 把通道3配置为输出  CCMR2_CC3S=00 */
    TIM4->CCMR2 &= ~TIM_CCMR2_CC3S;
    /* 3.6 配置通道的输出比较模式 CCMR2_OC3M=110 */
    TIM4->CCMR2 |= TIM_CCMR2_OC3M_2;
    TIM4->CCMR2 |= TIM_CCMR2_OC3M_1;
    TIM4->CCMR2 &= ~TIM_CCMR2_OC3M_0;
    /* 3.7 使能通道2  CCER_CC3E=1 */
    TIM4->CCER |= TIM_CCER_CC3E;
    /* 3.8 设置通道的极性 0=高电平有效  1=低电平有效 */
    TIM4->CCER &= ~TIM_CCER_CC3P;

    /* 3.4 配置通道4的捕获比较寄存器 */
    TIM4->CCR4 = 0;
    /* 3.5 把通道3配置为输出  CCMR2_CC4S=00 */
    TIM4->CCMR2 &= ~TIM_CCMR2_CC4S;
    /* 3.6 配置通道的输出比较模式 CCMR2_OC4M=110 */
    TIM4->CCMR2 |= TIM_CCMR2_OC4M_2;
    TIM4->CCMR2 |= TIM_CCMR2_OC4M_1;
    TIM4->CCMR2 &= ~TIM_CCMR2_OC4M_0;
    /* 3.7 使能通道2  CCER_CC4E=1 */
    TIM4->CCER |= TIM_CCER_CC4E;
    /* 3.8 设置通道的极性 0=高电平有效  1=低电平有效 */
    TIM4->CCER &= ~TIM_CCER_CC4P;

    /*启动定时器*/
    TIM4->CR1 |= TIM_CR1_CEN;
}

//定时器2编码器模式初始化，CH1,CH2
void Dri_TIM2_Init(void)
{
    /* 1.  开启时钟*/
    /* 1.1 定时器4的时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    /* 1.2 GPIO的时钟 PA,PB,AFIO时钟 */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);

    /*GPIO重映射*/
    /*关闭JTAG功能，保留SWD开启SWJ_CFG=010*/
    AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;

    /*重映射*/
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_FULLREMAP;

    /* 2. 设置GPIO的浮空输入 PA15，PB3 CNF=01 MODE=00*/
    GPIOB->CRH |= GPIO_CRH_CNF15_0;
    GPIOB->CRH &= ~(GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15);
    GPIOB->CRL |= GPIO_CRL_CNF3_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF3_1 | GPIO_CRL_MODE3);


    /* 3. 定时器配置 */
    /*PWM输出频率 = 72M / PSC / ARR ;*/
    /* 3.1 预分频器的配置 */
    TIM2->PSC = 1 - 1;
    /* 3.2 自动重装载寄存器的配置 */
    TIM2->ARR = 65536 - 1;
    
    /*编码器模式*/
    /*配置输入通道映射*/
    TIM2->CCMR1 &= ~ TIM_CCMR1_CC1S_1;
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;
    TIM2->CCMR1 &= ~ TIM_CCMR1_CC2S_1;
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_0;
    /*配置不反相*/
    TIM2->CCER &= ~TIM_CCER_CC1P;
    TIM2->CCER &= ~TIM_CCER_CC2P;
    /*编码器模式3，sms=011*/
    TIM2->SMCR |= TIM_SMCR_SMS;
    TIM2->SMCR &= ~TIM_SMCR_SMS_2;

    /*启动定时器*/
    TIM2->CR1 |= TIM_CR1_CEN;
}

//定时器3编码器模式初始化，CH1,CH2
void Dri_TIM3_Init(void)
{
    /* 1.  开启时钟*/
    /* 1.1 定时器4的时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    /* 1.2 GPIO的时钟 PA,PB,AFIO时钟 */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN);

    /*GPIO重映射*/
    /*关闭JTAG功能，保留SWD开启SWJ_CFG=010*/
    AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;

    /*重映射*/
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;

    /* 2. 设置GPIO的浮空输入 PA15，PB3 CNF=01 MODE=00*/
    GPIOB->CRL |= GPIO_CRL_CNF4_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4);
    GPIOB->CRL |= GPIO_CRL_CNF5_0;
    GPIOB->CRL &= ~(GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5);


    /* 3. 定时器配置 */
    /*PWM输出频率 = 72M / PSC / ARR ;*/
    /* 3.1 预分频器的配置 */
    TIM3->PSC = 1 - 1;
    /* 3.2 自动重装载寄存器的配置 */
    TIM3->ARR = 65536 - 1;
    
    /*编码器模式*/
    /*配置输入通道映射*/
    TIM3->CCMR1 &= ~ TIM_CCMR1_CC1S_1;
    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;
    TIM3->CCMR1 &= ~ TIM_CCMR1_CC2S_1;
    TIM3->CCMR1 |= TIM_CCMR1_CC2S_0;
    /*配置不反相*/
    TIM3->CCER &= ~TIM_CCER_CC1P;
    TIM3->CCER &= ~TIM_CCER_CC2P;
    /*编码器模式3，sms=011*/
    TIM3->SMCR |= TIM_SMCR_SMS;
    TIM3->SMCR &= ~TIM_SMCR_SMS_2;

    /*启动定时器*/
    TIM3->CR1 |= TIM_CR1_CEN;
}
