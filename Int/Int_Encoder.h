#ifndef __INT_ENCODER_H
#define __INT_ENCODER_H

#include "Dri_TIM.h"

void Int_Encoder_Init(void);

int16_t Int_Encoder_ReadCount(uint8_t timx);

#endif


