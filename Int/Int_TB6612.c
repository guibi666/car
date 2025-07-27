#include "Int_TB6612.h"

void Int_TB6612_Init(void)
{
    /*初始化定时器*/
    Dri_TIM4_Init();

    /*初始化GPIO,推挽输出*/
    GPIOB->CRH |= (GPIO_CRH_MODE12 |GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);
    GPIOB->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_CNF15);

}

void Int_TB6612_MortorA(uint8_t direct)
{
    if (direct == GO)
    {
        /*正转AIN1=0,AIN2=1*/
        AIN1_L;
        AIN2_H;

    }
    else if (direct == BACK)
    {
        /*反转AIN1=1,AIN2=0*/
        AIN1_H;
        AIN2_L;
    }
    else
    {
        /*刹车*/
        AIN1_H;
        AIN2_H;
    }
}

void Int_TB6612_MortorB(uint8_t direct)
{
    if (direct == GO)
    {
        /*正转AIN1=0,AIN2=1*/
        BIN1_L;
        BIN2_H;

    }
    else if (direct == BACK)
    {
        /*反转AIN1=1,AIN2=0*/
        BIN1_H;
        BIN2_L;
    }
    else
    {
        /*刹车*/
        BIN1_H;
        BIN2_H;
    }
}

void Int_TB6612_SetPWM(int pwma,int pwmb)
{
    if (pwma > 0)
    {
        Int_TB6612_MortorA(GO);
    }
    else if (pwma < 0)
    {
        Int_TB6612_MortorA(BACK);
        pwma = - pwma;
    }
    else
    {
        Int_TB6612_MortorA(STOP);
    }
    
    TIM4->CCR4 = pwma;


    if (pwmb > 0)
    {
        Int_TB6612_MortorB(GO);
    }
    else if (pwmb < 0)
    {
        Int_TB6612_MortorB(BACK);
        pwmb = - pwmb;
    }
    else
    {
        Int_TB6612_MortorB(STOP);
    }
    
    TIM4->CCR3 = pwmb;
}
