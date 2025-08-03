#include "main.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Int_TB6612.h"
#include "Int_Encoder.h"
#include "Dri_Usart1.h"
#include "Int_MPU6050.h"
#include "App_Car.h"

void For_Delay_ms(uint32_t ms)
{
    uint32_t delay = ms * 7200 /9;
    do
    {
        __NOP();
    } while (delay --);
}


int main(void) 
{

    Int_TB6612_Init();
    Int_Encoder_Init();
    Dri_USART1_Init();
    Int_MPU6050_Init();

    while (1)
    {
        App_Car_GetAngle();
        For_Delay_ms(10);
    }
    
}

extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
    }
}

