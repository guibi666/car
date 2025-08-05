#ifndef __DRI_SPI_H
#define __DRI_SPI_H

#include "stm32f10x.h"

#define CS_HIGH (GPIOA->ODR |= GPIO_ODR_ODR4)
#define CS_LOW (GPIOA->ODR &= ~GPIO_ODR_ODR4)

#define SCK_HIGH (GPIOA->ODR |= GPIO_ODR_ODR5)
#define SCK_LOW (GPIOA->ODR &= ~GPIO_ODR_ODR5)

#define MOSI_HIGH (GPIOA->ODR |= GPIO_ODR_ODR7)
#define MOSI_LOW (GPIOA->ODR &= ~GPIO_ODR_ODR7)


void Dri_SPI_Init(void);

void Dri_SPI_WriteByte(uint8_t byte);

#endif
