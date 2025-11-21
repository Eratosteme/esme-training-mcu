/* 
 * *****************************************************************************
 * Company: ESME Sudria
 * Projet: Projet ESME
 * 
 * *****************************************************************************
 * @file:     AppManager.h
 * 
 * @author:   Ephistos
 * @date      31 octobre 2025, 03:02
 * @version   0.0.0
 * @copyright Copyright (c) 2025 This software is used for education proposal
 */

#ifndef APPMANAGER_H
#define	APPMANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif

/* INCLUDE FILES */
 
/* CONSTANTS MACROS */
 
/* TYPES */
typedef enum AppManager_status
{
  AppManager_eSTATUS_OK =0,
  AppManager_eSTATUS_NOK,
  AppManager_eSTATUS_ptrERROR,
}AppManager_status; 
    
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

typedef struct AppManager_stateMachine
{
  AppManager_appState currentState;
}AppManager_stateMachine;

/* PUBLIC FUNCTION PROTOTYPES */
AppManager_status AppManager_initialize(AppManager_stateMachine *pStateMachine);
void AppManager_btnAppCallBack(void);
AppManager_appState AppManager_getCurrentState(AppManager_stateMachine *pStateMachine);
AppManager_status AppManager_changeState(AppManager_stateMachine *pStateMachine, AppManager_appState newState);
AppManager_run(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPMANAGER_H */

