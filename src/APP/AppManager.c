/**
 ***********************************************************************************************************************
 * Company: Esme Sudria
 * Project: Projet Esme
 *
 ***********************************************************************************************************************
 * @file      AppManager.c
 *
 * @author    Nicolas MARTI
 * @date      27/11/2025
 *
 * @version   0.1.3
 *
 * @brief     AppManager, state machine that oversee the current running process
 * @details   This module should be initialized with AppManager_initialize()
 *            Then it can you should run it with AppManager_run()
 *            /!\ AppManager_run() should be run only once, as it contain 
 *            an infinite event loop.
 *
 * @remark    Coding Language: C
 *
 * @copyright Copyright (c) 2025 This software is used for education proposal
 *
 ***********************************************************************************************************************
 */

/**********************************************************************************************************************/
/* INCLUDE FILES                                                                                                      */
/**********************************************************************************************************************/
#include "AppManager.h"
#include <stdio.h>
#include <stdlib.h> // for abs()
#include "Common.h"
#include "GPIO.h"
#include "CLOCK.h"
#include "MCP9700.h" // Driver for temperature
#include "SERP.h"

/**********************************************************************************************************************/
/* CONSTANTS, MACROS                                                                                                  */
/**********************************************************************************************************************/
#define APPMANAGER_VERSION "1.3"


/**********************************************************************************************************************/
/* TYPES                                                                                                              */
/**********************************************************************************************************************/
/**
 * @brief type for the state of AppManager
 * @details New true states should be added before AppManager_APPSTATUS_SLEEP
 */
typedef enum AppManager_appState
{
  AppManager_APPSTATUS_INIT = 0,
  AppManager_APPSTATUS_NORMAL,
  AppManager_APPSTATUS_BLINK,
  AppManager_APPSTATUS_TEMPERATURE,
  AppManager_APPSTATUS_BLINKTEMP,
  AppManager_APPSTATUS_SLEEP, // last true state type before error types
  AppManager_APPSTATUS_BTNINTERRUPT,
  AppManager_APPSTATUS_ERROR, // Default value for errors
}AppManager_appState;
 


/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/
/**
 * @TODO delete that later
 */
//static AppManager_stateMachine *appStateMachine = NULL;

/*--------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief global state of the AppManager
 */
static AppManager_appState currentState = AppManager_APPSTATUS_INIT;

/*--------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief register to remember if a button has been clicked
 */
static volatile bool buttonClicked = false;


/**********************************************************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES                                                                                       */
/**********************************************************************************************************************/
/**
 * @brief Callback function registered to the interrupt module and called when an interruption triggers to check if this
 *        interruption came from the timer TIM0
 * @details See "PIC18F47Q10 - Datasheet", P.194, 14.9"
 */
void AppManager_btnAppCallBack(void);
static void AppManager_modeNormal(void);
static void AppManager_modeBlink(void);
static void AppManager_modeTemperature(void);
static void AppManager_modeBlinkTemp(void);
static void AppManager_modeSleep(void);

/* Fonctions */

static void AppManager_modeNormal(void)
{
  GPIO_setGpioHigh(); 
  CMN_systemPrintf("State: NORMAL\r\n");
  __delay_ms(500);
}

static void AppManager_modeBlink(void)
{
  static bool led = false;
  led ? GPIO_setGpioHigh() : GPIO_setGpioLow();
  led = !led;
  CMN_systemPrintf("State: BLINK\r\n");
  __delay_ms(500);
}

static void AppManager_modeTemperature(void)
{
  GPIO_setGpioHigh(); //set the led on, don't blink it
  //CMN_systemPrintf("AppManager mode Temperature \r\n");
  // Lecture capteur
  int16_t temp = MCP9700_GetDeciCelsius();
  
  if(temp == -9999) {
      CMN_systemPrintf("Temp: ERROR (ADC Timeout)\r\n");
  } else {
      // Affichage avec virgule (division enti�re / 10 et modulo % 10)
      CMN_systemPrintf("Temp: %d.%d C\r\n", (temp / 10), abs(temp % 10));
  }
  __delay_ms(500);
}

static void AppManager_modeBlinkTemp(void)
{
  static bool led = false;
  led ? GPIO_setGpioHigh() : GPIO_setGpioLow();
  led = !led;
  
  int16_t temp = MCP9700_GetDeciCelsius();
  
  if(temp == -9999) {
      CMN_systemPrintf("Blink & Temp: Error\r\n");
  } else {
      CMN_systemPrintf("Blink & Temp: %d.%d C\r\n", (temp / 10), abs(temp % 10));
  }
  __delay_ms(500);
}

static void AppManager_modeSleep(void)
{
  GPIO_setGpioLow(); //set the led on, don't blink it
  CMN_systemPrintf("AppManager mode Sleep \r\n");
  CMN_systemPrintf("Entering Sleep mode ...\nPress button to awaken \r\n");
  SLEEP();//wait until button pressed or other interrupt 
  __delay_ms(500);
}

void AppManager_btnAppCallBack(void)
{
  buttonClicked = true;
  uint8_t myMsg[] = "Hello World";
  SERP_enuSendMessage(SERP_ID_TX_CUSTOM_MSG, myMsg, 11); 
}

/* Publiques */

AppManager_status AppManager_initialise(void)
{
  AppManager_status status = AppManager_eSTATUS_OK;
  CMN_systemPrintf("Init AppManager version : %s\r\n", APPMANAGER_VERSION);
  GPIO_status ret = GPIO_registerBtnCallback(AppManager_btnAppCallBack);
  if (ret != GPIO_OK)
  {
    if ((ret == GPIO_CALLBACK_INIT_ERROR)||(ret == GPIO_CALLBACK_REGISTER_ERROR))
    {
        status = AppManager_eSTATUS_ptrERROR;
    }
    status = AppManager_eSTATUS_NOK;
  }
  return status;
}

AppManager_status AppManager_run(void)
{
  currentState = AppManager_APPSTATUS_NORMAL;
  CMN_systemPrintf("--- SYSTEM START ---\r\n");
  
  while (true)
  {
    if (buttonClicked)
    {
      buttonClicked = false;
      currentState++;
      if (currentState > AppManager_APPSTATUS_SLEEP)
      {
        currentState = AppManager_APPSTATUS_NORMAL;
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
      default:
        currentState = AppManager_APPSTATUS_NORMAL;
        break;
    }
  }
  return AppManager_unexpected_end;
}