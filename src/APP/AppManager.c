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
#include "common.h"

/* CONSTANTS MACROS */
 
/* TYPES */
 
/* PRIVATE VARIABLES */
static AppManager_stateMachine *appStateMachine = NULL;
static AppManager_appState currentState = AppManager_APPSTATUS_INIT;
static bool buttonClicked = false;

/* PRIVATE FUNCTION PROTOTYPES */

/*static void AppManager_onEnterInit(void);
static void AppManager_onEnterNormal(void);
static void AppManager_onEnterBtnInterrupt(void);*/

static void AppManager_modeNormal(void);
static void AppManager_modeBlink(void);
static void AppManager_modeTemperature(void);
static void AppManager_modeBlinkTemp(void);
static void AppManager_modeSleep(void);

/* PRIVATE FUNCTION DEFINITIONS */

/*static void AppManager_onEnterInit(void)
{
  // TODO
}

static void AppManager_onEnterNormal(void)
{
  // TODO
}

static void AppManager_onEnterBtnInterrupt(void)
{
  // TODO
}*/

/* PUBLIC FUNCTION DEFINITIONS */
AppManager_status AppManager_initialize(void)
{
  /*if (pStateMachine == NULL) return AppManager_eSTATUS_ptrERROR;
 
  pStateMachine->currentState = AppManager_APPSTATUS_INIT;
  appStateMachine = pStateMachine;

  AppManager_onEnterInit();*/
  currentState = AppManager_APPSTATUS_NORMAL;
  return AppManager_eSTATUS_OK;
}
/*
AppManager_appState AppManager_getCurrentState(AppManager_stateMachine *pStateMachine)
{
  if (pStateMachine == NULL) return AppManager_APPSTATUS_ERROR;
  return pStateMachine->currentState;
}

AppManager_status AppManager_changeState(AppManager_stateMachine *pStateMachine, AppManager_appState newState)
{
  if (pStateMachine == NULL) return AppManager_eSTATUS_ptrERROR;

  pStateMachine->currentState = newState;
  appStateMachine = pStateMachine;

  switch (newState)
  {
    case AppManager_APPSTATUS_INIT:
      AppManager_onEnterInit();
      break;
    case AppManager_APPSTATUS_NORMAL:
      AppManager_onEnterNormal();
      break;
    case AppManager_APPSTATUS_BTNINTERRUPT:
      AppManager_onEnterBtnInterrupt();
      break;
    default:
      break;
  }

  return newState;
}*/

/* GPIO callback triggered by ISR */
void AppManager_btnAppCallBack(void)
{
  //AppManager_changeState(&appStateMachine, AppManager_APPSTATUS_BTNINTERRUPT);
  buttonClicked = true;
}

void AppManager_run(void)
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
}