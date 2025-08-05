#include "main.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Int_TB6612.h"
#include "Int_Encoder.h"
#include "Dri_Usart1.h"
#include "Int_MPU6050.h"
#include "App_Car.h"
#include "Dri_ADC.h"
#include "oled.h"

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

    Dri_USART1_Init();
    printf("1");
    OLED_Init();
    printf("2");
	OLED_Clear();
    printf("3");
    OLED_ShowString(0,10,"hello",16,1);
    printf("4");
    OLED_Refresh();
    printf("5");

    while (1)
    {
       
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

