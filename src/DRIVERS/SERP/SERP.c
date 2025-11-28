// HEAD
/* 
 * File:   SERP.c
 * Author: Esme Sudria
 */

//#include "SERP.h"
//#include "EUSART.h" // Inclusion du driver Hardware

/* MACROS */
// Timeout pour l'envoi d'un caractère (en ms). 
// 10ms est largement suffisant pour 1 octet à 115200 bauds.
//#define SERP_TX_TIMEOUT_MS  10U 

/* FONCTIONS PRIVEES */

/**
 * @brief Wrapper pour adapter la fonction EUSART existante
 * @param u8Byte: L'octet à envoyer
 *//*
static void SERP_vidWriteByte(uint8_t u8Byte)
{
    // Conversion explicite en (char) car EUSART_vidSendChar attend un char
    EUSART_vidSendChar((char)u8Byte, SERP_TX_TIMEOUT_MS);
}*/

/**
 * @brief Envoie un octet en gérant le caractère d'échappement (Escaping)
 */ /*
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
*/
/* FONCTIONS PUBLIQUES */
/*
void SERP_vidInitialize(void)
{
    // L'EUSART est déjà initialisé dans le main via EUSART_vidInitialize().
    // Pas d'actions supplémentaires requises ici pour l'émission.
}*/
/*
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
*/
/**
 * @file SERP.c
 * @author Thomas Boubennec - Groupe 7
 * @date 2025
 * @version 1.0
 *
 * @brief Driver de communication série SERP
 *
 * @details
 * Ce composant implémente un protocole de communication encapsulé
 * pour permettre l?échange de messages entre le microcontrôleur et
 * une IHM PC via l?EUSART.
 */

/* INCLUDE FILES */
#include "SERP.h"
#include "EUSART.h"

/* CONSTANTS MACROS */
#define SERP_START_BYTE   0x6F
#define SERP_STOP_BYTE    0x65
#define SERP_ESCAPE_BYTE  0x64

#define SERP_TEMPERATURE_MSG_ID   18
#define SERP_LIVE_MSG_ID          19
#define SERP_CUSTOM_MSG_ID        20

#define SERP_MAX_DATA_LEN         50
#define SERP_MAX_RAW_FRAME_BYTES  (2 + 1 + SERP_MAX_DATA_LEN)

/* TYPES */
typedef enum
{
    SERP_RX_IDLE = 0,
    SERP_RX_WAIT_DATA,
    SERP_RX_WAIT_ESCAPE
} SERP_RxState_t;

/* PRIVATE VARIABLES */
static SERP_tpfvidMsgRxCallback SERP_pfAppCallback = 0;
static SERP_RxState_t SERP_enRxState = SERP_RX_IDLE;
static uint8_t SERP_au8RxRawBuffer[SERP_MAX_RAW_FRAME_BYTES];
static uint16_t SERP_u16RxRawIndex = 0;
static uint8_t SERP_au8RxDataBuffer[SERP_MAX_DATA_LEN];

/* PRIVATE FUNCTION PROTOTYPES */
static void SERP_vidResetRxState(void);
static void SERP_vidProcessCompleteFrame(void);
static void SERP_vidSendEncodedByte(uint8_t b);
static void SERP_vidEusartRxCallback(char const * const data,
                                     const uint16_t length,
                                     const EUSART_tenuStatus status);

/* PRIVATE FUNCTION DEFINITIONS */
static void SERP_vidResetRxState(void)
{
    SERP_enRxState = SERP_RX_IDLE;
    SERP_u16RxRawIndex = 0;
}

static void SERP_vidSendEncodedByte(uint8_t b)
{
    if (b == SERP_START_BYTE || b == SERP_STOP_BYTE || b == SERP_ESCAPE_BYTE)
        EUSART_vidSendChar((char)SERP_ESCAPE_BYTE, CMN_10_MS);

    EUSART_vidSendChar((char)b, CMN_10_MS);
}

