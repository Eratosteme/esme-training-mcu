/**
 * @file      ADC_cfg.h
 * @brief     Configuration de l'ADC pour le MCP9700
 * @copyright Copyright (c) 2024 Esme Sudria
 */
#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#include "Common.h"

/**
 * @brief Définit le canal utilisé pour le MCP9700.
 * @details 
 *  - true  : Le capteur est sur RA0 (Pin 2)
 *  - false : Le capteur est sur RB3 (Pin 36)
 */
#define ADC_CONFIG_USE_POTENTIOMETER  false  // <-- Assurez-vous que votre MCP9700 est sur RA0

/*--------------------------------------------------------------------------------------------------------------------*/
/* REGISTRES ET POSITIONS (Ne pas toucher sauf si changement de pin) */
/*--------------------------------------------------------------------------------------------------------------------*/

#if(ADC_CONFIG_USE_POTENTIOMETER == true)
#  define ADC_CONFIG_REG_ADDRESS_TRIS       0x0F87 // TRISA
#  define ADC_CONFIG_REG_ADDRESS_ANSEL      0x0F0C // ANSELA
#  define ADC_CONFIG_CHANNEL_ADPCH          0b00000000 // ANA0
#  define ADC_CONFIG_CHANNEL_PORT           _TRISA_TRISA0_POSITION
#elif(ADC_CONFIG_USE_POTENTIOMETER == false)
#  define ADC_CONFIG_REG_ADDRESS_TRIS       0x0F88 // TRISB
#  define ADC_CONFIG_REG_ADDRESS_ANSEL      0x0F14 // ANSELB
#  define ADC_CONFIG_CHANNEL_ADPCH          0b00001011 // ANB3
#  define ADC_CONFIG_CHANNEL_PORT           _TRISB_TRISB3_POSITION
#endif

#endif /* ADC_CFG_H_ */