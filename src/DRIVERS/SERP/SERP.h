/**
 * @file SERP.h
 * @author Thomas Boubennec
 * @date 2025
 * @version 1.0
 *
 * @brief Driver de communication série SERP
 *
 * @details
 * Ce composant implémente un protocole d?encapsulation pour permettre
 * l?échange de messages entre le microcontrôleur et l?IHM PC via l?EUSART.
 */

#ifndef SERP_H_
#define SERP_H_

/* INCLUDE FILES */
#include <stdint.h>
#include <stdbool.h>

/* CONSTANTS MACROS */
/* IDs provenant de la slide 61 */
#define SERP_START_MEASURE_MSG_ID   17u     /* RX depuis l'IHM */
#define SERP_STOP_MEASURE_MSG_ID    18u     /* RX depuis l'IHM */
#define SERP_TEMP_VALUE_MSG_ID      18u     /* TX vers l'IHM (1 octet) */
#define SERP_LIVE_SIGN_MSG_ID       19u     /* TX vers l'IHM */
#define SERP_CUSTOM_MSG_ID          20u     /* TX jusqu'à 50 octets */

/* TYPES */
typedef enum
{
    SERP_enOK = 0,
    SERP_enERROR,
    SERP_enINVALID_PARAM,
    SERP_enBUSINESS_ERROR
} SERP_tenuStatus;

typedef void (*SERP_tpfvidMsgRxCallback)(uint8_t u8MsgId,
                                         uint16_t u16Length,
                                         const uint8_t *pu8Data);

/* PUBLIC FUNCTION PROTOTYPES */
SERP_tenuStatus SERP_enuInit(void);

SERP_tenuStatus SERP_enuRegisterAppCbk(SERP_tpfvidMsgRxCallback pfCallback);

SERP_tenuStatus SERP_enuSendMsg(uint8_t u8MsgId,
                                const uint8_t *pu8Data,
                                uint16_t u16Length);

#endif /* SERP_H_ */