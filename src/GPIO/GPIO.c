/* 
 * *****************************************************************************
 * Company: ESME Sudria
 * Projet: Projet ESME
 * 
 * *****************************************************************************
 * @file:     GPIO.c
 * 
 * @author:   Ephistos
 * @date      31 octobre 2025, 03:02
 * @version   0.0.0
 * @copyright Copyright (c) 2025 This software is used for education proposal
 */

/* INCLUDE FILES */
#include <xc.h>
#include <stdbool.h>
#include <stdio.h>
#include "GPIO.h"
#include "ISR.h"

/* CONFIGURATION BITS */
#pragma config WDTE = OFF       /* disable Watchdog */
#pragma config LVP = ON         /* Low voltage programming enabled */

/* CONSTANTS MACROS */
#define INPUT 1
#define OUTPUT 0
#define DISABLED 0
#define ENABLED 1
/* TYPES */

/* PRIVATE VARIABLES */
//GPIO_status GPIO_returnCode = GPIO_OK;
static GPIO_btnAppCallBackType GPIO_btnAppCallBack        = NULL;

/* PRIVATE FUNCTION PROTOTYPES */
bool GPIO_BtnIsrCallBck(void);

/* PRIVATE FUNCTION DEFINITIONS */
bool GPIO_BtnIsrCallBck(void)
{
  // check if the interrupt is from button at pin B4 and falling-edge
  CMN_systemPrintf("Interrupt : %d \r\n",IOCBFbits.IOCBF4);
  if (IOCBFbits.IOCBF4) {
    //CMN_systemPrintf("Button Pressed ! \r\n");
    IOCBFbits.IOCBF4 = 0;  // Clear the flag
    if (GPIO_btnAppCallBack != NULL) {
      CMN_systemPrintf("ButtonCallback ! \r\n");
      GPIO_btnAppCallBack(); // Call AppManager
    }
    return true;
  }
  return false;
}

/* PUBLIC FUNCTION DEFINITIONS */
GPIO_status GPIO_registerBtnCallback(GPIO_btnAppCallBackType callback)
{
  GPIO_status status = GPIO_OK;
  
  if(callback == NULL)
  {
    CMN_systemPrintf("error: no callback function given \r\n"):
    return GPIO_CALLBACK_INIT_ERROR;
  }
  
  GPIO_btnAppCallBack = callback;
  CMN_systemPrintf("registering callbackfct : %d \r\n",callback);
  if(!ISR_bRegisterIsrCbk(ISR_ePERIPHERAL_INPUT_GPIO, GPIO_BtnIsrCallBck))
  {
    status = GPIO_CALLBACK_REGISTER_ERROR;
    CMN_systemPrintf("error registering callback function \r\n");
  }
  return status;
}

GPIO_status GPIO_initialize(void)
{
  GPIO_status status = GPIO_OK;
  TRISAbits.TRISA4 = OUTPUT;        // LED pin
  TRISBbits.TRISB4 = INPUT;         // button pin
  WPUBbits.WPUB4 = ENABLED;         // weak pull-up resistor
  ANSELBbits.ANSELB4 = DISABLED;    // analog functionality
  IOCBFbits.IOCBF4 = 0;             // Clear interrupt flag
  IOCBNbits.IOCBN4 = ENABLED;       // enable falling-edge detection
  PIE0bits.IOCIE = ENABLED;         // Enable IOC interrupt
  
  return status;
}

GPIO_status GPIO_setGpioHigh(void)
{
  GPIO_status status = GPIO_OK;
  PORTAbits.RA4 = 1;
  return status;
}

GPIO_status GPIO_setGpioLow(void)
{
  GPIO_status status = GPIO_OK;
  PORTAbits.RA4 = 0;
  return status;
}