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
#include "SERP.h" 
#include <stdio.h>

/* CONSTANTS MACROS */
 
/* TYPES */
 
/* PRIVATE VARIABLES */
static AppManager_stateMachine *appStateMachine = NULL;

/* PRIVATE FUNCTION PROTOTYPES */
/* PRIVATE FUNCTION PROTOTYPES */
static void AppManager_onEnterInit(void);
static void AppManager_onEnterNormal(void);
static void AppManager_onEnterBtnInterrupt(void);
static void AppManager_serpMsgReceived(uint8_t msgId, uint16_t length, const uint8_t *data);

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
    uint8_t msg[] = "Hello World";
    SERP_enuSendMsg(SERP_CUSTOM_MSG_ID, msg, sizeof(msg) - 1);
}

/* gestion des messages SERP */
static void AppManager_serpMsgReceived(uint8_t msgId, uint16_t length, const uint8_t *data)
{
    switch (msgId)
    {
        case SERP_START_MEASURE_MSG_ID:
            AppManager_changeState(appStateMachine, AppManager_APPSTATUS_NORMAL);
            break;

        case SERP_STOP_MEASURE_MSG_ID:
            AppManager_changeState(appStateMachine, AppManager_APPSTATUS_INIT);
            break;

        default:
            break;
    }
}
/* PUBLIC FUNCTION DEFINITIONS */
AppManager_status AppManager_initialize(AppManager_stateMachine *pStateMachine)
{
  if (pStateMachine == NULL) return AppManager_eSTATUS_ptrERROR;
 
  pStateMachine->currentState = AppManager_APPSTATUS_INIT;
  appStateMachine = pStateMachine;

  SERP_enuRegisterAppCbk(AppManager_serpMsgReceived);
  
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

  //return newState;
  return AppManager_eSTATUS_OK;
}

/* GPIO callback triggered by ISR */
void AppManager_btnAppCallBack(void)
{
    AppManager_changeState(appStateMachine, AppManager_APPSTATUS_BTNINTERRUPT);
}