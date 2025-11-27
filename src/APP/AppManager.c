/* 
 * File:     AppManager.c
 * Author:   Esme Sudria
 */

#include "AppManager.h"
#include <stdio.h>
#include <stdlib.h> // pour abs()
#include "Common.h"
#include "GPIO.h"
#include "CLOCK.h"
#include "MCP9700.h" // Inclusion du driver
#include "SERP.h"

/* CONSTANTS MACROS */
#define APPMANAGER_VERSION "1.3"

/* TYPES */
    
typedef enum AppManager_appState
{
  AppManager_APPSTATUS_INIT = 0,
  AppManager_APPSTATUS_NORMAL,
  AppManager_APPSTATUS_BLINK,
  AppManager_APPSTATUS_TEMPERATURE,
  AppManager_APPSTATUS_BLINKTEMP,
  AppManager_APPSTATUS_SLEEP,
  AppManager_APPSTATUS_BTNINTERRUPT,
  AppManager_APPSTATUS_ERROR, // Default value for errors
}AppManager_appState;
 
/* PRIVATE VARIABLES */
//static AppManager_stateMachine *appStateMachine = NULL;
static AppManager_appState currentState = AppManager_APPSTATUS_INIT;
static volatile bool buttonClicked = false;

/* PRIVATE FUNCTION PROTOTYPES */
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