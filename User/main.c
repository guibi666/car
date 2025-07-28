#include "main.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Int_TB6612.h"
#include "Int_Encoder.h"
#include "Dri_Usart1.h"

void For_Delay_ms(uint32_t ms)
{
    uint32_t delay = ms * 72000 /9;
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

    while (1)
    {
       printf("tim2 cnt=%d\r\n",Int_Encoder_ReadCount(2));
       printf("tim3 cnt=%d\r\n",Int_Encoder_ReadCount(3));
       For_Delay_ms(1000);
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

