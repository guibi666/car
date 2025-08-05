#include "Dri_ADC.h"

void Dri_ADC1_Init(void)
{
    /* 1. 时钟配置 */
    /* 1.1 adc时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    /* 分频，adc时钟频率不高于14M， 72M作6分频 = 12M ，adcpre=10*/
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    /* 1.2 gpioA的时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. gpio工作模式: PA1 模拟输入  CNF=00 MODE=00 */
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);

    /* 2. ADC相关配置 */
    /* 2.1 禁用扫描模式. 只有一个通道不用扫描 */
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    /* 2.2 采集电池电压这种adc不重要，禁用连续转换模式 CR2=CONT 0*/
    ADC1->CR2 &= ~ADC_CR2_CONT;
    /* 2.3 数据对齐方式: 右对齐 左对齐 */
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    /* 2.4 设置采样时间 ADC_SMPR1 ，拉到最大就行 111=239.5周期*/
    ADC1->SMPR2 |= ADC_SMPR2_SMP1; //TODO
    /* 2.6 通道组的配置 */
    /* 2.6.1 配置几个通道需要转换 */
    ADC1->SQR1 &= ~ADC_SQR1_L;
    /* 2.6.1 把通道号配置到组里面.  */
    ADC1->SQR3 &= ~ADC_SQR3_SQ1; /* 先把5位清零 */
    ADC1->SQR3 |= 1 << 0;       /* 设置最后5位为通道1 */
    /* 2.7 选择软件触发 */
    ADC1->CR2 |= ADC_CR2_EXTTRIG; /* 启动规则组的外部事件触发 */
    ADC1->CR2 |= ADC_CR2_EXTSEL;  /* 外部事件 选择使用软件触发ADC */

    /* 1. 上电: 把ADC从休眠模式唤醒 */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 2. 执行校准 */
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;

    /* 3. ADON = 1, 开始转换 0>1 从休眠模式唤醒 1->1 开始 */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 4. 使用软件开始转换规则通道 */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 5. 等待首次转换完成 */
    while((ADC1->SR & ADC_SR_EOC) == 0);

}


double Dri_ADC1_ReadV(void)
{
    /* 由于关闭了连续转换，每次读取前都要手动启动一下 */
    /* 1. ADON 1->1 开始 */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 2. 使用软件开始转换规则通道 */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 3. 等待转换完成 */
    while((ADC1->SR & ADC_SR_EOC) == 0);

    // 4、12位的ADC 范围 [0, 4095] 因为电路图中，做了分压，测试到的电压=电池电压/4
    return (ADC1->DR * 3.3 / 4095) * 4;
}
