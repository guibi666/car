#include "Dri_SPI.h"


/**
 * @description: 初始化SPI
 */
void Dri_SPI_Init(void)
{
    /* 1. 开启GPIO时钟 PA */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* 2. 初始化引脚：CS(PA4) CLK(PA5) MOSI(PA7) 使用通用推挽输出 MODE=11 CNF=00 */
    GPIOA->CRL |= (GPIO_CRL_MODE4|GPIO_CRL_MODE5 | GPIO_CRL_MODE7);
    GPIOA->CRL &= ~(GPIO_CRL_CNF4|GPIO_CRL_CNF5 | GPIO_CRL_CNF7);

    /* 3.spi的模式0  sck空闲状态是 0 */
    // SCK_LOW(); 

    /* 4. 片选默认不选中 */
    CS_HIGH;
}

/**
 * @description: 使用SPI发送一个字节的数据
 * @param {uint8_t} byte  要发送的字节数据
 * @return {void} 
 */
void Dri_SPI_WriteByte(uint8_t byte)
{
    /* 1.选中 */
    CS_LOW;

    for (uint8_t i = 0; i < 8; i++)
    {
        SCK_LOW;
        /* 2. 把数据输出到MOSI. 先从高位发送. */
        if (byte & 0x80)
        {
            MOSI_HIGH;
        }
        else
        {
            MOSI_LOW;
        }
        /* 3. 拉高时钟 (第一个跳变)*/
        SCK_HIGH;
        /* 4. 移位 */
        byte <<= 1;
    }
    /* 5 不选中 */
    CS_HIGH;
}
