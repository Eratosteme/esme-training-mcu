/* 
 * File:     AppManager.h
 * Author:   Esme Sudria
 */

#ifndef APPMANAGER_H
#define	APPMANAGER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum AppManager_status
{
  AppManager_eSTATUS_OK = 0,
  AppManager_eSTATUS_NOK,
  AppManager_eSTATUS_ptrERROR,
  AppManager_unexpected_end,
} AppManager_status; 
    
typedef enum AppManager_appState
{
  AppManager_APPSTATUS_INIT = 0,
  AppManager_APPSTATUS_NORMAL,
  AppManager_APPSTATUS_BLINK,
  AppManager_APPSTATUS_TEMPERATURE, // Mode affichage temp
  AppManager_APPSTATUS_BLINKTEMP,   // Mode affichage temp + blink
  AppManager_APPSTATUS_SLEEP,
  AppManager_APPSTATUS_BTNINTERRUPT,
  AppManager_APPSTATUS_ERROR
} AppManager_appState;

void AppManager_btnAppCallBack(void);
AppManager_status AppManager_run(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPMANAGER_H */