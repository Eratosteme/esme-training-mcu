/* 
 * File:   SERP.c
 * Author: Esme Sudria
 */

#include "SERP.h"
#include "EUSART.h" // Inclusion du driver Hardware

/* MACROS */
// Timeout pour l'envoi d'un caractère (en ms). 
// 10ms est largement suffisant pour 1 octet à 115200 bauds.
#define SERP_TX_TIMEOUT_MS  10U 

/* FONCTIONS PRIVEES */

/**
 * @brief Wrapper pour adapter la fonction EUSART existante
 * @param u8Byte: L'octet à envoyer
 */
static void SERP_vidWriteByte(uint8_t u8Byte)
{
    // Conversion explicite en (char) car EUSART_vidSendChar attend un char
    EUSART_vidSendChar((char)u8Byte, SERP_TX_TIMEOUT_MS);
}

/**
 * @brief Envoie un octet en gérant le caractère d'échappement (Escaping)
 */
static void SERP_vidSendSafeByte(uint8_t u8Byte)
{
    // Si l'octet correspond à un caractère spécial (Start, Stop, Escape)
    if ((u8Byte == SERP_START_BYTE) || 
        (u8Byte == SERP_STOP_BYTE)  || 
        (u8Byte == SERP_ESCAPE_BYTE))
    {
        // On envoie d'abord le caractère d'échappement
        SERP_vidWriteByte(SERP_ESCAPE_BYTE);
    }
    
    // On envoie l'octet (qu'il ait été échappé ou non)
    SERP_vidWriteByte(u8Byte);
}

/* FONCTIONS PUBLIQUES */

void SERP_vidInitialize(void)
{
    // L'EUSART est déjà initialisé dans le main via EUSART_vidInitialize().
    // Pas d'actions supplémentaires requises ici pour l'émission.
}

SERP_enuStatus SERP_enuSendMessage(uint8_t u8MsgId, uint8_t *pu8Data, uint16_t u16DataLen)
{
    // Vérification des paramètres
    if (pu8Data == NULL && u16DataLen > 0)
    {
        return SERP_eSTATUS_ERR_NULL_PTR;
    }

    // 1. Envoi du START BYTE (Jamais échappé)
    SERP_vidWriteByte(SERP_START_BYTE);

    // 2. Envoi de l'ID (Peut être échappé)
    SERP_vidSendSafeByte(u8MsgId);

    // 3. Envoi de la LONGUEUR (2 octets, LSB first)
    // LSB (Poids faible)
    SERP_vidSendSafeByte((uint8_t)(u16DataLen & 0xFF));
    // MSB (Poids fort)
    SERP_vidSendSafeByte((uint8_t)((u16DataLen >> 8) & 0xFF));

    // 4. Envoi des DONNEES (Payload)
    for (uint16_t i = 0; i < u16DataLen; i++)
    {
        SERP_vidSendSafeByte(pu8Data[i]);
    }

    // 5. Envoi du STOP BYTE (Jamais échappé)
    SERP_vidWriteByte(SERP_STOP_BYTE);

    return SERP_eSTATUS_OK;
}