/* 
 * File:   LED.h
 * Author: mperr
 *
 * Created on 24 octobre 2025, 16:05
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>    
    
#define GPIO_MAX 44
#define LED_PIN 4  // RA4

    
typedef enum LED_tenuStatus
{
  LED_eSTATUS_OK                                            = 0,  //!< Everything is OK
  LED_eSTATUS_NO_OK,                                              //!< Generic/default error code
}LED_tenuStatus;

LED_tenuStatus LED_Init(void); 
LED_tenuStatus LED_Pilot(uint8_t state);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

