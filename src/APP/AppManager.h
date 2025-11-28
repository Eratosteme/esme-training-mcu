/**
 ***********************************************************************************************************************
 * Company: Esme Sudria
 * Project: Projet Esme
 *
 ***********************************************************************************************************************
 * @file      AppManager.h
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

#ifndef APPMANAGER_H
#define	APPMANAGER_H


/**********************************************************************************************************************/
/* INCLUDE FILES                                                                                                      */
/**********************************************************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


/**********************************************************************************************************************/
/* CONSTANTS, MACROS                                                                                                  */
/**********************************************************************************************************************/

    
/**********************************************************************************************************************/
/* TYPES                                                                                                              */
/**********************************************************************************************************************/
/**
 * @brief Set the list of the return values used by this module's function
 */
typedef enum AppManager_status
{
  AppManager_eSTATUS_OK = 0,
  AppManager_eSTATUS_NOK,
  AppManager_eSTATUS_ptrERROR,
  AppManager_unexpected_end,
}AppManager_status; 


/**********************************************************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES                                                                                         */
/**********************************************************************************************************************/
/**
 * @brief Initialize AppManager
 * @details Setup a callBack with th GPIO Module
 * @return - AppManager_eSTATUS_OK if it succeed
 *         - AppManager_eSTATUS_ptrERROR the setup failed due to an issue with 
 *           the callback pointer
 *         - AppManager_eSTATUS_NOK if the setup failed for unidentified reason 
 */
AppManager_status AppManager_initialise(void);

/*--------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief launch the AppManager
 * @details press the button to change state
 * @return AppManager_unexpected_end if the function return by accident
 */
AppManager_status AppManager_run(void);



#ifdef	__cplusplus
}
#endif
/*--------------------------------------------------------------------------------------------------------------------*/
#endif	/* APPMANAGER_H */
/*--------------------------------------------------------------------------------------------------------------------*/

