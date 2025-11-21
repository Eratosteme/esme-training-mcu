/* 
 * *****************************************************************************
 * Company: ESME Sudria
 * Projet: Projet ESME
 * 
 * *****************************************************************************
 * @file:     AppManager.c
 * 
 * @author:   Ephistos
 * @date      31 octobre 2025, 03:02
 * @version   0.0.0
 * @copyright Copyright (c) 2025 This software is used for education proposal
 */


/* INCLUDE FILES */
#include "AppManager.h"
#include <stdio.h>
#include "Common.h"
#include "GPIO.h"
#include "CLOCK.h"

/* CONSTANTS MACROS */
 
/* TYPES */
 
/* PRIVATE VARIABLES */
//static AppManager_stateMachine *appStateMachine = NULL;
static AppManager_appState currentState = AppManager_APPSTATUS_INIT;
static bool buttonClicked = false;

/* PRIVATE FUNCTION PROTOTYPES */
static void AppManager_modeNormal(void);
static void AppManager_modeBlink(void);
static void AppManager_modeTemperature(void);
static void AppManager_modeBlinkTemp(void);
static void AppManager_modeSleep(void);

/* PRIVATE FUNCTION DEFINITIONS */


static void AppManager_modeNormal(void)
{
  GPIO_setGpioHigh(); //set the led on, don't blink it
  CMN_systemPrintf("AppManager mode Normal \r\n");
  __delay_ms(500);
}

static void AppManager_modeBlink(void)
{
  //LED blinking logic
  static bool AppManager_LED_state = false;
  AppManager_LED_state ? GPIO_setGpioHigh() : GPIO_setGpioLow();
  AppManager_LED_state = !AppManager_LED_state;
  
  CMN_systemPrintf("AppManager mode Blink \r\n");
  __delay_ms(500);
}

static void AppManager_modeTemperature(void)
{
  CMN_systemPrintf("AppManager mode Temperature \r\n");
  __delay_ms(500);
}

static void AppManager_modeBlinkTemp(void)
{
  //LED blinking logic
  static bool AppManager_LED_state = false;
  AppManager_LED_state ? GPIO_setGpioHigh() : GPIO_setGpioLow();
  AppManager_LED_state = !AppManager_LED_state;
  
  CMN_systemPrintf("AppManager mode Blink and Temperature \r\n");
  __delay_ms(500);
}

static void AppManager_modeSleep(void)
{
  CMN_systemPrintf("AppManager mode Sleep \r\n");
  CMN_systemPrintf("Entering Sleep mode ...\nPress button to awaken \r\n");
  SLEEP();//wait until button pressed or other interrupt 
  __delay_ms(500);
}


/* PUBLIC FUNCTION DEFINITIONS */

/* GPIO callback triggered by ISR */
void AppManager_btnAppCallBack(void)
{
  //AppManager_changeState(&appStateMachine, AppManager_APPSTATUS_BTNINTERRUPT);
  buttonClicked = true;
}

AppManager_status AppManager_run(void)
{
  currentState = AppManager_APPSTATUS_NORMAL;
  CMN_systemPrintf("ButtonCallback ! \r\n");
  
  // Main application loop
  while (true)
  {
    if (buttonClicked)
    {
      if (currentState <= AppManager_APPSTATUS_SLEEP)
      {
        currentState += 1;
        buttonClicked = false;
        if (currentState == AppManager_APPSTATUS_SLEEP + 1)
        {
          currentState = AppManager_APPSTATUS_NORMAL;
        }
      }
    }    
        
    switch (currentState)
    {
      case AppManager_APPSTATUS_INIT:
        currentState = AppManager_APPSTATUS_NORMAL;
        break;
      case AppManager_APPSTATUS_NORMAL:
        AppManager_modeNormal();
        break;
      case AppManager_APPSTATUS_BLINK:
        AppManager_modeBlink();
        break;
      case AppManager_APPSTATUS_TEMPERATURE:
        AppManager_modeTemperature();
        break;
      case AppManager_APPSTATUS_BLINKTEMP:
        AppManager_modeBlinkTemp();
        break;
      case AppManager_APPSTATUS_SLEEP:
        AppManager_modeSleep();
        break;
      case AppManager_APPSTATUS_BTNINTERRUPT:
        currentState = AppManager_APPSTATUS_NORMAL;
        break;
      case AppManager_APPSTATUS_ERROR:
        currentState = AppManager_APPSTATUS_NORMAL;
        break;
      default:
        currentState = AppManager_APPSTATUS_NORMAL;
        break;
    }
  }
  return AppManager_unexpected_end;
}
