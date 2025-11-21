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
#include "MCP9700.h"   // Driver Capteur
#include "AppManager.h"

void main(void)
{
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

  // Add your initialization function here for the driver modules...

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