static void SERP_vidProcessCompleteFrame(void)
{
    uint16_t length;
    uint8_t id;
    uint16_t i;

    if (SERP_u16RxRawIndex < 3)
        return;

    length  = SERP_au8RxRawBuffer[0];
    length |= ((uint16_t)SERP_au8RxRawBuffer[1] << 8);

    id = SERP_au8RxRawBuffer[2];

    if (length > SERP_MAX_DATA_LEN)
        return;

    if ((SERP_u16RxRawIndex - 3) != length)
        return;

    for (i = 0; i < length; i++)
        SERP_au8RxDataBuffer[i] = SERP_au8RxRawBuffer[i + 3];

    if (SERP_pfAppCallback)
        SERP_pfAppCallback(id, length, SERP_au8RxDataBuffer);
}

static void SERP_vidEusartRxCallback(char const * const data,
                                     const uint16_t length,
                                     const EUSART_tenuStatus status)
{
    if ((length == 0) || (status != EUSART_eSTATUS_OK))
        return;

    uint8_t u8Byte = (uint8_t)data[0];

    switch (SERP_enRxState)
    {
        case SERP_RX_IDLE:
            if (u8Byte == SERP_START_BYTE)
            {
                SERP_enRxState = SERP_RX_WAIT_DATA;
                SERP_u16RxRawIndex = 0;
            }
            break;

        case SERP_RX_WAIT_DATA:
            if (u8Byte == SERP_START_BYTE)
            {
                SERP_u16RxRawIndex = 0;
            }
            else if (u8Byte == SERP_ESCAPE_BYTE)
            {
                SERP_enRxState = SERP_RX_WAIT_ESCAPE;
            }
            else if (u8Byte == SERP_STOP_BYTE)
            {
                SERP_vidProcessCompleteFrame();
                SERP_vidResetRxState();
            }
            else
            {
                if (SERP_u16RxRawIndex < SERP_MAX_RAW_FRAME_BYTES)
                    SERP_au8RxRawBuffer[SERP_u16RxRawIndex++] = u8Byte;
                else
                    SERP_vidResetRxState();
            }
            break;

        case SERP_RX_WAIT_ESCAPE:
            if (SERP_u16RxRawIndex < SERP_MAX_RAW_FRAME_BYTES)
                SERP_au8RxRawBuffer[SERP_u16RxRawIndex++] = u8Byte;

            SERP_enRxState = SERP_RX_WAIT_DATA;
            break;
    }
}

/* PUBLIC FUNCTION DEFINITIONS */
SERP_tenuStatus SERP_enuInit(void)
{
    SERP_vidResetRxState();
    SERP_pfAppCallback = 0;

    EUSART_enuRegisterRxCbk(SERP_vidEusartRxCallback);

    return SERP_enOK;
}

SERP_tenuStatus SERP_enuRegisterAppCbk(SERP_tpfvidMsgRxCallback pfCallback)
{
    if (pfCallback == 0)
        return SERP_enINVALID_PARAM;

    SERP_pfAppCallback = pfCallback;
    return SERP_enOK;
}

SERP_tenuStatus SERP_enuSendMsg(uint8_t u8MsgId, const uint8_t *pData, uint16_t len)
{
    uint16_t i;
    uint8_t L = (uint8_t)len;
    uint8_t H = (uint8_t)(len >> 8);

    if ((len > SERP_MAX_DATA_LEN) || (len > 0 && pData == 0))
        return SERP_enINVALID_PARAM;

    EUSART_vidSendChar((char)SERP_START_BYTE, CMN_10_MS);

    SERP_vidSendEncodedByte(L);
    SERP_vidSendEncodedByte(H);
    SERP_vidSendEncodedByte(u8MsgId);

    for (i = 0; i < len; i++)
        SERP_vidSendEncodedByte(pData[i]);

    EUSART_vidSendChar((char)SERP_STOP_BYTE, CMN_10_MS);

    return SERP_enOK;
}
