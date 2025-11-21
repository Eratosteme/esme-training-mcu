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
  AppManager_unexpected_end,
}AppManager_status; 


/* PUBLIC FUNCTION PROTOTYPES */
AppManager_status AppManager_initialise(void);
AppManager_status AppManager_run(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPMANAGER_H */

