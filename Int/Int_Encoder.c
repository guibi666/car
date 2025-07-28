#include "Int_Encoder.h"

/*初始化*/
void Int_Encoder_Init(void)
{
    Dri_TIM2_Init();
    Dri_TIM3_Init();
}

/*读取编码器计数值*/
int16_t Int_Encoder_ReadCount(uint8_t timx)
{
    int encoder_value = 0;
    switch (timx)
    {
    case 2:
        /*读取定时器计数值*/
        encoder_value = (uint16_t)TIM2->CNT;
        TIM2->CNT = 0;
        break;
    
    case 3:
    /*读取定时器计数值*/
    encoder_value = (uint16_t)TIM3->CNT;
    encoder_value = - encoder_value;
    TIM3->CNT = 0;
    break;

    default:
        break;
    }
    return encoder_value;
}
