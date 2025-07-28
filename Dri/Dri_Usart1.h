#ifndef __DRI_USART1_H
#define _DRI_USART1_H

#include "stm32f10x.h"
#include "stdio.h"

void Dri_USART1_Init(void);

void Dri_USART1_SendChar(uint8_t byte);

#endif


