/**
 * @file      main.c
 * @brief     Main program
 */

#include <stdio.h>
#include "Common.h"
#include "ISR.h"
#include "CLOCK.h"
#include "ADC.h"       // Driver Hardware
#include "TIMER.h"
#include "EUSART.h"
#include "I2CM.h"
#include "GPIO.h"
#include "LCD.h"
<<<<<<< HEAD
#include "MCP9700.h"   // Driver Capteur
=======
#include "SERP.h"

// Add the required includes for the driver modules here...

/*********************************/
/* APPLICATION INCLUDES          */
/*********************************/
// Add the required includes for the application modules here...
>>>>>>> SERP
#include "AppManager.h"
#include "SERP.h"

void main(void)
{
<<<<<<< HEAD
  #pragma config WDTE = OFF
  #pragma config LVP = ON

  ISR_GlobalInterruptEnable();
  ISR_PeripheralInterruptEnable();

  CMN_vidInitialize();

  /* HARDWARE */
  CLOCK_vidInitialize();
  EUSART_vidInitialize();
  
  // INITIALISATION ADC (Configure la broche d�finie dans ADC_cfg.h)
  ADC_vidInitialize(); 
  
  TIM0_vidInitialize();
  I2CM_vidInitalize();
  GPIO_initialize();

  /* DRIVERS */
  LCD_vidInitialize();
  MCP9700_Init();
  SERP_vidInitialize();
=======
    #pragma config WDTE = OFF
    #pragma config LVP = ON

    ISR_GlobalInterruptEnable();
    ISR_PeripheralInterruptEnable();

    CMN_vidInitialize();

    /*********************************/
    /* HARDWARE INITIALIZATIONS      */
    /*********************************/
    CLOCK_vidInitialize();
    EUSART_vidInitialize();      // UART d?abord
    ADC_vidInitialize();
    TIM0_vidInitialize();
    I2CM_vidInitalize();
    GPIO_initialize();

    /*********************************/
    /* DRIVER INITIALIZATIONS        */
    /*********************************/
    LCD_vidInitialize();
    SERP_enuInit();              // Puis SERP (obligatoire)

    /*********************************/
    /* APPLICATION INITIALIZATIONS   */
    /*********************************/
    AppManager_stateMachine main_AppManager_stateMachine;
    AppManager_status ret;

    do {
        ret = AppManager_initialize(&main_AppManager_stateMachine);
        if(ret == AppManager_eSTATUS_ptrERROR)
        {
            CMN_systemPrintf("not init yet \r\n");
        }
    } while(ret != AppManager_eSTATUS_OK);
>>>>>>> SERP

    CMN_systemPrintf("AppManager Inited \r\n");

<<<<<<< HEAD
  /*********************************/
  /* APPLICATION INITIALIZATIONS   */
  /*********************************/
  // Add your initialization function here for the application modules...
  AppManager_initialise();
  
  // End of the initialization:
  CMN_vidEndInit();
  
  // Boucle infinie
  AppManager_run();
  
  CMN_abortAll();
}
=======
    GPIO_registerBtnCallback(AppManager_btnAppCallBack);

    CMN_vidEndInit();

    static uint8_t main_LED_state = 0;

    while(true)
    {
        __delay_ms(500);

        CMN_systemPrintf("Hello World ! \r\n");

        main_printf(&main_AppManager_stateMachine);

        main_LED_state ? GPIO_setGpioHigh() : GPIO_setGpioLow();
        main_LED_state = !main_LED_state;
    }

    CMN_abortAll();
}
/*--------------------------------------------------------------------------------------------------------------------*/
>>>>>>> SERP
