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

static AppManager_appState currentState = AppManager_APPSTATUS_INIT;
static volatile bool buttonClicked = false;

/* Prototypes */
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
  // Lecture capteur
  int16_t temp = MCP9700_GetDeciCelsius();
  
  if(temp == -9999) {
      CMN_systemPrintf("Temp: ERROR (ADC Timeout)\r\n");
  } else {
      // Affichage avec virgule (division entière / 10 et modulo % 10)
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
  CMN_systemPrintf("State: SLEEP (Press Btn to Wake)\r\n");
  SLEEP();
  NOP();
  __delay_ms(100);
}

/* Publiques */

void AppManager_btnAppCallBack(void)
{
  buttonClicked = true;
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