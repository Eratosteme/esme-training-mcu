/**
 ***********************************************************************************************************************
 * Company: Esme Sudria
 * Project: Projet Esme
 *
 ***********************************************************************************************************************
 * @file      main.c
 *
 * @author    Jean DEBAINS
 * @date      14/06/2023
 *
 * @version   0.0.0
 *
 * @brief     Main program entry point
 *
 * @remark    Coding Language: C
 *
 * @copyright Copyright (c) 2024 This software is used for education proposal
 *
 ***********************************************************************************************************************
 */



/**********************************************************************************************************************/
/* INCLUDE FILES                                                                                                      */
/**********************************************************************************************************************/
#include <stdio.h>
#include "Common.h"

/*********************************/
/* HARDWARE INCLUDES             */
/*********************************/
#include "ISR.h"
#include "CLOCK.h"
#include "ADC.h"
#include "TIMER.h"
#include "EUSART.h"
#include "I2CM.h"
//#include "LED.h"
#include "GPIO.h"

// Add the required includes for the hardware modules here...

/*********************************/
/* DRIVER INCLUDES               */
/*********************************/
#include "LCD.h"

// Add the required includes for the driver modules here...

/*********************************/
/* APPLICATION INCLUDES          */
/*********************************/
// Add the required includes for the application modules here...
#include "AppManager.h"

/**********************************************************************************************************************/
/* CONSTANTS, MACROS                                                                                                  */
/**********************************************************************************************************************/



/**********************************************************************************************************************/
/* TYPES                                                                                                              */
/**********************************************************************************************************************/



/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/



/**********************************************************************************************************************/
/* PRIVATE FUNCTIONS PROTOTYPES                                                                                       */
/**********************************************************************************************************************/
void main_printf(AppManager_stateMachine *pStateMachine);


/**********************************************************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                                                                       */
/**********************************************************************************************************************/
void main_printf(AppManager_stateMachine *pStateMachine)
{
  switch (pStateMachine->currentState)
  {
    case AppManager_APPSTATUS_NORMAL:
      CMN_systemPrintf("State Normal \r\n");
      break;
    case AppManager_APPSTATUS_INIT:
      CMN_systemPrintf("State INIT \r\n");
      break;
    case AppManager_APPSTATUS_BTNINTERRUPT:
      CMN_systemPrintf("State BtnInterupt \r\n");
      break;
    case AppManager_APPSTATUS_ERROR:
      CMN_systemPrintf("State error :/ \r\n");
      break;
    default:
      CMN_systemPrintf("Very Weird, no state ... \r\n");
      break;
  }
}



/**********************************************************************************************************************/
/* START FUNCTION                                                                                                     */
/**********************************************************************************************************************/
void main(void)
{
  // WDT operating mode ? WDT Disabled:
  #pragma config WDTE = OFF

  // Low-voltage programming enabled:
  #pragma config LVP = ON

  // Enable the Global Interrupts
  ISR_GlobalInterruptEnable();

  // Enable the Peripheral Interrupts:
  ISR_PeripheralInterruptEnable();

  // Begin of the Init:
  CMN_vidInitialize();

  /*********************************/
  /* HARDWARE INITIALIZATIONS      */
  /*********************************/
  CLOCK_vidInitialize();
  EUSART_vidInitialize();
  ADC_vidInitialize();
  TIM0_vidInitialize();
  I2CM_vidInitalize();

  // Add your initialization function here for the hardware modules...
  GPIO_initialize();
  /*********************************/
  /* DRIVER INITIALIZATIONS        */
  /*********************************/
  LCD_vidInitialize();

  // Add your initialization function here for the driver modules...

  /*********************************/
  /* APPLICATION INITIALIZATIONS   */
  /*********************************/
  // Add your initialization function here for the application modules...
  AppManager_initialize();
  
  // CALLBACK INITAIALISATION
  GPIO_registerBtnCallback(AppManager_btnAppCallBack);
  /*
  AppManager_stateMachine main_AppManager_stateMachine;
  main_AppManager_stateMachine.currentState = AppManager_APPSTATUS_INIT;
  AppManager_status ret = AppManager_eSTATUS_NOK;
  
  while (ret!=AppManager_eSTATUS_OK)
  {
    ret =AppManager_initialize(&main_AppManager_stateMachine);
    
    if(ret == AppManager_eSTATUS_ptrERROR)
    {
        CMN_systemPrintf("not init yet \r\n");
    }
  }
  
  CMN_systemPrintf("AppManager Inited \r\n");
  
  GPIO_registerBtnCallback(AppManager_btnAppCallBack);
  */
  // End of the Init:
  CMN_vidEndInit();
  
  
  // Main program loop:
  AppManager_run();
  
  /*
  static uint8_t main_LED_state = 0;
  
  
  while(true)
  {
    // Performs a delay of 0.5s:
    __delay_ms(500);
    
    // Send a "Hello World" message to the serial port:
    CMN_systemPrintf("Hello World ! \r\n");
    
    // print current state
    main_printf(&main_AppManager_stateMachine);
    
    //Blink LED 
    main_LED_state ? GPIO_setGpioHigh() : GPIO_setGpioLow();
    main_LED_state = !main_LED_state;
  }*/

  // We should never reach this code part:
  CMN_abortAll();
}


/*--------------------------------------------------------------------------------------------------------------------*/
