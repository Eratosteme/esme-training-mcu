/* 
 * File:   SERP.h
 * Author: Esme Sudria
 */

#ifndef SERP_H
#define	SERP_H

#include <stdint.h>
#include <stdbool.h>
#include "Common.h" // Pour les types standards

#ifdef	__cplusplus
extern "C" {
#endif

/* CONSTANTES DU PROTOCOLE (Page 56) */
#define SERP_START_BYTE     0x6F
#define SERP_STOP_BYTE      0x65
#define SERP_ESCAPE_BYTE    0x64

/* ID DES MESSAGES (Page 61) */
#define SERP_ID_RX_START_MEASURE    17  // IHM -> MCU
#define SERP_ID_RX_STOP_MEASURE     18  // IHM -> MCU

#define SERP_ID_TX_TEMP_VALUE       18  // MCU -> IHM
#define SERP_ID_TX_LIVE_SIGN        19  // MCU -> IHM
#define SERP_ID_TX_CUSTOM_MSG       20  // MCU -> IHM

/* TYPES */
typedef enum
{
    SERP_eSTATUS_OK = 0,
    SERP_eSTATUS_ERR_NULL_PTR,
    SERP_eSTATUS_ERR_DATA_TOO_LONG
} SERP_enuStatus;

/* PROTOTYPES PUBLICS */

/**
 * @brief Initialise le driver SERP (et l'EUSART sous-jacent)
 */
void SERP_vidInitialize(void);

/**
 * @brief Envoie un message formaté selon le protocole SERP
 * @param u8MsgId : L'identifiant du message (ex: 20 pour Custom)
 * @param pu8Data : Pointeur vers les données à envoyer
 * @param u16DataLen : Taille des données (max 50 octets recommandé)
 * @return Statut de l'envoi
 */
SERP_enuStatus SERP_enuSendMessage(uint8_t u8MsgId, uint8_t *pu8Data, uint16_t u16DataLen);

#ifdef	__cplusplus
}
#endif

#endif	/* SERP_H */