

#include "stdtypes.h"
#include "atmega32.h"
#include "bitmath.h"
#include "DIO/DIO.h"
#include "TIMER0/timer0.h"
#include "EXTI/EXTI.h"

#include "LED/led.h"
#include "LED/led_cfg.h"

int Pedestrian_Flag;
void IRQ_ISR()
{
    // flag
    Pedestrian_Flag = 1;
}

void APP_Init()
{
    LED_Init();
    TIMER0_Init();
    TIMER0_Start();
    EXTI_Configs_t IRQ0 = {EXTI_0, RISINING_EDGE, IRQ_ISR};
    EXTI_Init(&IRQ0);
}

void main()
{
    LED_ON(LED_0);
    LED_OFF(LED_2);
    LED_OFF(LED_1);

    T0_delay_ms(5000);
    LED_ON(LED_1);
    LED_OFF(LED_0);
    LED_OFF(LED_2);

    T0_delay_ms(5000);
    LED_OFF(LED_2);
    LED_OFF(LED_0);
    LED_OFF(LED_1);
    T0_delay_ms(5000);

    if (Pedestrian_Flag == 0)
    {
        Pedestrian_Flag = 1;
        LED_oFF(LED_0);
        LED_OFF(LED_2);
        LED_OFF(LED_1);
        T0_delay_ms(5000);
    }
}
