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

/* CONSTANTS MACROS */
 
/* TYPES */
 
/* PRIVATE VARIABLES */
static AppManager_stateMachine *appStateMachine = NULL;

/* PRIVATE FUNCTION PROTOTYPES */
static void AppManager_onEnterInit(void);
static void AppManager_onEnterNormal(void);
static void AppManager_onEnterBtnInterrupt(void);

/* PRIVATE FUNCTION DEFINITIONS */
static void AppManager_onEnterInit(void)
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
}

/* PUBLIC FUNCTION DEFINITIONS */
AppManager_status AppManager_initialize(AppManager_stateMachine *pStateMachine)
{
  if (pStateMachine == NULL) return AppManager_eSTATUS_ptrERROR;

  pStateMachine->currentState = AppManager_APPSTATUS_INIT;
  appStateMachine = pStateMachine;

  AppManager_onEnterInit();
  return AppManager_eSTATUS_OK;
}

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
}

/* GPIO callback triggered by ISR */
void AppManager_btnAppCallBack(void)
{
  AppManager_changeState(&appStateMachine, AppManager_APPSTATUS_BTNINTERRUPT);
}