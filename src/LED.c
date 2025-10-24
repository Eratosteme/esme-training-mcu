#include "LED.h"
#include <xc.h>

LED_tenuStatus LED_Init()
{
    if (4 != LED_PIN) return LED_eSTATUS_NO_OK; //Led on pin 4
    ANSELAbits.ANSELA4 = 0;
    TRISAbits.TRISA4 = 0;
    PORTAbits.RA4 = 1;

    return LED_eSTATUS_OK;
}

LED_tenuStatus LED_Pilot(uint8_t state)
{
    if (4 != LED_PIN) return LED_eSTATUS_NO_OK; //Led on pin 4

    if (state)
        PORTAbits.RA4 = 0;  
    else
        PORTAbits.RA4 = 1; 

    return LED_eSTATUS_OK;
}