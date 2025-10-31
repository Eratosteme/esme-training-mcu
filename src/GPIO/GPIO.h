/* 
 * *****************************************************************************
 * Company: ESME Sudria
 * Projet: Projet ESME
 * 
 * *****************************************************************************
 * @file:     GPIO.h
 * 
 * @author:   Ephistos
 * @date      31 octobre 2025, 03:02
 * @version   0.0.0
 * @copyright Copyright (c) 2025 This software is used for education proposal
 */

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

/* INCLUDE FILES */
    
 
/* CONSTANTS MACROS */
#define GPIO_MA_MACRO
    
/* TYPES */
typedef enum GPIO_status
{
  GPIO_OK = 0, // Tous va bien
  GPIO_NOT_OK, // Erreur?
  GPIO_UNDEFINED,
  GPIO_CALLBACK_INIT_ERROR,
}GPIO_status;

typedef void (*GPIO_btnAppCallBackType)(void);

/* PUBLIC FUNCTION PROTOTYPES */
GPIO_status GPIO_initialize(void);
GPIO_status GPIO_setGpioHigh(void);
GPIO_status GPIO_setGpioLow(void);
void GPIO_registerBtnCallback(GPIO_btnAppCallBackType callback);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

