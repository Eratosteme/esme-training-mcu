// HEAD
/* 
 * File:   SERP.h
 * Author: Esme Sudria
 */ /*

#ifndef SERP_H
#define	SERP_H

#include <stdint.h>
#include <stdbool.h>
#include "Common.h" // Pour les types standards

#ifdef	__cplusplus
extern "C" {
#endif

// CONSTANTES DU PROTOCOLE (Page 56) /
#define SERP_START_BYTE     0x6F
#define SERP_STOP_BYTE      0x65
#define SERP_ESCAPE_BYTE    0x64

// ID DES MESSAGES (Page 61) /
#define SERP_ID_RX_START_MEASURE    17  // IHM -> MCU
#define SERP_ID_RX_STOP_MEASURE     18  // IHM -> MCU

#define SERP_ID_TX_TEMP_VALUE       18  // MCU -> IHM
#define SERP_ID_TX_LIVE_SIGN        19  // MCU -> IHM
#define SERP_ID_TX_CUSTOM_MSG       20  // MCU -> IHM
*/
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

// HEAD
/*
    SERP_eSTATUS_OK = 0,
    SERP_eSTATUS_ERR_NULL_PTR,
    SERP_eSTATUS_ERR_DATA_TOO_LONG
} SERP_enuStatus;

/* PROTOTYPES PUBLICS */

/**
 * @brief Initialise le driver SERP (et l'EUSART sous-jacent)
 */
//void SERP_vidInitialize(void);

/**
 * @brief Envoie un message formaté selon le protocole SERP
 * @param u8MsgId : L'identifiant du message (ex: 20 pour Custom)
 * @param pu8Data : Pointeur vers les données à envoyer
 * @param u16DataLen : Taille des données (max 50 octets recommandé)
 * @return Statut de l'envoi
 */ /*
SERP_enuStatus SERP_enuSendMessage(uint8_t u8MsgId, uint8_t *pu8Data, uint16_t u16DataLen);

#ifdef	__cplusplus
}
#endif

#endif	// SERP_H /
*/

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
