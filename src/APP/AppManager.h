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
}AppManager_status; 


/* PUBLIC FUNCTION PROTOTYPES */
AppManager_status AppManager_initialise(void);
AppManager_status AppManager_run(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPMANAGER_H */