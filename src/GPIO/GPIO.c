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
#include "GPIO.h"
#include "ISR.h"

/* CONFIGURATION BITS */
#pragma config WDTE = OFF       /* disable Watchdog */
#pragma config LVP = ON         /* Low voltage programming enabled */

/* CONSTANTS MACROS */
#define INPUT 1
#define OUTPUT 0
#define DISABLED 1
#define ENABLED 0
/* TYPES */

/* PRIVATE VARIABLES */
GPIO_status GPIO_returnCode = GPIO_OK;
static GPIO_btnAppCallBackType GPIO_btnAppCallBack        = NULL;

/* PRIVATE FUNCTION PROTOTYPES */
bool GPIO_BtnIsrCallBck(void);

/* PRIVATE FUNCTION DEFINITIONS */
bool GPIO_BtnIsrCallBck(void)
{
  // check if the interrupt is from button at pin B4 and falling-edge
  if (IOCBFbits.IOCBF4) {
    IOCBFbits.IOCBF4 = 0;  // Clear the flag
    if (GPIO_btnAppCallBack != NULL) {
      GPIO_btnAppCallBack(); // Call AppManager
    }
    return true;
  }
  return false;
}

/* PUBLIC FUNCTION DEFINITIONS */
void GPIO_registerBtnCallback(GPIO_btnAppCallBackType callback)
{
    GPIO_btnAppCallBack = callback;
}

GPIO_status GPIO_initialize(void)
{
  TRISAbits.TRISA4 = OUTPUT;        // LED pin
  TRISBbits.TRISB4 = INPUT;         // button pin
  WPUBbits.WPUB4 = ENABLED;         // weak pull-up resistor
  ANSELBbits.ANSELB4 = DISABLED;    // analog functionality
  IOCBNbits.IOCBN4 = ENABLED;       // enable falling-edge detection
  IOCBFbits.IOCBF4 = 0;             // Clear interrupt flag
  PIE0bits.IOCIE = ENABLED;         // Enable IOC interrupt
  if(!ISR_bRegisterIsrCbk(ISR_ePERIPHERAL_INPUT_GPIO, GPIO_BtnIsrCallBck))
  {
    GPIO_returnCode = GPIO_CALLBACK_INIT_ERROR;
  }
  return GPIO_returnCode;
}

GPIO_status GPIO_setGpioHigh(void)
{
  PORTAbits.RA4 = 1;
  return GPIO_returnCode;
}

GPIO_status GPIO_setGpioLow(void)
{
  PORTAbits.RA4 = 0;
  return GPIO_returnCode;
}