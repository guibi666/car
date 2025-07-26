#include "main.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Int_TB6612.h"

int main(void) 
{

    Int_TB6612_Init();
    Int_TB6612_SetPWM(50,50);

    while (1)
    {
        /* code */
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

